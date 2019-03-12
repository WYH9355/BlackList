#ifndef _SELECTER_H
#define _SELECTER_H

#include "Server.h"
#include "TcpServer.h"
#include <json/json.h>
#include <event.h>
#include <sstream>
#include "MyDefine.h"


//采集机服务器
class Selecter
{
	public:

		//构造函数
		Selecter();//创建事件表，端口监听

		//析构
		~Selecter();

		//Listen_cb
		static void Listen_cb(int fd,short event,void* arg);

		//Select_cb
		static void Select_cb(int fd,short event,void* arg);

		//运行 添加sockfd 循环
		void RunSelecter();


	private:

		TcpServer				_Server;			//服务器对象
		struct event_base*		_Lib_base;			//事件表
};


#endif


