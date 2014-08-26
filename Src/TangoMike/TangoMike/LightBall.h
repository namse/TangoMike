#pragma once
#include "Component.h"
class LightBall :
	public Component
{
public:

	LightBall::LightBall();
	LightBall(D2D1_POINT_2F ps, D2D1_POINT_2F pb, D2D1_POINT_2F pe);
	~LightBall();

	void Render();
	void Update(float dTime);

	bool IsMovingDone(){ return isMovingDone_; }

	void SetMoveOn(bool isMove){
		Reset();
		isMovingDone_ = !isMove;
	}
	void Reset();
private:
	D2D_POINT_2F point_start;
	D2D_POINT_2F point_bezier;
	D2D_POINT_2F point_end;

	float radius_;
	float radiusAnimationTimer_;
	
	float currentTime;

	ID2D1GradientStopCollection* stops_;
	ID2D1RadialGradientBrush* brush_;


	float velocity;
	float d;

	bool isMovingDone_;
	
};

