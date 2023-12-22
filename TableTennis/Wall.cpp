#include "Wall.h"
#include "Game.h"

extern Game* g_Game;

void Wall::initialize()
{
	m_wall_shape.setSize(sf::Vector2f(m_wall_width, m_wall_height));
	m_wall_shape.setFillColor(m_sprite_color);
	m_wall_shape.setPosition(m_position);
	m_physicActor = g_Game->create_physic_actor(m_entity_id);
	m_physicActor->initialize(
		m_position, sf::Vector2f(0.f, 0.f), PhysicActor::motion_type::immovable,
		PhysicActor::shape_type::rectangle,
		sf::Vector2f(m_wall_width, m_wall_height));
}

void Wall::draw(std::unique_ptr<sf::RenderWindow>& window)
{
	window->draw(m_wall_shape);
}

