#pragma once
#include "MovableEntity.h"
#include <array>
#include <random>
#include "Observer.h"


class Ball : public MovableEntity
{
	// GameEntity implementation
public:

	Ball(Vector2f pos, uint32_t entity_id, entity_type entType) : 
		MovableEntity(pos, entity_id, entType), m_starting_position(pos) { }

	void initialize() override;
	void draw(std::unique_ptr<sf::RenderWindow>& window) override;
	void update(float delta, float round_time) override;
	void move(float delta, float round_time) override;
	void set_position(Vector2f pos) { m_ball_shape.setPosition(vec2sfml(pos)); }
	void onHit(const Vector2f& normal, const std::shared_ptr<IGameEntity>& entity_hit) override;
	void addObserver(Observer* observer) override;
	void removeObserver(Observer* observer) override;

public:
		
	void reset(const Vector2f& vel) override;

private:

	std::vector<Observer*> observers;
	sf::CircleShape m_ball_shape;
	const float m_ball_radius = 7.f;
	const float m_ball_speed_step = 10.f;
	const float m_ball_starting_speed = 100.f;
	const Vector2f m_starting_position;
	const uint32_t m_ball_speed_step_duration = 3;
	std::vector<Vector2f> m_ball_starting_dir {
		Vector2f(-1.f, -1.f), 
		Vector2f(-1.f, 0.f), 
		Vector2f(-1.f, 1.f),
		Vector2f(1.f, -1.f),
		Vector2f(1.f, 0.f),
		Vector2f(1.f, 1.f)	
	};
	Vector2f modify_vector(Vector2f& vec);
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen{ rd() }; // seed the generator
	std::uniform_int_distribution<> distr{ -10, 10 }; // define the range
	std::uniform_int_distribution<int> dist{ 0, 5 };
	std::uniform_int_distribution<int> leftHit{ 3, 5 };
	std::uniform_int_distribution<int> rightHit{ 0, 2 };
	bool m_ball_vel_sign{ false };	
};

