#pragma once
#include "MovableEntity.h"

class Player : public MovableEntity
{
public:

	Player(sf::Vector2f pos, uint32_t entity_id) : MovableEntity(pos, entity_id) {	}

	void initialize() override;
	void draw(std::unique_ptr<sf::RenderWindow>& window) override;
	void update(float delta, float round_time) override;
	void move(float delta, float round_time) override;

	sf::Vector2f get_position() { return m_player_shape.getPosition(); }
	void set_position(sf::Vector2f pos) { m_player_shape.setPosition(pos); }
	float get_height() { return m_player_height; }
	void change_velocity(float vel_y);

private:	
	sf::RectangleShape m_player_shape;
	const float m_player_width = 15.f;	
	const float m_player_height = 120.f;
};

