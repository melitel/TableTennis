#pragma once
#include "StaticEntity.h"

class Wall :
    public StaticEntity
{
	// GameEntity implementation
public:
	enum type {
		top,
		bottom,
		left,
		right
	};

	Wall(Vector2f pos, uint32_t entity_id, entity_type entType, type wall_type) : 
		StaticEntity(pos, entity_id, entType), m_wall_type(wall_type) { }

	void initialize() override;
	void draw(std::unique_ptr<sf::RenderWindow>& window) override;

private:
	type m_wall_type;
	sf::RectangleShape m_wall_shape;
	const float m_wall_width = 700.f;
	const float m_wall_height = 2.f;
	Vector2f get_hit_normal();
};

