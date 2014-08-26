#pragma once
#include "stdafx.h"
#include "EventListener.h"
class XMLBackup : public EventListener
{

public:
	static XMLBackup* GetInstance()
	{
		if (pInstance_ == nullptr)
		{
			pInstance_ = new XMLBackup;
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

	virtual void Notify(EventHeader* event);
	void LoadData();
	void Backup();
	pugi::xml_document* GetXML() {
		return &xml_doc;
	}
	std::list<std::pair<int, int>> LoadLines();
private:
	XMLBackup();
	~XMLBackup();

	void MakeFile();

private:
	static XMLBackup* pInstance_;


	pugi::xml_document xml_doc;

	int circular_index;
};

inline bool IsFileExist(const std::wstring& name) {
	std::ifstream f(name.c_str());
	if (f.good()) {
		f.close();
		return true;
	}
	else {
		f.close();
		return false;
	}
}
