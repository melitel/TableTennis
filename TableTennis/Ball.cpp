#include "Ball.h"
#include "DynamicActor.h"
#include <cmath>
#include "Game.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

extern Game* g_Game;

void Ball::initialize()
{
	m_velocity = Vector2f(-1.f, 0.f);
	m_speed = 0.f;
	m_ball_shape.setFillColor(m_sprite_color);
	m_ball_shape.setRadius(m_ball_radius);
	m_ball_shape.setPosition(vec2sfml(m_position));
	m_physicActor = g_Game->create_dynamic_actor(m_entity_id);
	DynamicActor* dynactor = (DynamicActor*)m_physicActor.get();
	dynactor->initialize(m_position, m_velocity, true, PhysicActor::shape_type::circle, m_ball_radius, Vector2f(0.f, 0.f));
}

void Ball::draw(std::unique_ptr<sf::RenderWindow>& window)
{
	sf::Vector2f pos = vec2sfml(m_physicActor->get_position());
	m_ball_shape.setPosition(pos);
	window->draw(m_ball_shape);
}

void Ball::update(float delta, float round_time)
{
	move(delta, round_time);
}

void Ball::move(float delta, float round_time)
{
	DynamicActor* dynactor = (DynamicActor*)m_physicActor.get();
	uint32_t n = uint32_t(round_time / m_ball_speed_step_duration);
	m_speed = m_ball_starting_speed + m_ball_speed_step * n;
	Vector2f vel = dynactor->get_velocity_dir() * m_speed;
	dynactor->set_velocity(vel);
}

void Ball::onHit(const Vector2f& normal)
{	
	DynamicActor* dynactor = (DynamicActor*)m_physicActor.get();
	Vector2f reversed_move = -m_velocity;
	Vector2f reflected = reversed_move.reflect(normal);
	reflected = modify_vector(reflected).normalized();
	dynactor->set_velocity(reflected);
}

void Ball::reset(const Vector2f& vel) {
	DynamicActor* dynactor = (DynamicActor*)m_physicActor.get();
	m_velocity = vel;
	m_ball_shape.setPosition(vec2sfml(m_position));
	int random = distr(gen);
	float angle = ((m_ball_vel_sign ? -1 : 1) * 45.f) + random;
	float radians = angle * static_cast<float>(M_PI) / 180.0f;
	m_ball_vel_sign = !m_ball_vel_sign;

	// Rotate the vector manually
	float x = m_velocity.x * std::cos(radians) - m_velocity.y * std::sin(radians);
	float y = m_velocity.x * std::sin(radians) + m_velocity.y * std::cos(radians);

	// Update the velocity vector
	m_velocity.x = x;
	m_velocity.y = y;

	dynactor->set_velocity(m_velocity);
}

Vector2f Ball::modify_vector(Vector2f& vel)
{
	// get a random angle in degrees
	float angle = static_cast<float>(distr(gen));

	// convert degrees to radians
	float radians = angle * static_cast<float>(M_PI) / 180.0f;
	// rotate the vector manually
	float new_x = vel.x * std::cos(radians) - vel.y * std::sin(radians);
	float new_y = vel.x * std::sin(radians) + vel.y * std::cos(radians);

	vel.x = new_x;
	vel.y = new_y;

	return vel;
}


