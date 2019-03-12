#include "WorkPthread.h"



WorkPthread::WorkPthread()
{
	pthread_t id;
	if ( -1 == pthread_create(&id,NULL,run,NULL) )
	{
		std::cerr<<"pthread_create fail;errno:"<<errno<<std::endl;
		exit(2);
	}
}



void* WorkPthread::run(void* arg)
{
	while ( 1 )
	{
		SPTR p = Mqueue::getMqueue()->Pop();

		Contral::getContral()->process(p);
	}
}
