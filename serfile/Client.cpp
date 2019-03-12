#include "Client.h"

//单例对象指针初始化
Client* Client::_client = nullptr;

//单例回收初始化 
Client::ClientDelete Client::_clientdelete;

//锁初始化
std::mutex Client::_mutex;


//获取单例类
Client* Client::getClient()
{
	if ( nullptr == _client )
	{
		std::lock_guard<std::mutex> lck(_mutex);

		if ( nullptr == _client )
		{
			_client = new Client;
		}
	}
	return _client;
}

//构造
Client::Client()
{
	if ( nullptr ==  _client )
	{
		std::string ip = "127.0.0.1";
		unsigned short port = 6000;

		_server = new TcpServer(ip,port);
	}
}


//服务器发送数据
int Client::sendClient(int fd,const std::string &str)
{
	return _server->sendClient(fd,str);
}

//服务器接收数据
int Client::recvClient(int fd,std::string &str)
{
	return _server->recvClient(fd,str);
}

//获取描述符
int Client::getFd()
{
	return _server->getFd();
}

//析构
Client::~Client()
{
	if ( _client )
	{
		delete _server;
		_server = nullptr;
	}
}

//回收
Client::ClientDelete::~ClientDelete()
{
	if ( _client )
	{
		delete _client;
		_client = nullptr;
	}
}


