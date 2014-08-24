#include "stdafx.h"
#include "Work.h"



Work::Work(int id, std::wstring name, float width, std::wstring englishName, float englishWidth)
	:Object(id, name, width, englishName, englishWidth)
{
}

Work::~Work()
{
}
