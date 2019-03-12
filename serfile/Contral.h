#ifndef _CONTRAL_H
#define _CONTRAL_H

#include "Model.h"
#include "MyDefine.h"
#include <memory>
#include <mutex>
#include <json/json.h>

typedef std::shared_ptr<std::pair<int,std::string>> SHAREDPTR;

//MVC模式  单例模式
class Contral
{
	public:


		void process(SHAREDPTR sptr);

		static Contral* getContral();


	private:


		Contral();

		~Contral();

		Contral(const Contral &src);

		Contral& operator=(const Contral &src);



		class ContralDelete
		{
			public:
				~ContralDelete();
		};


		//单例对象指针
		static Contral *		_contral;
		//锁
		static std::mutex		_mutex;
		//单例回收
		static ContralDelete	_contralDelete;

		Model*					_model;
};



#endif
