#include "TcpServer.h"

//构造函数
TcpServer::TcpServer(const std::string &ip,const unsigned short port)
{
	_ip = ip;
	_port = port;
	createServer(ip,port);
}

//创建套接字
void TcpServer::createServer(const std::string &ip,const unsigned short port)
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if ( -1 == sockfd )
	{
		std::cerr<<"fd create fail;errno:"<<errno<<std::endl;
		exit(1);
	}

	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = inet_addr(ip.c_str());

	//绑定端口
	if (-1 == bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr)))
	{
		std::cerr<<"fd bind fail"<<errno<<std::endl;
		exit(2);
	}

	//监听
	if ( -1 == listen(sockfd,LISTEN_MAX))
	{
		std::cerr<<"fd listen fail;errno:"<<errno<<std::endl;
		exit(3);
	}

	_listenFd = sockfd;

	std::cout<<"监听成功 ip，port："<<ip<<" "<<port<<std::endl;
}

//创建套接字
int TcpServer::acceptClient()
{
	struct sockaddr_in caddr;
	socklen_t len = sizeof(caddr);
	int clifd = accept(_listenFd,(struct sockaddr*)&caddr,&len);
	if ( -1 == clifd )
	{
		std::cerr<<"clifd accept fail;errno:"<<errno<<std::endl;
	}
	return clifd;
}

//接收客户端数据
int TcpServer::recvClient(int clifd,std::string &str)
{
	char buff[512] = {0};
	if ( recv(clifd,buff,511,0) <= 0)
	{
		close(clifd);
		return -1;//客户端的链接断开 返回-1
	}
	str = buff;
	return str.size();
}

//发送服务器数据
int TcpServer::sendClient(int clifd,const std::string &str)
{
	int res = send(clifd,str.c_str(),strlen(str.c_str()),0);
	if ( -1 == res )
	{
		std::cerr<<"send fail;errno:"<<errno<<std::endl;
	}
	return res;
}

//获取套接字描述符
int TcpServer::getFd()const
{ 
	return _listenFd; 
}

//获取端口号
unsigned short TcpServer::getPort()const
{ 
	return _port; 
}

//获取IP地址
std::string TcpServer::getIp()const
{ 
	return _ip; 
}  















