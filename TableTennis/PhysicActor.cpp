#include "PhysicActor.h"
#include "PhysicsScene.h"

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
