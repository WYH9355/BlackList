#include "Server.h"

//初始化单例对象指针
Server* Server::_server = nullptr;

//初始化单例析构对象
Server::ServerDelete Server::_serverdelete;

//初始化互斥锁对象
std::mutex Server::_mutex;




//获取单例对象
Server* Server::getServer()
{
	if ( nullptr == _server )
	{
		//使用锁守卫 构造时加锁 析构时解锁 防止new失败时无法解锁
		std::lock_guard<std::mutex> _lck(_mutex);

		if ( nullptr == _server )
		{
			std::string ip;
			unsigned short port;
			std::cout<<"\ninput ip & port to Client：";
			std::cin>>ip>>port;

			_server = new Server(ip,port);
		}

	}
	return _server;
}

//构造函数
Server::Server(const std::string &ip,const unsigned short port)
{
	if ( nullptr == _cli )
	{
		_cli = new TcpClient(ip,port);
	}
}

//客户端发送数据
int Server::sendServer(const std::string &str)
{
	return _cli->sendServer(str);
}

//客户端接收数据
int Server::recvServer(std::string &str)
{
	return _cli->recvServer(str);
}

//获取客户端描述符
int Server::getFd()
{
	return _cli->getFd();
}

//析构函数
Server::~Server()
{
	if ( _server )
	{
		delete _cli;
		_cli = nullptr;
	}
}

//回收函数的析构
Server::ServerDelete::~ServerDelete()
{
	if ( _server )
	{
		delete _server;
		_server = nullptr;
	}
}







