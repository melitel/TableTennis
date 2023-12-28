#pragma once
#include "IObserver.h"

class Observer :
    public IObserver
{
public:
    void ballOut(Ball* ball, const Vector2f& vel, int player_score) override;
};

