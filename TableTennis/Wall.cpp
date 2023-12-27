#include "StaticActor.h"
#include "Wall.h"
#include "Game.h"

extern Game* g_Game;

void Wall::initialize()
{
	m_wall_shape.setSize(sf::Vector2f(m_wall_width, m_wall_height));
	m_wall_shape.setFillColor(m_sprite_color);
	m_wall_shape.setPosition(vec2sfml(m_position));
	m_physicActor = g_Game->create_static_actor(m_entity_id);
	StaticActor* statactor = (StaticActor*)m_physicActor.get();
	statactor->initialize(m_position, Vector2f(m_wall_width, m_wall_height), get_hit_normal());
}

void Wall::draw(std::unique_ptr<sf::RenderWindow>& window)
{
	window->draw(m_wall_shape);
}

Vector2f Wall::get_hit_normal()
{
	Vector2f hit_normal;

	if (m_wall_type == type::top) {
		hit_normal = Vector2f(0.f, 1.f);
	}
	else if(m_wall_type == type::bottom) {
		hit_normal = Vector2f(0.f, -1.f);
	}
	else {
		assert(false);
	}

	return hit_normal;
}


