#ifndef _TCPCLIENT_H
#define _TCPCLIENT_H
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <string>
#include <iostream>


//客户端类
class TcpClient
{
	public:

		TcpClient(){}

		//构造函数
		TcpClient(const std::string &ip,const unsigned short port);

		//链接函数
		int connectServer(const std::string &ip,const unsigned short port);

		//接收服务器的数据
		int recvServer(std::string &str);

		//给服务器发送数据
		int sendServer(const std::string &str);

		//获取套接字描述符
		int getFd()const;

		//获取端口号
		unsigned short getPort()const;

		//获取IP地址
		std::string getIP()const;

	private:

		int					_fd;	//客户端描述符
		std::string			_ip;	//IP地址
		unsigned short		_port;	//端口号
};




#endif




