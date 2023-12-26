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
	m_velocity = reset_ball({ -1.f, 0.f });
	m_speed = 0.f;
	m_ball_shape.setFillColor(m_sprite_color);
	m_ball_shape.setRadius(m_ball_radius);
	m_ball_shape.setPosition(vec2sfml(m_position));
	m_physicActor = g_Game->create_dynamic_actor(m_entity_id);
	DynamicActor* dynactor = (DynamicActor*)m_physicActor.get();
	dynactor->initialize(m_position, m_velocity, true, PhysicActor::shape_type::circle, m_ball_radius);
}

void Ball::draw(std::unique_ptr<sf::RenderWindow>& window)
{
	sf::Vector2f pos = vec2sfml(m_physicActor->get_position());
	m_ball_shape.setPosition(pos);
	window->draw(m_ball_shape);
}

void Ball::update(float delta, float round_time)
{
	//ball_collision_processing(delta);
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

Vector2f Ball::reflect_ball(Vector2f collision_type) const {

	Vector2f normal = collision_type;
	Vector2f reversed_move = -m_velocity;
	Vector2f reflected = reflect(reversed_move, normal);
	reflected = reflected.normalized();

	return reflected;
}

Vector2f Ball::reset_ball(Vector2f velocity) {
		
	int random = distr(gen);
	float angle = ((m_ball_vel_sign ? -1 : 1) * 45.f) + random;
	float radians = angle * static_cast<float>(M_PI) / 180.0f;
	m_ball_vel_sign = !m_ball_vel_sign;

	// Rotate the vector manually
	float x = velocity.x * std::cos(radians) - velocity.y * std::sin(radians);
	float y = velocity.x * std::sin(radians) + velocity.y * std::cos(radians);

	// Update the velocity vector
	velocity.x = x;
	velocity.y = y;

	return velocity;
}

float Ball::dot(const Vector2f& v1, const Vector2f& v2) const {
	return v1.x * v2.x + v1.y * v2.y;
}

Vector2f Ball::reflect(const Vector2f& vector, const Vector2f& normal) const {
	return 2.f * dot(normal, vector) * normal - vector;
}
