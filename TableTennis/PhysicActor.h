#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<variant>
#include<vector>
#include "Sector.h"
#include "Math.h"

class PhysicsScene;
class GameEntity;

class PhysicActor
{
public:

	PhysicActor(std::weak_ptr<PhysicsScene> scene, std::weak_ptr<GameEntity> owner) : m_scene(scene), m_owner(owner) {}

	enum motion_type {
		kinematic,
		dynamic,
		immovable
	};

	enum shape_type {
		rectangle,
		circle		
	};

	struct Rectangle {		
		float width;
		float height;
		BoundingBox calculate_bbox() const {
			return BoundingBox(Vector2f(0.f, 0.f), Vector2f(width, height));
		}
	};

	struct Circle {
		float radius;
		BoundingBox calculate_bbox() const {
			return BoundingBox(Vector2f(0.f, 0.f), Vector2f(2.f*radius, 2.f * radius));
		}
	};

	void initialize(
		sf::Vector2f pos,
		sf::Vector2f vel,
		motion_type type_of_motion,
		shape_type shape,
		const std::variant<sf::Vector2f, float>& size
	);

	void set_position(const sf::Vector2f& pos) 
	{
		m_position = pos;
	};

	void set_velocity(const sf::Vector2f& vel)
	{
		m_velocity = vel;
	};

	const sf::Vector2f& get_position() const
	{
		return m_position;
	};

	const sf::Vector2f& get_velocity() const
	{
		return m_velocity;
	};

	const motion_type& get_motion_type() const {
		return m_motion_type;
	}

	shape_type get_shape() {	
		return m_shape_type;
	}

	BoundingBox get_bounds() const;
	void set_sector(int sector_id) {
		m_sectors.push_back(sector_id);
	}	

private:
	std::weak_ptr<PhysicsScene> m_scene;
	std::weak_ptr<GameEntity> m_owner;
	motion_type m_motion_type;
	std::variant <Rectangle, Circle> m_shapeVariant;
	shape_type m_shape_type;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;	
	std::vector<int> m_sectors;
};

