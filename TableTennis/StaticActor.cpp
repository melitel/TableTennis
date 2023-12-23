#include "StaticActor.h"

void StaticActor::initialize(sf::Vector2f pos, const std::variant<sf::Vector2f, float>& size)
{
	m_position = pos;
	sf::Vector2f actor_size = std::get<sf::Vector2f>(size);
	m_shapeVariant = Rectangle{ actor_size.x , actor_size.y };
}
