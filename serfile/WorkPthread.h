#ifndef _WORKPTHREAD_H
#define _WORKPTHREAD_H


#include <pthread.h>
#include "Mqueue.h"
#include "Contral.h"

//工作线程
class WorkPthread
{
	public:

		WorkPthread();

		static void* run(void* arg);
};




#endif
