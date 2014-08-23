#pragma once
#include "stdafx.h"
#include "Component.h"
#include "Relationship.h"
#include "Line.h"
class LineCollection :
	public Component
{
public:
	LineCollection();
	~LineCollection();

	void Update(float dTime);
	void Render();

	virtual void Notify(EventHeader* event);

	void InitLinePoints();

	void MakeLine(int feelId, int workId);
private:
	std::list<Line*> lines_;
	std::vector<D2D_POINT_2F> linePoints_;

	ID2D1SolidColorBrush* pointBrush_work_;
	ID2D1SolidColorBrush* pointBrush_feel_;


};

