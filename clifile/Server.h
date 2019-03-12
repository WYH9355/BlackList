#ifndef _SERVER_H
#define _SERVER_H
#include "TcpClient.h"
#include <mutex>


//客户端的‘服务器’ 单例模式
class Server
{
	public:

		//获取单例对象
		static Server* getServer();

		//客户端发送数据
		int sendServer(const std::string &str);

		//客户端接收数据
		int recvServer(std::string &str);

		//获取客户端描述符
		int getFd();

	private:

		//构造
		Server(const std::string &ip,const unsigned short port);
		
		//析构
		~Server();

		//拷贝构造
		Server(const Server &src);

		//赋值重载
		Server& operator=(const Server &src);

		//单例析构类
		class ServerDelete
		{
			public:
				~ServerDelete();
		};
		
		TcpClient *					_cli;			//客户端对象

		static Server *				_server;		//单例对象指针
		static ServerDelete			_serverdelete;	//单例析构对象
		static std::mutex			_mutex;			//互斥锁对象
};


#endif





