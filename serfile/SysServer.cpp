#include "SysServer.h"




SysServer::SysServer()
{
	_base = event_base_new();

	int fd = Client::getClient()->getFd();

	struct event* listen_event = event_new(_base,fd,EV_READ|EV_PERSIST
			,listen_cb,_base);
	if ( NULL == listen_event )
	{
		std::cerr<<"listen_event new fail;errno:"<<errno<<std::endl;
		exit(1);
	}

	event_add(listen_event,NULL);
}

void SysServer::run()
{
	new WorkPthread;
	new WorkPthread;
	new WorkPthread;


	event_base_dispatch(_base);
}


void SysServer::listen_cb(int fd,short event,void* arg)
{
	struct event_base* base = (struct event_base*)arg;

	struct sockaddr_in caddr;
	socklen_t len = sizeof(caddr);
	int clifd = accept(fd,(struct sockaddr*)&caddr,&len);
	if ( -1 == clifd )
	{
		std::cerr<<"accept fail;errno:"<<errno<<std::endl;
		return;
	}

	struct event* cli_event = event_new(base,clifd,EV_READ|EV_PERSIST,clirecv_cb,NULL);
	if ( NULL == cli_event )
	{
		std::cerr<<"cli_event new fail;errno:"<<errno<<std::endl;
		exit(1);
	}
	event_add(cli_event,NULL);
}


void SysServer::clirecv_cb(int fd,short event,void* arg)
{
	std::string str;

	if ( -1 == Client::getClient()->recvClient(fd,str) )
	{
		std::cout<<"one client quit"<<std::endl;
		return ;
	}
	SPTR s = std::make_shared<std::pair<int,std::string>>(fd,str);

	Mqueue::getMqueue()->Push(s);
}





