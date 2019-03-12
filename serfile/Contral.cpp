#include "Contral.h"


Contral* Contral::_contral = nullptr;

Contral::ContralDelete Contral::_contralDelete;

std::mutex Contral::_mutex;



Contral* Contral::getContral()
{
	if (nullptr == _contral )
	{
		std::lock_guard<std::mutex> lck(_mutex);
		if ( nullptr == _contral )
		{
			_contral = new Contral;
		}
	}
	return _contral;
}


Contral::Contral():_model(new Model)
{
	//用户注册
	_model->insertPair(INSERT,new InsertRootListView);

	//用户查询
	_model->insertPair(SELECT,new SelectRootListView);

	//黑名单注册
	_model->insertPair(INSERT_HOST,new InsertBlackListView);
	//黑名单查询
	_model->insertPair(SELECT_HOST,new SelectBlackListView);
	//黑名单删除
	_model->insertPair(DELETE_HOST,new DeleteBlackListView);
	//黑名单更新
	_model->insertPair(UPDATE_HOST,new UpdataBlackListView);
}


void Contral::process(SHAREDPTR sptr)
{
	Json::Value		val;
	Json::Reader	read;

	//测试语句
	std::cout<<"recv:"<<sptr->second<<std::endl;

	if ( !read.parse(sptr->second.c_str(),val) )
	{
		std::cout<<"解读失败"<<std::endl;
		std::cerr<<"Contral read.parse fail;errno:"<<errno<<std::endl;
		return ;
	}
	(*_model)[val[TYPE].asInt()]->process(sptr->first,val);
}


Contral::~Contral()
{
	if ( _contral )
	{
		delete _model;
	}
}

Contral::ContralDelete::~ContralDelete()
{
	if ( _contral )
	{
		delete _contral;
		_contral = nullptr;
	}
}

