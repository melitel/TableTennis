#pragma once
#include "GameEntity.h"


class MovableEntity :
    public GameEntity
{
public:

    MovableEntity(Vector2f pos, uint32_t entity_id) : GameEntity(pos, entity_id) {}

    virtual void update(float delta, float round_time);
    virtual void move(float delta, float round_time);
    MovableEntity* asMovableEntity() override { return this; }

protected:

    Vector2f m_velocity{ 0.f, 0.f };
    float m_speed = 0.f;
};

