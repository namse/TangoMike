#pragma once
#include"stdafx.h"
#include "Object.h"
#include "Feel.h"
#include "Work.h"
#include "EventListener.h"
class Relationship : public EventListener
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

	std::vector<Feel*> GetFeels()		{ return feels_; }
	std::vector<Work*> GetWorks()		{ return works_; }

	virtual void Notify(EventHeader* event);

	Object* FindObjectById(int id);

	Feel* FindFeelById(int id)
	{
		return (Feel*)FindObjectById(id);
	}

	Work* FindWorkById(int id)
	{
		return (Work*)FindObjectById(id);
	}

	int GetCount(std::pair<Feel*, Work*> pair)
	{
		return count_.find(pair)->second;
	}

private:
	Relationship();
	~Relationship();

private:
	static Relationship* pInstance_;
	std::map<std::pair<Feel*, Work*>, int> count_;
	std::vector<Feel*> feels_;
	std::vector<Work*> works_;


	std::map<Feel*, int> pickCount_feel;
	std::map<Work*, int> pickCount_work;

	int totalUser;

	Feel* tp_feel;
	int tp_feel_count;
	Work* tp_work;
	int tp_work_count;
	std::pair<Feel*, Work*> tc_com;
	int tc_com_count ;

};

