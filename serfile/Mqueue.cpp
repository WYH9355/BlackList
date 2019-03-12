#include "Mqueue.h"

Mqueue* Mqueue::_Mqueue = nullptr;

std::mutex Mqueue::_mutex;


Mqueue* Mqueue::getMqueue()
{
	if ( nullptr == _Mqueue )
	{
		std::lock_guard<std::mutex> lckg(_mutex);
		if ( nullptr == _Mqueue )
		{
			_Mqueue = new Mqueue;
		}
	}
	return _Mqueue;
}

Mqueue::Mqueue()
{

}

SPTR Mqueue::Pop()
{
	while ( 1 )
	{
		if ( !_queue.empty() )
		{
			std::lock_guard<std::mutex> lck(_mutex);
			if ( !_queue.empty() )
			{
				SPTR res = _queue.front();_queue.pop();
				return res;
			}
		}
		else
		{
			sleep(1);
		}
	}
}



void Mqueue::Push(SPTR s)
{
	_queue.push(s);
}




