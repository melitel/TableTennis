#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Math.h"

class MovableEntity;
class StaticEntity;
//class Observer;

class IGameEntity
{
public:
	enum entity_type {
		wall,
		player,
		ball
	};

	virtual void initialize() = 0;
	virtual void draw(std::unique_ptr<sf::RenderWindow>& window) = 0;
	virtual void onHit(const Vector2f& normal, const std::shared_ptr<IGameEntity>& entity_hit) = 0;
	virtual MovableEntity* asMovableEntity() { return nullptr; }
	virtual StaticEntity* asStaticEntity() { return nullptr; }
	virtual void reset(const Vector2f& vel) = 0;
	virtual entity_type get_entity_type() = 0;
	virtual ~IGameEntity() = default;
};

