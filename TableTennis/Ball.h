#pragma once
#include "MovableEntity.h"
#include <array>
#include <random>


class Ball : public MovableEntity
{
	// GameEntity implementation
public:

	Ball(Vector2f pos, uint32_t entity_id) : MovableEntity(pos, entity_id) { }

	void initialize() override;
	void draw(std::unique_ptr<sf::RenderWindow>& window) override;
	void update(float delta, float round_time) override;
	void move(float delta, float round_time) override;
	void set_position(Vector2f pos) { m_ball_shape.setPosition(vec2sfml(pos)); }
	void onHit(const Vector2f& normal) override;

public:
		
	void reset(const Vector2f& vel) override;

private:

	sf::CircleShape m_ball_shape;
	const float m_ball_radius = 7.f;
	const float m_ball_speed_step = 10.f;
	const float m_ball_starting_speed = 100.f;
	const uint32_t m_ball_speed_step_duration = 3;
	Vector2f modify_vector(Vector2f& vec);
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen{ rd() }; // seed the generator
	std::uniform_int_distribution<> distr{ -10, 10 }; // define the range
	bool m_ball_vel_sign{ false };	
};

