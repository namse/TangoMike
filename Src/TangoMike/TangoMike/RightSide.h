#pragma once
#include "stdafx.h"
#include "Component.h"
#include "WordSpriteCollection.h"
#include "LineCollection.h"
class RightSide :
	public Component
{
public:
	RightSide();
	~RightSide();


	void Render();
	void Update(float dTime);

	void SetArrange();
	void SetFocus();
	void SetIdle();

	void OffFocus();
	void OffShuffle();

	virtual void Notify(EventHeader* event);

private:
	void CleanFocus();
	
private:
	WordSpriteCollection wordSpriteCollection_;
	LineCollection lineCollection_;
	std::vector<Object*> SelectdObjects_;
};

