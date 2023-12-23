#include "Player.h"
#include "Game.h"
#include "DynamicActor.h"

extern Game* g_Game;

void Player::initialize()
{	
	m_speed = 500.f;
	m_player_shape.setSize(sf::Vector2f(m_player_width, m_player_height));
	m_player_shape.setFillColor(m_sprite_color);
	m_player_shape.setPosition(m_position);
	m_physicActor = g_Game->create_dynamic_actor(m_entity_id);
	DynamicActor* dynactor = (DynamicActor*)m_physicActor.get();
	dynactor->initialize(
		m_position, m_velocity, false,
		PhysicActor::shape_type::rectangle, 
		sf::Vector2f(m_player_width, m_player_height));
}

void Player::draw(std::unique_ptr<sf::RenderWindow>& window)
{
	window->draw(m_player_shape);
}

void Player::update(float delta, float round_time)
{
	change_velocity(g_Game->get_velocity_requested());
	move(delta, round_time);
}

void Player::move(float delta, float round_time)
{
	sf::Vector2f p0 = m_player_shape.getPosition();
	sf::Vector2f vel = m_velocity * m_speed;
	sf::Vector2f p1 = p0 + delta * vel;
	m_physicActor->set_position(p1);
	m_player_shape.setPosition(p1);
}

void Player::change_velocity(float vel_y)
{
	m_velocity.y = vel_y;
}


