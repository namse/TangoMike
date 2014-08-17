#pragma once
#include "stdafx.h"
class Object
{
public:
	Object();
	virtual ~Object();

	int GetId(){ return id_; }
	
protected:
	int id_;
	std::string name_;
};