#include "stdafx.h"
#include "Object.h"


Object::Object(int id, std::wstring name, float width, std::wstring englishName, float englishWidth)
	:name_(L""), englishName_(L"")
{
	name_ = name;
	englishName_ = englishName;
	englishWidth_ = englishWidth;
	width_ = width;
	id_ = id;

	//std::replace(name_.begin(), name_.end(), L"_", L" ");
	while (name_.find(L"_") != std::string::npos)
		name_.replace(name_.find(L"_"), 1, L" ");
	while (englishName_.find(L"_") != std::string::npos)
		englishName_.replace(englishName_.find(L"_"), 1, L" ");
}


Object::~Object()
{
}
