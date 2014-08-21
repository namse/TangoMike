#pragma once
#include "Object.h"
#include "stdafx.h"
class Work : public Object
{
public:
	Work(int id, std::wstring name, float width, std::wstring englishName, float englishWidth);
	~Work();
};

