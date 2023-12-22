#include "Player.h"
#include "Game.h"

extern Game* g_Game;

void Player::initialize()
{	
	m_player_shape.setSize(sf::Vector2f(m_player_width, m_player_height));
	m_player_shape.setFillColor(sprite_color);
	m_player_shape.setPosition(m_player_pos);
	m_physicActor = g_Game->create_physic_actor(m_entity_id);
	m_physicActor->initialize(
		m_player_pos, m_player_velocity, PhysicActor::motion_type::kinematic,
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
	object_move(delta, round_time);
}

void Player::object_move(float delta, float round_time)
{
	sf::Vector2f p0 = m_player_shape.getPosition();
	sf::Vector2f vel = m_player_velocity * m_player_speed;
	sf::Vector2f p1 = p0 + delta * vel;
	m_physicActor->set_position(p1);
	m_player_shape.setPosition(p1);
}

void Player::change_velocity(float vel_y)
{
	m_player_velocity.y = vel_y;
}


