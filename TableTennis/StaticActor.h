#pragma once
#include "PhysicActor.h"

class StaticActor :
    public PhysicActor
{
public:

	StaticActor(std::weak_ptr<PhysicsScene> scene, std::weak_ptr<IGameEntity> owner) : PhysicActor(scene, owner) {}

	void initialize(Vector2f pos,
		const std::variant<Vector2f, float>& size);
};

