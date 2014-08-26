#pragma once
#include "stdafx.h"
#include "Component.h"
#include "LightBall.h"
class Line :
	public Component
{
public:
	Line(D2D1_POINT_2F* point1, D2D1_POINT_2F* point2, int feelID, int workID);
	~Line();

	void Render();
	void Update(float dTime);

	void LightBallOn();
	bool IsLightBallOn(){
		return !(lightBall_->IsMovingDone());
	}

	bool IsFocus(){
		return (isFocus[feelID_] == true && isFocus[workID_] == true);
	}
private:
	void CalcBezier();
private:
	int feelID_, workID_;
	//bool didDrawBackground;
	D2D1_POINT_2F * point1_;
	D2D1_POINT_2F * point2_;

	D2D1_POINT_2F point_bezier_;

	ID2D1PathGeometry* geometry_;
	ID2D1GeometrySink* sink_;


	LightBall* lightBall_;

	float lineThickness;
	Animation<float> lineThicknessAnimation;
	bool isFirstTimeFromFocus;
	bool isFirstTimeFromUnFocus;

	float timeForFadeOut;
};