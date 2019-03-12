#ifndef _CLIENT_H
#define _CLIENT_H


#include "TcpServer.h"
#include <mutex>



//单例模式
class Client
{
	public:

		//获取单例对象
		static Client* getClient();

		//服务器发送数据
		int sendClient(int fd,const std::string &str);

		//服务器接收数据
		int recvClient(int fd,std::string &str);


		//获取描述符
		int getFd();
	
	private:

		//构造 创建服务端套接字 初始化事件表
		Client();

		//析构 关闭套接字 关闭内核事件
		~Client();

		Client(const Client &src);

		Client& operator=(const Client &src);


		//单例回收类
		class ClientDelete
		{
			public:
				~ClientDelete();
		};


		static Client *			_client;
		static ClientDelete		_clientdelete;
		static std::mutex		_mutex;

		TcpServer *				_server;
};

#endif
