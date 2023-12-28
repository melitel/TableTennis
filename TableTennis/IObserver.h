#pragma once
#include "Math.h"

class Ball;

class IObserver
{
public:
	virtual void ballOut(Ball* ball, const Vector2f& vel, int player_score) = 0;
	virtual ~IObserver() {};
};

