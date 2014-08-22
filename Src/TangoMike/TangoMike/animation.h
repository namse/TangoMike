template <typename T>
class Animation
{
public:
	Animation(T* object)
	{
		object_ = object;
		isAnimating = false;
	}

	~Animation()
	{

	}

	void DoAnimate(T nextObject, float duration)
	{
		prevObject_ = *object_;
		nextObject_ = nextObject;
		isAnimating = true;
		duration_ = duration;
		currentTime_ = 0.f;
	}

	void OnAnimate(float dTime)
	{
		if (isAnimating == true)
		{
			currentTime_ += dTime;
			if (currentTime_ >= duration_)
			{
				// end of Animate;
				OnEnd();
			}
			else
			{
				*object_ = prevObject_ + (nextObject_ - prevObject_) * (currentTime_ / duration_);
			}
		}
	}

private:
	void OnEnd()
	{
		currentTime_ = duration_;
		isAnimating = false;
		*object_ = nextObject_;
	}

private:
	T* object_;
	bool isAnimating;
	float duration_;
	float currentTime_;
	T prevObject_;
	T nextObject_;
};