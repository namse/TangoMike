#include "stdafx.h"
#include "Line.h"


Line::Line(D2D1_POINT_2F* point1, D2D1_POINT_2F* point2, int feelID, int workID)
	:point1_(point1), point2_(point2), geometry_(nullptr)
	, feelID_(feelID), workID_(workID), lineThickness(0.f), lineThicknessAnimation(&lineThickness)
	, isFirstTimeFromFocus(true)
{
	CalcBezier();

	if (rand()%2 == 0)
		lightBall_ = new LightBall(*point1_, point_bezier_, *point2_);
	else
		lightBall_ = new LightBall(*point2_, point_bezier_, *point1_);

	AddChild(lightBall_);
}

void Line::CalcBezier()
{
	float h = (((float)rand() / (float)RAND_MAX) * 0.4f) - 0.2f;
	float t = (((float)rand() / (float)RAND_MAX) * 1.6f) - 0.3f;

	D2D1_POINT_2F vec = *point2_ - *point1_;

	D2D1_POINT_2F vec_horizen = vec * t;
	D2D1_POINT_2F vec_vertical;
	vec_vertical.x = -vec.y;
	vec_vertical.y = vec.x;
	vec_vertical = vec_vertical * h;

	point_bezier_ = vec_vertical + vec_horizen + *point1_;
}

Line::~Line()
{
}

void Line::Render()
{
	Component::Render();
	HRESULT hr;
	if (geometry_ == nullptr)
	{
		hr = m_pD2DFactory->CreatePathGeometry(&geometry_);

		hr = geometry_->Open(&sink_);

		sink_->BeginFigure(
			D2D1::Point2F(point1_->x, point1_->y),
			D2D1_FIGURE_BEGIN_HOLLOW);

		float radius, angle;
		float length = sqrt(pow(point1_->x - point2_->x, 2) + pow(point1_->y - point2_->y, 2));
		float factor = 0.5f;//(float)(std::rand() % 10) / 100.f;
		radius = length * factor;
		angle = 1.5f;//(float)((float)std::rand() / (float)RAND_MAX) * M_PI * 2.0f;

		sink_->AddBezier(
			D2D1::BezierSegment(
			*point1_,
			point_bezier_, //D2D1::Point2F( point1_->x + radius * cos(angle), point1_->y + radius * sin(angle)),
			*point2_)
			);

		sink_->EndFigure(D2D1_FIGURE_END_OPEN);
		hr = sink_->Close();
	}
	if (didDrawBackground == false)
	{
		pCompatibleRenderTarget->BeginDraw();
		pCompatibleRenderTarget->SetTransform(matrix_);
		pCompatibleRenderTarget->DrawGeometry(geometry_, GetLineBrush_Background(feelID_, workID_), LINE_THICKNESS);
		pCompatibleRenderTarget->EndDraw();
		
	}
	if (IsFocus())
	{

	// ÃÖÀûÈ­ : http://msdn.microsoft.com/ko-kr/library/windows/desktop/ee719658(v=vs.85).aspx
	
		m_pBackBufferRT->BeginDraw(); m_pBackBufferRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
		m_pBackBufferRT->SetTransform(matrix_);
		m_pBackBufferRT->DrawGeometry(geometry_,
			GetLineBrush(feelID_, workID_), lineThickness);
		hr = m_pBackBufferRT->EndDraw();

	}
	else
	{
		lightBall_->Reset();

		if (timeForFadeOut > 0.f)
		{
			m_pBackBufferRT->BeginDraw(); m_pBackBufferRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
			m_pBackBufferRT->SetTransform(matrix_);
			m_pBackBufferRT->DrawGeometry(geometry_,
				GetLineBrush(feelID_, workID_), lineThickness);
			hr = m_pBackBufferRT->EndDraw();
		}
	}
}

void Line::Update(float dTime)
{
	Component::Update(dTime);
	lineThicknessAnimation.OnAnimate(dTime);

	
	if (IsFocus() == true)
	{
		if (isFirstTimeFromFocus == true)
		{
			isFirstTimeFromFocus = false;
			lineThicknessAnimation.DoAnimate(LINE_THICKNESS, 0.3f);
			isFirstTimeFromUnFocus = true;
		}
	}
	else{

		isFirstTimeFromFocus = true;
		if (isFirstTimeFromUnFocus)
		{
			lineThicknessAnimation.DoAnimate(0.f, 0.3f);
			timeForFadeOut = 0.3f;
		}
	}

	if (timeForFadeOut > 0.f)
		timeForFadeOut -= dTime;
}

void Line::LightBallOn()
{
	lightBall_->SetMoveOn(true);


}
