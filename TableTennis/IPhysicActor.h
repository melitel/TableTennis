#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Math.h"
#include<variant>
#include<vector>

class BoundingBox;
class IGameEntity;

class IPhysicActor
{
public:

	virtual void set_position(const Vector2f& pos) = 0;
	virtual const Vector2f& get_position() const = 0;
	virtual BoundingBox get_bounds() const = 0;
	virtual BoundingBox get_bounds(const Vector2f& pos) const = 0;
	virtual void set_sector(int sector_id) = 0;
	virtual Vector2f get_hit_normal() const = 0;
	virtual const std::weak_ptr<IGameEntity>& get_owner() const = 0;

	virtual ~IPhysicActor() = default;
};

