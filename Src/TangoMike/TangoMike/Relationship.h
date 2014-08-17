#pragma once
#include"stdafx.h"
#include "Object.h"
#include "Feel.h"
#include "Work.h"
class Relationship
{
public:
	static Relationship* GetInstance()
	{
		if (pInstance_ == nullptr)
		{
			pInstance_ = new Relationship;
		}
		return pInstance_;
	}
	static void FreeInstance()
	{
		if (pInstance_ != nullptr)
		{
			delete pInstance_;
			pInstance_ = nullptr;
		}
	}

	bool LoadDataFromFile(std::string filename);

private:
	Relationship();
	~Relationship();

private:
	static Relationship* pInstance_;
	std::map<std::pair<Feel*, Work*>, int> count_;
	std::vector<Feel*> feels_;
	std::vector<Work*> works_;
};

