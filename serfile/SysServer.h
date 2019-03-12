#ifndef _SYSSERVER_H
#define _SYSSERVER_H

#include "Client.h"
#include "Mqueue.h"
#include "WorkPthread.h"
#include <sys/socket.h>
#include <event.h>




//服务器主机
class SysServer
{
	public:
		SysServer();

		void run();

		static void listen_cb(int fd,short event,void* arg);

		static void clirecv_cb(int fd,short event,void* arg);

	private:

		struct event_base* _base;

};







#endif
