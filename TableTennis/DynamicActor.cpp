#include "DynamicActor.h"
#include <cassert>

void DynamicActor::initialize(
	Vector2f pos, Vector2f vel, bool isPureDynamic, shape_type shape,
	const std::variant<Vector2f, float>& size)
{
	m_position = pos;
	m_velocity = vel;
	m_PureDynamic = isPureDynamic;
	m_shape_type = shape;

	if (m_shape_type == rectangle) {
		Vector2f rectangle_size = std::get<Vector2f>(size);
		m_shapeVariant = Rectangle{ rectangle_size.x , rectangle_size.y };
	}
	else if (m_shape_type == circle) {
		float circle_radius = std::get<float>(size);
		m_shapeVariant = Circle{ circle_radius };
	}
	else {
		assert(false);
	}
}