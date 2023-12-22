#pragma once
#include "GameEntity.h"
#include "PhysicActor.h"

class Wall :
    public GameEntity
{
	// GameEntity implementation
public:

	Wall(sf::Vector2f pos, uint32_t entity_id) : m_pos(pos), m_entity_id(entity_id), m_physicActor(nullptr) { }

	void initialize() override;
	void draw(std::unique_ptr<sf::RenderWindow>& window) override;
	void update(float delta, float round_time) override;
	void object_move(float delta, float round_time) override;

private:
	std::shared_ptr<PhysicActor> m_physicActor;
	sf::RectangleShape m_wall_shape;
	sf::Vector2f m_pos;
	uint32_t m_entity_id;
	const sf::Color sprite_color{ 255, 255, 255 };
	sf::Vector2f m_velocity{ 0.f, 0.f };
	const float m_wall_width = 700.f;
	const float m_wall_height = 1.f;
};

