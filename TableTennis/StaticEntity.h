#pragma once
#include "GameEntity.h"

class StaticEntity :
    public GameEntity
{
public:
    StaticEntity(Vector2f pos, uint32_t entity_id) : GameEntity(pos, entity_id) {}

    StaticEntity* asStaticEntity() override { return this; }
};

