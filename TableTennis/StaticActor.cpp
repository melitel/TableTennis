#include "StaticActor.h"

void StaticActor::initialize(Vector2f pos, const std::variant<Vector2f, float>& size)
{
	m_position = pos;
	Vector2f actor_size = std::get<Vector2f>(size);
	m_shapeVariant = Rectangle{ actor_size.x , actor_size.y };
	m_shape_type = shape_type::rectangle;
}
