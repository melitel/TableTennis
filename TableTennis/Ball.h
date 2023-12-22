#pragma once
#include "MovableEntity.h"
#include <array>
#include <random>


class Ball : public MovableEntity
{
	// GameEntity implementation
public:

	Ball(sf::Vector2f pos, uint32_t entity_id) : MovableEntity(pos, entity_id) { }

	void initialize() override;
	void draw(std::unique_ptr<sf::RenderWindow>& window) override;
	void update(float delta, float round_time) override;
	void move(float delta, float round_time) override;

public:

	sf::Vector2f reflect_ball(sf::Vector2f collision_type) const;
	sf::Vector2f reset_ball(sf::Vector2f velocity);

private:

	sf::CircleShape m_ball_shape;
	const float m_ball_radius = 7.f;
	const float m_ball_speed_step = 50.f;
	const float m_ball_starting_speed = 100.f;
	const uint32_t m_ball_speed_step_duration = 3;

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen{ rd() }; // seed the generator
	std::uniform_int_distribution<> distr{ -10, 10 }; // define the range
	bool m_ball_vel_sign{ false };	

	sf::Vector2f normalize(sf::Vector2f& vector) const;
	float dot(const sf::Vector2f& v1, const sf::Vector2f& v2) const;
	sf::Vector2f reflect(const sf::Vector2f& vector, const sf::Vector2f& normal) const;
};

