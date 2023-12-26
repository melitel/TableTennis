#include "PhysicActor.h"
#include "PhysicsScene.h"
#include <cassert>

BoundingBox PhysicActor::get_bounds() const
{
	if (m_shape_type == rectangle) {
		Rectangle rect = std::get<Rectangle>(m_shapeVariant);
		return rect.calculate_bbox().offset2world(m_position);
	}
	else if (m_shape_type == circle) {
		Circle circle = std::get<Circle>(m_shapeVariant);
		return circle.calculate_bbox().offset2world(m_position);
	}
	else {
		assert(false);
		return BoundingBox();
	}
}

BoundingBox PhysicActor::get_bounds(const Vector2f& pos) const
{
	if (m_shape_type == rectangle) {
		Rectangle rect = std::get<Rectangle>(m_shapeVariant);
		return rect.calculate_bbox().offset2world(pos);
	}
	else if (m_shape_type == circle) {
		Circle circle = std::get<Circle>(m_shapeVariant);
		return circle.calculate_bbox().offset2world(pos);
	}
	else {
		return BoundingBox();
	}
}
