#pragma once
#include "stdafx.h"
class Object
{
public:
	Object();
	virtual ~Object();

	int GetId(){ return id_; }
	std::wstring GetName() { return name_; }
protected:
	int id_;
	std::wstring name_;
};