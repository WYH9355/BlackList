#include "Model.h"


void Model::insertPair(int type,View* p)
{
	_map.insert(std::make_pair(type,p));
}

View* Model::operator[](int type)
{
	return _map[type];
}
