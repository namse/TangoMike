#pragma once
#include "stdafx.h"
#include "Component.h"
class Line :
	public Component
{
public:
	Line(D2D1_POINT_2F* point1, D2D1_POINT_2F* point2);
	~Line();

	void Render();
	void Update(float dTime);
private:
	D2D1_POINT_2F * point1_;
	D2D1_POINT_2F * point2_;

};

