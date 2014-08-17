#pragma once
#include "stdafx.h"
class Component
{
public:
	Component();
	virtual ~Component();

	void AddChild(Component* child);
	void RemoveChild(Component* child);

	virtual void Update(float dTime);
	virtual void Render();

	// about Transforms : http://msdn.microsoft.com/en-us/library/windows/desktop/ff684172(v=vs.85).aspx
	void SetPosition(D2D_VECTOR_2F position)	{ position_ = position; }
	void SetCenter(D2D_VECTOR_2F center)		{ center_ = center; }
	void SetRotation(float rotation)				{ rotation_ = rotation; }
	void SetScale(D2D_VECTOR_2F scale)			{ scale_ = scale; }

	D2D_VECTOR_2F GetPosition()					{ return position_; }
	D2D_VECTOR_2F GetCenter()					{ return center_; }
	float GetRotation()								{ return rotation_; }
	D2D_VECTOR_2F GetScale()					{ return scale_; }

	D2D1_MATRIX_3X2_F GetMatrix()				{ return matrix_; }

	bool IsVisible()									{ return isVisible_; }
	void SetVisible(bool isVisible)					{ isVisible_ = isVisible_; }
private:
	Component* parent_;
	std::list<Component*> childs_;
	
	D2D_VECTOR_2F position_;
	D2D_VECTOR_2F center_;
	float rotation_;
	D2D_VECTOR_2F scale_;
	D2D_MATRIX_3X2_F matrix_;

	bool isVisible_;
};

