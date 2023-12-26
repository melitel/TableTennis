#pragma once
#include "StaticEntity.h"

class Wall :
    public StaticEntity
{
	// GameEntity implementation
public:

	Wall(Vector2f pos, uint32_t entity_id) : StaticEntity(pos, entity_id) { }

	void initialize() override;
	void draw(std::unique_ptr<sf::RenderWindow>& window) override;

private:

	sf::RectangleShape m_wall_shape;
	const float m_wall_width = 700.f;
	const float m_wall_height = 2.f;
};

