#include "stdafx.h"
#include "LeftSide.h"


LeftSide::LeftSide()
{
	AddChild(&mainTitle_);
	AddChild(&totalCount_);
}


LeftSide::~LeftSide()
{
}

void LeftSide::Update(float dTime)
{
	Component::Update(dTime);
}

void LeftSide::Render()
{
	Component::Render();
}
