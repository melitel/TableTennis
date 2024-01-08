#include "Player.h"
#include "Game.h"
#include "DynamicActor.h"

extern Game* g_Game;

void Player::initialize()
{	
	m_speed = 500.f;
	isOfAiInterest = false;
	m_player_shape.setSize(sf::Vector2f(m_player_width, m_player_height));
	m_player_shape.setFillColor(m_sprite_color);
	m_player_shape.setPosition(vec2sfml(m_position));
	m_physicActor = g_Game->create_dynamic_actor(m_entity_id);
	DynamicActor* dynactor = (DynamicActor*)m_physicActor.get();	
	if (m_player_type == left) {
		dynactor->initialize(
			m_position, m_velocity, false,
			PhysicActor::shape_type::rectangle,
			Vector2f(m_player_width, m_player_height), Vector2f(1, 0));
	}
	else if (m_player_type == right) {
		dynactor->initialize(
			m_position, m_velocity, false,
			PhysicActor::shape_type::rectangle,
			Vector2f(m_player_width, m_player_height), Vector2f(-1, 0));
	}
	else {
		assert(false);
	}	
}

void Player::draw(std::unique_ptr<sf::RenderWindow>& window)
{
	window->draw(m_player_shape);
}

void Player::update(float delta, float round_time)
{
	if (m_player_type == left) {
		change_velocity(g_Game->get_playerL_velocity_requested());
	}
	else if (m_player_type == right) {
		change_velocity(g_Game->get_playerR_velocity_requested());
	}
	else {
		assert(false);
	}	
	move(delta, round_time);
}

void Player::move(float delta, float round_time)
{
	Vector2f p0 = sfml2svec(m_player_shape.getPosition());
	Vector2f vel = m_velocity * m_speed;
	Vector2f p1 = p0 + delta * vel;
	std::vector<std::shared_ptr<IPhysicActor>> actorsHit;
	if (vel.length() > 0.001f && !g_Game->overlap(m_physicActor->get_bounds(p1), m_physicActor, false, true, actorsHit)) {
		m_physicActor->set_position(p1);
		m_player_shape.setPosition(vec2sfml(p1));
	}
}

void Player::change_velocity(float vel_y)
{
	m_velocity.y = vel_y;
}


