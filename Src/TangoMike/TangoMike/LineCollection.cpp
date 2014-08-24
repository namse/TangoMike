#include "stdafx.h"
#include "LineCollection.h"
#include "EventManager.h"

LineCollection::LineCollection()
{
	//SetCenter(D2D1::Point2F(CIRCLE_RADIUS_TO_POINT, CIRCLE_RADIUS_TO_POINT));
	//SetPosition(CIRCLE_CENTER_POSITION);


	EventManager::GetInstance()->AddEventListener(EVENT_VOTE_COMPLETE, this);


	InitLinePoints();
	/*
	for (int i = 0; i < 3; i++)
	{
		int a = rand() % Relationship::GetInstance()->GetFeels().size();
		for (int l = 0; l < 2; l++)
		{
			int b = rand() % Relationship::GetInstance()->GetWorks().size();
			b += Relationship::GetInstance()->GetFeels().size();
			MakeLine(a, b);
		}
	}*/
}


LineCollection::~LineCollection()
{
	for (auto& object : lines_)
	{
		delete object;
	}
}

void LineCollection::Update(float dTime)
{
	Component::Update(dTime);
}

void LineCollection::Render()
{
	Component::Render();
	m_pBackBufferRT->BeginDraw();

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
	
	HRESULT hr = m_pBackBufferRT->EndDraw();
}

void LineCollection::InitLinePoints()
{
	int totalCount = Relationship::GetInstance()->GetFeels().size() + Relationship::GetInstance()->GetWorks().size();
	float dAngle = M_PI * 2.f / (float)totalCount;
	for (int i = 0; i < totalCount; i++)
	{
		float angle = 0.f;
		if ( i < FEEL_COUNT ) // is Feel's Point
			angle = M_PI * 2.f * 0.75f - (dAngle * (i + 0.5f));
		else
			angle = M_PI * 2.f * 0.75f + (dAngle * (i - FEEL_COUNT + 0.5f));
			
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
	}break;
	default:
		break;
	}
}

void LineCollection::MakeLine(int feelId, int workId)
{
	//Line* line = new Line(&linePoints_[feelId - FEEL_COUNT + 1], &linePoints_[FEEL_COUNT + WORK_COUNT -  workId]);
	Line* line = new Line(&linePoints_[feelId], &linePoints_ [workId]);
	AddChild(line);
}
