#ifndef _MQUEUE_H
#define _MQUEUE_H

#include <queue>
#include <mutex>
#include <memory>
#include <unistd.h>


typedef std::shared_ptr<std::pair<int,std::string>>		SPTR;

//单例队列
class Mqueue
{
	public:


		static Mqueue* getMqueue();


		SPTR Pop();

		void Push(SPTR s);

	private:

		Mqueue();

		~Mqueue();

		Mqueue(const Mqueue &src);

		Mqueue& operator=(const Mqueue &src);

		static Mqueue*		_Mqueue;

		static std::mutex	_mutex;

		std::queue<SPTR>	_queue;
};

#endif
