#include "PhysicActor.h"
#include <cassert>
#include "PhysicsScene.h"

void PhysicActor::initialize(
	sf::Vector2f pos, sf::Vector2f vel, motion_type type_of_motion, shape_type shape,
	const std::variant<sf::Vector2f, float>& size)
{
	m_position = pos;
	m_velocity = vel;
	m_motion_type = type_of_motion;
	m_shape_type = shape;

	if (m_shape_type == rectangle) {
		sf::Vector2f rectangle_size = std::get<sf::Vector2f>(size);
		m_shapeVariant = Rectangle{ rectangle_size.x , rectangle_size.y};		
	}
	else if (m_shape_type == circle) {
		float circle_radius = std::get<float>(size);
		m_shapeVariant = Circle { circle_radius };
	}
	else {
		assert(false);
	}
}

BoundingBox PhysicActor::get_bounds() const
{
	if (m_shape_type == rectangle) {
		Rectangle rect = std::get<Rectangle>(m_shapeVariant);
		return rect.calculate_bbox().offset2world(Vector2f(m_position.x, m_position.y));
	}
	else if (m_shape_type == circle) {
		Circle circle = std::get<Circle>(m_shapeVariant);
		return circle.calculate_bbox().offset2world(Vector2f(m_position.x, m_position.y));
	}
	else {
		return BoundingBox();
	}
}
