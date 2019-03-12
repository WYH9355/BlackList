#ifndef _MODEL
#define _MODEL

#include "View.h"
#include <string>
#include <unordered_map>




//MVC模式 模型
class Model
{
	public:
		void insertPair(int type,View *p);

		View* operator[](int type);

	private:
		std::unordered_map<int,View*> _map;
};


#endif
