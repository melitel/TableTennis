#pragma once
#include "PhysicActor.h"

class StaticActor :
    public PhysicActor
{
public:

	void initialize(sf::Vector2f pos,
		const std::variant<sf::Vector2f, float>& size);
};

