#include "DataBase.h"

//初始化单例对象指针
DataBase* DataBase::_database = nullptr;

//初始化回收对象
DataBase::DataBaseDelete DataBase::_datadelete;

//初始化锁
std::mutex DataBase::_mutex;




//构造
DataBase::DataBase()
{
	_myrcon = mysql_init((MYSQL*)0);
	if ( !mysql_real_connect(_myrcon,"127.0.0.1","root","root",NULL,3306,NULL,0) )
	{
		std::cerr<<"sql connect fail;errno:"<<errno<<std::endl;
		exit(4);
	}
	//选择数据库
	if(mysql_select_db(_myrcon,"blacklist"))
	{
		std::cerr<<"select fail：errno："<<errno<<std::endl;
		exit(5);
	}

}

//析构
DataBase::~DataBase()
{
	mysql_close(_myrcon);
}

//回收
DataBase::DataBaseDelete::~DataBaseDelete()
{
	if ( _database )
	{
		delete _database;
		_database = nullptr;
	}
}


//获取单例对象
DataBase* DataBase::getDataBase()
{
	if ( nullptr == _database )
	{
		std::lock_guard<std::mutex> lck(_mutex);
		if ( nullptr == _database )
		{
			_database = new DataBase;
		}
	}
	return _database;
}


//用户注册
bool DataBase::insertRootList(Json::Value &val)
{
	bool flag = true;
	std::string str = "insert into rootlist(rootname,passwd) ";
	str += "values(\'" + val[NAME].asString() + "\',\'" + val[PW].
		asString() + "\')";


	if ( mysql_real_query(_myrcon,str.c_str(),str.size()) )
	{
		std::cerr<<"insert rootlist fail;errno:"<<errno<<std::endl;
		flag = false;
	}

	return flag;
}

//查询用户
bool DataBase::selectRootList(Json::Value &val)
{
	bool flag = true;
	std::string str = "select * from rootlist where rootname=";
	str += "'" + val[NAME].asString() +"'";

	if ( mysql_real_query(_myrcon,str.c_str(),str.size()) )
	{
		std::cerr<<"select rootlist fail;errno:"<<errno<<std::endl;
		flag = false;
		return flag;
	}

	//接收指令返回值
	MYSQL_RES* my_res = mysql_store_result(_myrcon);

	//接收返回值一行
	MYSQL_ROW my_row = mysql_fetch_row(my_res);
	if ( !my_row )
	{
		//查询失败
		flag = false;
	}

	if ( !(val[NAME].asString() == my_row[1] && val[PW].asString() == my_row[2]) )
		flag = false;

	mysql_free_result(my_res);
	
	return flag;
}



//插入黑名单
bool DataBase::insertBlackList(Json::Value &val)
{
	bool flag = true;
	std::string str = "insert into blacklist ";
	str += "values(" + val[ID].asString() + ",\'" 
					+ val[NAME].asString() + "\',\'"
					+ val[YEAR].asString() + "-"
					+ val[MONTH].asString() + "-"
					+ val[DAY].asString() + "\',"
					+ val[TIME].asString() + ")";
	

	if ( mysql_real_query(_myrcon,str.c_str(),str.size()) )
	{
		std::cerr<<"insert blacklist fail;errno:"<<errno<<std::endl;
		flag = false;
	}

	return flag;
}

//查询黑名单
bool DataBase::selectBlackList(Json::Value &val)
{
	bool flag = true;
	std::string str = "select id from blacklist where id=";
	str += val[ID].asString();

	
	if ( mysql_real_query(_myrcon,str.c_str(),str.size()) )
	{
		std::cerr<<"select blacklist fail;errno:"<<errno<<std::endl;
		flag = false;
		return flag;
	}

	//接收指令返回值
	MYSQL_RES* my_res = mysql_store_result(_myrcon);

	//接收返回值一行
	MYSQL_ROW my_row = mysql_fetch_row(my_res);
	if ( !my_row )
	{
		//查询失败
		flag = false;
	}
	mysql_free_result(my_res);
	
	return flag;
}

//删除黑用户
bool DataBase::deleteBlackList(Json::Value &val)
{
	bool flag = true;
	std::stringstream s;
	std::string tmp;
	std::string str = "delete from blacklist where id=";
	str += val[ID].asString();

	if ( mysql_real_query(_myrcon,str.c_str(),str.size()) )
	{
		std::cerr<<"delete blacklist fail;errno:"<<errno<<std::endl;
		flag = false;
	}

	return flag;
}


//更新用户
bool DataBase::updataBlackList(Json::Value &val)
{
	bool flag = true;
	std::string str = "update blacklist set ";
	str += "id=" + val[ID].asString() + ","
		+ " time=\'" + val[YEAR].asString() + "-" + val[MONTH].asString() + "-"
		+ val[DAY].asString() + "\'," 
		+ " limittime=" + val[TIME].asString()
		+ " where id=" + val[UPID].asString();

	if ( mysql_real_query(_myrcon,str.c_str(),str.size()) )
	{
		std::cerr<<"delete blacklist fail;errno:"<<errno<<std::endl;
		flag = false;
	}


	return flag;
}

