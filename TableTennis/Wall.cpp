#include "Wall.h"
#include "Game.h"

extern Game* g_Game;

void Wall::initialize()
{
	m_wall_shape.setSize(sf::Vector2f(m_wall_width, m_wall_height));
	m_wall_shape.setFillColor(sprite_color);
	m_wall_shape.setPosition(m_pos);
	m_physicActor = g_Game->create_physic_actor(m_entity_id);
	m_physicActor->initialize(
		m_pos, m_velocity, PhysicActor::motion_type::immovable,
		PhysicActor::shape_type::rectangle,
		sf::Vector2f(m_wall_width, m_wall_height));
}

void Wall::draw(std::unique_ptr<sf::RenderWindow>& window)
{
	window->draw(m_wall_shape);
}

void Wall::update(float delta, float round_time)
{
}

void Wall::object_move(float delta, float round_time)
{
}
