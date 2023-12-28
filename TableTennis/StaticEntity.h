#pragma once
#include "GameEntity.h"

class StaticEntity :
    public GameEntity
{
public:
    StaticEntity(Vector2f pos, uint32_t entity_id, entity_type entType) : GameEntity(pos, entity_id, entType) {}

    StaticEntity* asStaticEntity() override { return this; }
};

