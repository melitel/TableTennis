#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<variant>
#include<vector>

class BoundingBox;

class IPhysicActor
{
public:

	virtual void set_position(const sf::Vector2f& pos) = 0;
	virtual const sf::Vector2f& get_position() const = 0;
	virtual BoundingBox get_bounds() const = 0;
	virtual void set_sector(int sector_id) = 0;

	virtual ~IPhysicActor() = default;
};

