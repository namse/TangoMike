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

	
	void MakeLine(int feelId, int workId);
	void RemoveLine(Line* line);
	void LineLoadFromBackup();

private:
	void InitLinePoints();
	void InitLineBrushes();

private:
	std::list<Line*> lines_;
	std::vector<D2D_POINT_2F> linePoints_;

	ID2D1SolidColorBrush* pointBrush_work_;
	ID2D1SolidColorBrush* pointBrush_feel_;
	
	ID2D1Bitmap * bitmap_line;

	float lightballTiming;

};

