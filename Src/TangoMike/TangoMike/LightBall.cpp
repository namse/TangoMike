#include "stdafx.h"
#include "LightBall.h"



LightBall::LightBall()
{
}

LightBall::LightBall(D2D1_POINT_2F ps, D2D1_POINT_2F pb, D2D1_POINT_2F pe)
	:Component(), point_start(ps), point_bezier(pb), point_end(pe), brush_(nullptr), stops_(nullptr), currentTime(0.f)
{

}

LightBall::~LightBall()
{
}

void LightBall::Render()
{
	Component::Render();
	HRESULT hr;
	if (stops_ == nullptr)
	{
		hr = m_pBackBufferRT->CreateGradientStopCollection(
			lightBallStops,
			ARRAYSIZE(lightBallStops),
			&stops_
			);
	}

	if (brush_ == nullptr)
	{
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

	m_pBackBufferRT->BeginDraw();
	m_pBackBufferRT->SetTransform(matrix_);
	m_pBackBufferRT->FillEllipse(D2D1::Ellipse(D2D1::Point2F(0.f, 0.f), radius_, radius_), brush_);
	hr = m_pBackBufferRT->EndDraw();
}

void LightBall::Update(float dTime)
{
	Component::Update(dTime);

	float T = distance(&point_start, &point_end) / 55.f;
	float s;
	currentTime += dTime / 1000.f;

	if (currentTime < T/2.f)
	{
		s = 10.f * currentTime + 90.f / T * currentTime * currentTime;
	}
	else if ( currentTime >= T/2.f && currentTime < T)
	{
		s = (55.f * T / 2.f) 
			+ 100 * (currentTime - T/2.f) - 90.f / T * pow((currentTime - T/2.f), 2.f);
	}
	else if (currentTime >= T)
	{
		s =distance(&point_start, &point_end);
	}

	float p = s / (  distance(&point_start, &point_end));
	D2D_POINT_2F position = (point_start*(1.f - p) + point_bezier * p) * (1.f - p) + (point_bezier * (1.f-p) + point_end * p) * p;

	
	// for radius
	if (currentTime < T*0.2f)
	{
		radius_ = LIGHT_BALL_MAX_RADIUS * currentTime / (T*0.2f);
	}
	else if (currentTime > T*0.8f && currentTime < T)
	{
		radius_ = LIGHT_BALL_MAX_RADIUS * (T-currentTime) / (T*0.2f);
	}
	else
		radius_ = LIGHT_BALL_MAX_RADIUS;


	SetPosition(position);
}


