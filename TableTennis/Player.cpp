#include "Player.h"

void Player::initialize()
{
	m_player_shape.setSize(sf::Vector2f(m_player_width, m_player_height));
	m_player_shape.setFillColor(sprite_color);
	m_player_shape.setPosition(sf::Vector2f(100.f, 340.f));
}

void Player::draw(std::unique_ptr<sf::RenderWindow>& window)
{
	window->draw(m_player_shape);
}

void Player::update(float delta, float round_time)
{
	object_move(delta, round_time);
}

void Player::object_move(float delta, float round_time)
{
	sf::Vector2f p0 = m_player_shape.getPosition();
	sf::Vector2f vel = m_player_velocity * m_player_speed;
	sf::Vector2f p1 = p0 + delta * vel;
	m_player_shape.setPosition(p1);
}

void Player::change_velocity(float vel_y)
{
	m_player_velocity.y = vel_y;
}


