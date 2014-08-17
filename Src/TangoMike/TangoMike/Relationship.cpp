#include "stdafx.h"
#include "Relationship.h"

Relationship* Relationship::pInstance_ = nullptr;

Relationship::Relationship()
{
}


Relationship::~Relationship()
{
}

bool Relationship::LoadDataFromFile(std::string filename)
{
	feels_.clear();
	works_.clear();

	std::wifstream ifs(filename);
	ifs.imbue(std::locale("kor"));
	if (ifs.eof())
		return false;

	int feelCount, workCount;
	std::wstring nameTemp;
	ifs >> feelCount >> workCount;
	for (int i = 0; i < feelCount; i++)
	{
		ifs >> nameTemp;
		feels_.push_back(new Feel(nameTemp, feels_.size()));
	}
	for (int i = 0; i < feelCount; i++)
	{
		ifs >> nameTemp;
		works_.push_back(new Work(nameTemp, works_.size()));
	}


	// init count_
	for each (auto& feel in feels_)
	{
		for each (auto& work in works_)
		{
			count_[std::make_pair(feel, work)] = 0;
		}
	}

	return true;
}
