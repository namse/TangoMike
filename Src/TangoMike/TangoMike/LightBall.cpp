#include "stdafx.h"
#include "LightBall.h"



LightBall::LightBall()
{
}

LightBall::LightBall(D2D1_POINT_2F ps, D2D1_POINT_2F pb, D2D1_POINT_2F pe)
	:Component(), point_start(ps), point_bezier(pb), point_end(pe), brush_(nullptr), stops_(nullptr), currentTime(0.f)
	, d(0.f), isMovingDone_(true), radius_(0.f)
{

}

LightBall::~LightBall()
{
	if (stops_ != nullptr)
	{
		stops_->Release();
	}
	if (brush_ != nullptr)
	{
		brush_->Release();
	}

}

void LightBall::Render()
{
	if (isMovingDone_ == false)
	{
		Component::Render();
		HRESULT hr = S_OK;
		if (stops_ == nullptr)
		{
			if (hr == S_OK){
				hr = m_pBackBufferRT->CreateGradientStopCollection(
					lightBallStops,
					ARRAYSIZE(lightBallStops),
					&stops_
					);
			}
		}

		if (brush_ == nullptr)
		{
			if (hr == S_OK){
				hr = m_pBackBufferRT->CreateRadialGradientBrush(
					D2D1::RadialGradientBrushProperties(
					D2D1::Point2F(0, 0),
					D2D1::Point2F(0, 0),
					LIGHT_BALL_MAX_RADIUS,
					LIGHT_BALL_MAX_RADIUS),
					D2D1::BrushProperties(),
					stops_,
					&brush_
					);
			}
		}

		m_pBackBufferRT->BeginDraw();
		m_pBackBufferRT->SetTransform(matrix_);
		m_pBackBufferRT->FillEllipse(D2D1::Ellipse(D2D1::Point2F(0.f, 0.f), radius_, radius_), brush_);
		hr = m_pBackBufferRT->EndDraw();
	}
}

void LightBall::Update(float dTime)
{
	Component::Update(dTime);
	if (isMovingDone_ == false)
	{
		currentTime += dTime;

		float T = distance(&point_start, &point_end) / 70.f;
		float vy = 360.f / T;
		float a = 720.f / (T*T);
		float velocity = 10.f +  vy * currentTime - 0.5 * a * (currentTime * currentTime);


		d += velocity * dTime;
		float s = d;
		

		float p = s / (distance(&point_start, &point_end));
		D2D_POINT_2F position = (point_start*(1.f - p) + point_bezier * p) * (1.f - p) + (point_bezier * (1.f - p) + point_end * p) * p;


		// for radius
		if (currentTime < T*0.2f)
		{
			radius_ = LIGHT_BALL_MAX_RADIUS * currentTime / (T*0.2f);
		}
		else if (currentTime > T*0.8f && currentTime < T)
		{
			radius_ = LIGHT_BALL_MAX_RADIUS * (T - currentTime) / (T*0.2f);
		}
		else if (currentTime <= T)
			radius_ = LIGHT_BALL_MAX_RADIUS;
		else
			radius_ = 0.f;

		SetPosition(position);

		if (currentTime > T)
			isMovingDone_ = true;
	}
}

void LightBall::Reset()
{
	currentTime = 0.f;
	d = 0.f;
}


