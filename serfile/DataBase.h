#ifndef _DATABASE_H
#define _DATABASE_H


#include <mysql/mysql.h>
#include <errno.h>
#include <string>
#include <json/json.h>
#include <mutex>
#include "MyDefine.h"
#include <string.h>
#include <sstream>
//数据库类
class DataBase
{

	public:

		//获取单例对象
		static DataBase* getDataBase();

		//主机登录注册
		bool insertRootList(Json::Value &val);
		bool selectRootList(Json::Value &val);

		//查询黑名单用户
		bool insertBlackList(Json::Value &val);
		bool deleteBlackList(Json::Value &val);
		bool selectBlackList(Json::Value &val);
		bool updataBlackList(Json::Value &val);


	private:

		//连接并选择数据
		DataBase();

		//断开连接
		~DataBase();

		DataBase(const DataBase &src);

		DataBase& operator=(const DataBase &src);

		class DataBaseDelete
		{
			public:
				~DataBaseDelete();
		};


		MYSQL*					_myrcon;		//数据库连接指针

		static DataBase*		_database;		//单例对象指针
		static DataBaseDelete	_datadelete;	//数据库回收对象
		static std::mutex		_mutex;			//资源互斥锁
};



#endif
