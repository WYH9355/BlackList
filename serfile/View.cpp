#include "View.h"


//执行用户注册并返回成功与否
void InsertRootListView::process(int fd,Json::Value &val)
{
	Json::Value data;
	data[FD] = HOSTFD;

	if ( DataBase::getDataBase()->insertRootList(val) )
		data[REASON] = YES;
	else
		data[REASON] = NO;

	Client::getClient()->sendClient(fd,data.toStyledString());
}

//执行用户登录时查询并返回成功与否
void SelectRootListView::process(int fd,Json::Value &val)
{
	Json::Value data;
	data[FD] = HOSTFD;

	if ( DataBase::getDataBase()->selectRootList(val) )
		data[REASON] = YES;
	else
		data[REASON] = NO;

	Client::getClient()->sendClient(fd,data.toStyledString());
}



//执行黑名单用户注册并返回成功与否
void InsertBlackListView::process(int fd,Json::Value &val)
{
	Json::Value data;
	data[FD] = HOSTFD;

	if ( DataBase::getDataBase()->insertBlackList(val) )
		data[REASON] = YES;
	else
		data[REASON] = NO;

	Client::getClient()->sendClient(fd,data.toStyledString());
}

//执行黑名单用户查询并返回成功与否
void SelectBlackListView::process(int fd,Json::Value &val)
{
	Json::Value data;
	data[FD] = HOSTFD;

	if ( DataBase::getDataBase()->selectBlackList(val) )
		data[REASON] = YES;
	else
		data[REASON] = NO;

	Client::getClient()->sendClient(fd,data.toStyledString());
}

//执行黑名单用户的删除并返回成功与否
void DeleteBlackListView::process(int fd,Json::Value &val)
{
	Json::Value data;
	data[FD] = HOSTFD;

	if ( DataBase::getDataBase()->deleteBlackList(val) )
		data[REASON] = YES;
	else
		data[REASON] = NO;

	Client::getClient()->sendClient(fd,data.toStyledString());
}

//执行黑名单用户的更新并返回成功与否
void UpdataBlackListView::process(int fd,Json::Value &val)
{
	Json::Value data;
	data[FD] = HOSTFD;

	if ( DataBase::getDataBase()->updataBlackList(val) )
		data[REASON] = YES;
	else
		data[REASON] = NO;

	Client::getClient()->sendClient(fd,data.toStyledString());
}

