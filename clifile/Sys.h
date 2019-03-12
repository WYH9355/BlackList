#ifndef _SYS_H
#define _SYS_H
#include "RootProcess.h"
#include "Server.h"
#include "MyDefine.h"
#include <stdio.h>
#include <json/json.h>
#include <fcntl.h>
#include <termios.h>




//界面类
class Sys
{
	public:

		//构造
		Sys();

		//析构
		~Sys();

		//界面清单
		void put();

		//界面运行
		void run();

		//登录
		bool Login();

		//检查登录
		void CheckLogin();

		//注册
		bool Register();

		//检查注册
		void CheckRegister();

		//退出
		void ExitSys();

		//输入回显去除
		void DeleteShow(struct termios &ts);

		//输入回显增加
		void AddShow(struct termios &ts);

	private:

		RootProcess *		_rootprocess; //主机运行对象
};


#endif
