#include "Selecter.h"


static const char *IP = "127.0.0.1";
static const unsigned short PORT = 8000;

//构造
Selecter::Selecter()
{
	//创建套接字并监听
	_Server.createServer(IP,PORT);

	//创建事件表
	_Lib_base = event_base_new();

}


//析构
Selecter::~Selecter()
{
	event_base_free(_Lib_base);
}


//客户端链接响应的回调函数
void Selecter::Listen_cb(int fd,short event,void* arg)
{
	struct event_base* lib_base = (struct event_base*)arg;
	struct sockaddr_in caddr;
	socklen_t len = sizeof(caddr);

	int clifd = accept(fd,(struct sockaddr*)&caddr,&len);
	if ( -1 == clifd )
	{
		std::cerr<<"Listen_cb accept fail;errno:"<<errno<<std::endl;
		return;
	}

	//注册客户端的链接事件
	struct event* cli_event = event_new(lib_base,
			clifd,EV_READ|EV_PERSIST,Select_cb,lib_base);
	if(NULL == cli_event)
	{
		std::cerr<<"cli event creat fail;errno:"<<errno<<std::endl;
		return;
	}
	
	//将事件加入事件表
	event_add(cli_event,NULL);
}

//客户端数据响应回调函数
void Selecter::Select_cb(int fd,short event,void* arg)
{

	char buff[128] = {0};
	Json::Value	val;
	Json::Reader read;

	if ( recv(fd,buff,127,0) <= 0)
	{
		close(fd);
		return ;
	}

	if ( !read.parse(buff,val) )
	{
		std::cerr<<"Select_cb read fail;errno:"<<errno<<std::cout;
		return ;
	}

	val[FD] = fd;
	Server::getServer()->sendServer(val.toStyledString());
}

//运行
void Selecter::RunSelecter()
{
	struct event* sockfd_event = event_new(_Lib_base,_Server.getFd(),EV_READ
			|EV_PERSIST,Listen_cb,_Lib_base);
	if ( NULL == sockfd_event )
	{
		std::cerr<<"sockfd_event new fail;errno:"<<errno<<std::endl;
		return ;
	}

	event_add(sockfd_event,NULL);

	event_base_dispatch(_Lib_base);
}
