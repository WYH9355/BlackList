#ifndef _VIEW_H
#define _VIEW_H


#include "DataBase.h"
#include "Client.h"
#include "MyDefine.h"
#include <json/json.h>

//视图类
class View
{
	public:
		virtual void process(int fd,Json::Value &val) = 0;
};

//主机用户注册
class InsertRootListView : public View
{
	public:
		void process(int fd,Json::Value &val);
};

//主机用户查询
class SelectRootListView : public View
{
	public:
		void process(int fd,Json::Value &val);
};

//黑名单用户插入
class InsertBlackListView : public View
{
	public:
		void process(int fd,Json::Value &val);
};

//黑名单用户查询
class SelectBlackListView : public View
{
	public:
		void process(int fd,Json::Value &val);
};

//黑名单用户删除
class DeleteBlackListView : public View
{
	public:
		void process(int fd,Json::Value &val);
};

//黑名单用户更新
class UpdataBlackListView : public View
{
	public:
		void process(int fd,Json::Value &val);
};



#endif
