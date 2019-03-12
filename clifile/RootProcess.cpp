#include "RootProcess.h"


//界面显示
void RootProcess::put()
{
	printf("***********************************\n");
	printf("****           HOST            ****\n");
	printf("****	 1、insert             ****\n");
	printf("****	 2、delete             ****\n");
	printf("****	 3、select             ****\n");
	printf("****	 4、Update             ****\n");
	printf("****	 5、exit               ****\n");
	printf("***********************************\n");
}


//insert
bool RootProcess::Insert()
{
	std::string str[6];
	Json::Value val;

	
	std::cout<<"输入 name id year month day time(day)：";
	for (int i=0;i<6;++i)
	{
		std::cin>>str[i];
	}


	val[TYPE]	= INSERT_HOST;//增加操作
	val[FD]		= HOSTFD;
	val[NAME]	= str[0].c_str();
	val[ID]		= str[1].c_str();
	val[YEAR]	= str[2].c_str();
	val[MONTH]	= str[3].c_str();
	val[DAY]	= str[4].c_str();
	val[TIME]	= str[5].c_str();

	if ( -1 == Server::getServer()->sendServer(val.toStyledString()))
	{
		std::cerr<<"insert_host send fail;errno:"<<errno<<std::endl;
		return false;
	}
	return true;
}

//delete
bool RootProcess::Delete()
{
	std::string str;
	Json::Value val;

	std::cout<<"输入删除的id：";
	std::cin>>str;

	val[TYPE]	= DELETE_HOST;//删除操作
	val[FD]		= HOSTFD;
	val[ID]		= str.c_str();

	if ( -1 == Server::getServer()->sendServer(val.toStyledString()) )
	{
		std::cerr<<"delete_host send fail;errno:"<<errno<<std::endl;
		return false;
	}
	return true;
}

//select
bool RootProcess::Select()
{
	std::string str;
	Json::Value val;

	std::cout<<"输入查询的id：";
	std::cin>>str;

	val[TYPE]	= SELECT_HOST;//查询操作
	val[FD]		= HOSTFD;
	val[ID]		= str.c_str();

	if ( -1 == Server::getServer()->sendServer(val.toStyledString()) )
	{
		std::cerr<<"Select_host send fail;errno:"<<errno<<std::endl;
		return false;
	}
	return true;
}

//Update
bool RootProcess::Update()
{
	std::string str;
	Json::Value	val;
	std::string newstr[6];

	std::cout<<"输入要修改的id：";
	std::cin>>str;

	
	std::cout<<"输入新的 name id year month day time：";
	for (int i=0;i<6;++i)
	{
		std::cin>>newstr[i];
	}


	val[TYPE]	= UPDATE_HOST;//更新操作
	val[FD]		= HOSTFD;
	val[UPID]	= str.c_str();
	val[NAME]	= newstr[0].c_str();
	val[ID]		= newstr[1].c_str();
	val[YEAR]	= newstr[2].c_str();
	val[MONTH]	= newstr[3].c_str();
	val[DAY]	= newstr[4].c_str();
	val[TIME]	= newstr[5].c_str();

	if ( -1 == Server::getServer()->sendServer(val.toStyledString()) )
	{
		std::cerr<<"Update_host send fail;errno:"<<errno<<std::endl;
		return false;
	}
	return true;
}


//exit
void RootProcess::ExitPro()
{
	exit(1);
}

//主机运行
void RootProcess::run()
{
	
	//启动接收线程
	RecvServerPthreadStart();
	
	//启动采集器线程
	SelecterPtreadStart();
	


	std::cout<<"\n启动！"<<std::endl;


	//主线程
	while (1)
	{

		int n = 0;

		put();
		printf("Input：");
		std::cin>>n;

		switch( n )
		{
			case 1:
				Insert();
				break;
			case 2:
				Delete();
				break;
			case 3:
				Select();
				break;
			case 4:
				Update();
				break;
			case 5:
				ExitPro();
				break;
			default:
				std::cout<<"input errno"<<std::endl;
				break;
		}
	}

	exit(0);
}



//接收工作线程
void* RootProcess::RecvWork(void* arg)
{

	while ( 1 )
	{
		Json::Value val;
		Json::Reader read;
		std::string str;

		if ( -1 == Server::getServer()->recvServer(str) )
		{
			std::cerr<<"connect down !;errno:"<<errno<<std::endl;
			pthread_exit(NULL);
		}

		if ( !read.parse(str,val) )
		{
			std::cerr<<"recv work read fail;errno:"<<errno<<std::endl;
			continue;
		}

	

		if ( val[FD].asInt() == HOSTFD )
		{
			
			Json::Value::Members mem = val.getMemberNames();

			std::cout<<"操作："<<val[REASON].asString()<<std::endl;
			usleep(500);
			/*for (auto it = mem.begin();it != mem.end(); ++it)
			{
				std::cout<<*it<<"\t: "<<val[*it]<<std::endl;
			}*/
		}
		else
		{
			if ( send(val[FD].asInt(),str.c_str(),str.size(),0) <= 0 )
			{
				std::cerr<<"send cfd fail;errno:"<<errno<<std::endl;
			}
		}
	}
}
//接收启动
bool RootProcess::RecvServerPthreadStart()
{
	pthread_t id;
	if ( pthread_create(&id,NULL,RecvWork,NULL) != 0)
	{
		std::cerr<<"recv pthread create fail;errno:"<<errno<<std::endl;
		exit(1);
	}
	return true;
}


void* RootProcess::SelecterWork(void* arg)
{
	Selecter _selecter;
	_selecter.RunSelecter();
}
//采集器线程启动
void RootProcess::SelecterPtreadStart()
{
	pthread_t id;
	if ( pthread_create(&id,NULL,SelecterWork,NULL) != 0)
	{
		std::cerr<<"Selecter pthread create fail;errno:"<<errno<<std::endl;
		exit(1);
	}
}




