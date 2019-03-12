#ifndef _TCPSERVER_H
#define _TCPSERVER_H
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <iostream>

//等待队列最大值
#define LISTEN_MAX 20

//服务器类
class TcpServer
{
	public:

		TcpServer(){}

		//构造函数
		TcpServer(const std::string &ip,const unsigned short port);

		//获取套接字
		void createServer(const std::string &ip,const unsigned short port);

		//接收客户端套接字
		int acceptClient();
	
		//接收客户端的数据
		int recvClient(int clifd,std::string &str);

		//给客户端发送数据
		int sendClient(int clifd,const std::string &str);

		//获取套接字描述符
		int getFd()const;

		//获取端口
		unsigned short getPort()const;

		//获取IP地址
		std::string getIp()const;  

	private:

		unsigned short		_port;		//端口号
		std::string			_ip;		//ip地址
		int					_listenFd;	//监听套接字
};








#endif
