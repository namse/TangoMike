#include "stdafx.h"
#include "LineCollection.h"
#include "EventManager.h"
#include "XMLBackup.h"

LineCollection::LineCollection()
	:bitmap_line(nullptr), pointBrush_feel_(nullptr), pointBrush_work_(nullptr)
	, lightballTiming(0.f)
{
	didDrawBackground = false;
	EventManager::GetInstance()->AddEventListener(EVENT_VOTE_COMPLETE, this);
	InitLinePoints();
	LineLoadFromBackup();
}


LineCollection::~LineCollection()
{
	didDrawBackground = false;
	for (auto& object : lines_)
	{
		delete object;
	}
}

void LineCollection::Update(float dTime)
{
	Component::Update(dTime);
	// On Light Ball
	lightballTiming += dTime;
	if (lightballTiming > LIGHT_BALL_PERIOD)
	{
		std::vector<Line*> lineOn;
		for (auto line : lines_)
		{
			if (line->IsFocus() == true)
			{
				lineOn.push_back(line);
			}
		}
		if (lineOn.empty() == false)
		{
			int index = rand() % lineOn.size();

			if (lineOn[index]->IsLightBallOn() == false)
			{
				lineOn[index]->LightBallOn();
			}
		}
		lightballTiming = 0.f;
	}
}

void LineCollection::Render()
{
	HRESULT hr;
	if (pCompatibleRenderTarget == nullptr)
	{
		InitLineBrushes();
		hr = m_pBackBufferRT->CreateCompatibleRenderTarget(
			D2D1::SizeF(1024.f, 768.f),
			&pCompatibleRenderTarget
			);
	}
	if (didDrawBackground == false)
	{
		pCompatibleRenderTarget->Release();
		hr = m_pBackBufferRT->CreateCompatibleRenderTarget(
			D2D1::SizeF(1024.f, 768.f),
			&pCompatibleRenderTarget
			);
	}
	Component::Render();
	if (didDrawBackground == false)
	{
		didDrawBackground = true;
	}

	m_pBackBufferRT->BeginDraw();

	m_pBackBufferRT->SetTransform(D2D1::Matrix3x2F::Identity());

	
	// Draw Background lines
	ID2D1Bitmap *pGridBitmap = NULL;
	hr = pCompatibleRenderTarget->GetBitmap(&pGridBitmap);

	// Choose the tiling mode for the bitmap brush.
	D2D1_BITMAP_BRUSH_PROPERTIES brushProperties =
		D2D1::BitmapBrushProperties(D2D1_EXTEND_MODE_WRAP, D2D1_EXTEND_MODE_WRAP);
	ID2D1BitmapBrush* pBitmapBrush;
	// Create the bitmap brush.
	hr = m_pBackBufferRT->CreateBitmapBrush(pGridBitmap, brushProperties, &pBitmapBrush);

	pGridBitmap->Release();

	m_pBackBufferRT->FillRectangle(
		D2D1::RectF(0.0f, 0.0f, 1024.f, 768.f),
		pBitmapBrush
		);


	// Draw Point

	m_pBackBufferRT->SetTransform(matrix_);
	if (pointBrush_feel_ == nullptr)
		m_pBackBufferRT->CreateSolidColorBrush(COLOR_FEEL, &pointBrush_feel_);
	if (pointBrush_work_ == nullptr)
		m_pBackBufferRT->CreateSolidColorBrush(COLOR_WORK, &pointBrush_work_);

	for (int i = 0; i < Relationship::GetInstance()->GetFeels().size(); i++)
	{
		auto linePoint = linePoints_[i];
		auto ellipse = D2D1::Ellipse(linePoint, POINT_RADIUS_UNFOCUS, POINT_RADIUS_UNFOCUS);
		m_pBackBufferRT->FillEllipse(ellipse, pointBrush_feel_);
	}
	
	for (int i = Relationship::GetInstance()->GetFeels().size(); 
		i < Relationship::GetInstance()->GetFeels().size() + Relationship::GetInstance()->GetWorks().size(); i++)
	{
		auto linePoint = linePoints_[i];
		auto ellipse = D2D1::Ellipse(linePoint, POINT_RADIUS_UNFOCUS, POINT_RADIUS_UNFOCUS);
		m_pBackBufferRT->FillEllipse(ellipse, pointBrush_work_);
	}
	hr = m_pBackBufferRT->EndDraw();

	pBitmapBrush->Release();
}

void LineCollection::InitLinePoints()
{
	int totalCount = Relationship::GetInstance()->GetFeels().size() + Relationship::GetInstance()->GetWorks().size();
	float dAngle = M_PI * 2.f / (float)totalCount;
	for (int i = 0; i < totalCount; i++)
	{
		float angle = 0.f;
		if ( i < FEEL_COUNT ) // is Feel's Point
			angle = M_PI * 2.f * 0.75f - (dAngle * (i));
		else
			angle = M_PI * 2.f * 0.75f + (dAngle * (i - FEEL_COUNT + 1.f));
			
		linePoints_.push_back(D2D1::Point2F(cos(angle), sin(angle)) * CIRCLE_RADIUS_TO_POINT);
	}
}

void LineCollection::Notify(EventHeader* event)
{
	switch (event->event_type_)
	{
	case EVENT_VOTE_COMPLETE:
	{
		Event::SelectEvent* recvEvent = (Event::SelectEvent*)event;

		for (int i = 1; i < recvEvent->objectLength; i++)
		{
			MakeLine(recvEvent->object[0], recvEvent->object[i]);
		}
		didDrawBackground = false;
	}break;
	default:
		break;
	}
}

void LineCollection::MakeLine(int feelId, int workId)
{
	if (lines_.size() > MAX_LINE_COUNT)
	{
		Line* frontLine = lines_.front();
		RemoveLine(frontLine);
	}
	Line* line = new Line(&linePoints_[feelId], &linePoints_ [workId], feelId, workId);
	lines_.push_back(line);

	AddChild(line);
}



void LineCollection::RemoveLine(Line* line)
{
	lines_.remove(line);
	this->RemoveChild(line);
	delete line;
}

void LineCollection::InitLineBrushes()
{

	HRESULT hr = m_pBackBufferRT->CreateGradientStopCollection(
			lineStops,
			ARRAYSIZE(lineStops),
			&lineStopCollection_
			);
	hr = m_pBackBufferRT->CreateGradientStopCollection(
		lineStops_background,
		ARRAYSIZE(lineStops_background),
		&lineStopCollection_background
		);
	
	for (int i = 0; i < FEEL_COUNT; i++)
	{
		for (int l = 0; l < WORK_COUNT; l++)
		{
			hr = m_pBackBufferRT->CreateLinearGradientBrush(
				D2D1::LinearGradientBrushProperties(
				linePoints_[i],
				linePoints_[l + FEEL_COUNT]),
				D2D1::BrushProperties(),
				lineStopCollection_,
				&linebrush_[i][l]
				);
			hr = m_pBackBufferRT->CreateLinearGradientBrush(
				D2D1::LinearGradientBrushProperties(
				linePoints_[i],
				linePoints_[l + FEEL_COUNT]),
				D2D1::BrushProperties(),
				lineStopCollection_background,
				&linebrush_background[i][l]
				);
		}
	}

	
}

void LineCollection::LineLoadFromBackup()
{
	auto lines = XMLBackup::GetInstance()->LoadLines();
	for (auto& line : lines)
	{
		MakeLine(line.first, line.second);
	}
}


