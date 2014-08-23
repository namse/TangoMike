#pragma once
#include "stdafx.h"
#include "Component.h"
#include "TotalCount.h"
#include "MainTitle.h"

class LeftSide : public Component
{
public:
	LeftSide();
	~LeftSide();

	void Update(float dTime);
	void Render();

private:
	MainTitle mainTitle_;
	TotalCount totalCount_;
};

