#include "stdafx.h"
#include "Component.h"


Component::Component()
	: isVisible_(true),
	matrix_(D2D1::Matrix3x2F::Identity())
{
	scale_.x = 1.f,	scale_.y = 1.f;
}


Component::~Component()
{
}

void Component::Update(float dTime)
{

}

void Component::Render()
{
	matrix_ = D2D1::Matrix3x2F::Identity()
		* D2D1::Matrix3x2F::Translation(center_.x, center_.y)
		* D2D1::Matrix3x2F::Scale(scale_.x, scale_.y)
		* D2D1::Matrix3x2F::Rotation(rotation_)
		* D2D1::Matrix3x2F::Translation(position_.x, position_.y);

	if (parent_)
	{
		matrix_ = matrix_ * parent_->GetMatrix();
	}

	for (const auto& child : childs_)
	{
		if (child->IsVisible() == true)
		{
			child->Render();
		}
	}
}

void Component::AddChild(Component* child)
{
	childs_.push_back(child);
	child->SetParent(this);
}