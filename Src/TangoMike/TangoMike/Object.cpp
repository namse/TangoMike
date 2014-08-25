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

	name_WithoutSpace = name_;
	englishName_WithoutSpace = englishName_;
	//std::replace(name_.begin(), name_.end(), L"_", L" ");
	while (name_.find(L"_") != std::string::npos)
		name_.replace(name_.find(L"_"), 1, L" ");
	while (englishName_.find(L"_") != std::string::npos)
		englishName_.replace(englishName_.find(L"_"), 1, L" ");

	name_forXML = name_WithoutSpace;

	while (name_forXML.find(L"#") != std::string::npos)
		name_forXML.replace(name_forXML.find(L"#"), 1, L"");
	while (name_forXML.find(L"!") != std::string::npos)
		name_forXML.replace(name_forXML.find(L"!"), 1, L"");
}


Object::~Object()
{
}

std::wstring Object::GetNameOnXML()
{
	return name_forXML;
}
