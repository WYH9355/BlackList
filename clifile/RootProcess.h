#ifndef _ROOTPROCESS_H
#define _ROOTPROCESS_H

#include "Selecter.h"
#include "Server.h"
#include "MyDefine.h"
#include <json/json.h>
#include <pthread.h>

//主机运行类
class RootProcess
{
	public:

		//主机运行
		void run();

		//界面显示
		void put();

		//增加操作
		bool Insert();
		//删除操作
		bool Delete();
		//查询操作
		bool Select();
		//更新操作
		bool Update();



		//接收线程
		bool RecvServerPthreadStart();

		static void* RecvWork(void* arg);

		//采集机线程
		void SelecterPtreadStart();

		static void* SelecterWork(void* arg);





		//检查增加
		void CheckInsert();
		//检查删除
		void CheckDelete();
		//检查查询
		void CheckSeleck();
		//检查更新
		void CheckUpdate();

		//退出
		void ExitPro();


	private:

};



#endif
