#include "StaticActor.h"
#include "Wall.h"
#include "Game.h"

extern Game* g_Game;

void Wall::initialize()
{
	m_wall_shape.setSize(sf::Vector2f(m_wall_width, m_wall_height));
	m_wall_shape.setFillColor(m_sprite_color);
	m_wall_shape.setPosition(m_position);
	m_physicActor = g_Game->create_static_actor(m_entity_id);
	StaticActor* statactor = (StaticActor*)m_physicActor.get();
	statactor->initialize(m_position, sf::Vector2f(m_wall_width, m_wall_height));
}

void Wall::draw(std::unique_ptr<sf::RenderWindow>& window)
{
	window->draw(m_wall_shape);
}

