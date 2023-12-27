#include "StaticActor.h"

void StaticActor::initialize(Vector2f pos, const std::variant<Vector2f, float>& size, const Vector2f& hit_normal)
{
	m_position = pos;
	Vector2f actor_size = std::get<Vector2f>(size);
	m_shapeVariant = Rectangle{ actor_size.x , actor_size.y };
	m_shape_type = shape_type::rectangle;
	m_hit_normal = hit_normal;
}
