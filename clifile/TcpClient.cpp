#include "TcpClient.h"


//构造函数

//无参数构造


TcpClient::TcpClient(const std::string &ip,const unsigned short port)
{
	connectServer(ip,port);
}

//链接函数
int TcpClient::connectServer(const std::string &ip,const unsigned short port)
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if ( -1 == sockfd )
	{
		std::cerr<<"sockfd create fail;errno:"<<errno<<std::endl;
		exit(1);
	}

	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = inet_addr(ip.c_str());

	_fd = sockfd;
	_ip = ip;
	_port = port;

	if ( -1 == connect(_fd,(struct sockaddr*)&saddr,sizeof(saddr)) )
	{
		std::cerr<<"fd connect fail;errno:"<<errno<<std::endl;
		return -1;
	}

	std::cout<<"链接上：ip,port:"<<_ip<<" "<<_port<<std::endl;
	return 0;
}

//接收服务器的数据
int TcpClient::recvServer(std::string &str)
{
	char buff[128] = {0};
	if ( recv(_fd,buff,127,0) <= 0 )
	{
		close(_fd);
		std::cerr<<"recv fail;errno:"<<errno<<std::endl;
		return -1;
	}

	str = buff;

	return str.size();
}

//给服务器发送数据
int TcpClient::sendServer(const std::string &str)
{
	int res = send(_fd,str.c_str(),strlen(str.c_str()),0);
	if ( -1 == res )
	{
		std::cerr<<"fd send fail;errno:"<<errno<<std::endl;
	}
	return res;
}

//获取套接字描述符
int TcpClient::getFd()const
{
	return _fd;
}

//获取端口号
unsigned short TcpClient::getPort()const
{
	return _port;
}

//获取IP地址
std::string TcpClient::getIP()const
{
	return _ip;
}








