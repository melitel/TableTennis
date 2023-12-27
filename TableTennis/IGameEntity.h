#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Math.h"

class MovableEntity;
class StaticEntity;

class IGameEntity
{
public:

	virtual void initialize() = 0;
	virtual void draw(std::unique_ptr<sf::RenderWindow>& window) = 0;
	virtual void onHit(const Vector2f& normal) = 0;
	virtual MovableEntity* asMovableEntity() { return nullptr; }
	virtual StaticEntity* asStaticEntity() { return nullptr; }
	virtual void reset(const Vector2f& vel) = 0;
	virtual ~IGameEntity() = default;
};

