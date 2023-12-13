#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameEntity.h"

class Player : public GameEntity
{
public:

	void initialize() override;
	void draw(std::unique_ptr<sf::RenderWindow>& window) override;
	void update(float delta, float round_time) override;
	void object_move(float delta, float round_time) override;

public:

	sf::Vector2f get_position() { return m_player_shape.getPosition(); }
	void set_position(sf::Vector2f pos) { m_player_shape.setPosition(pos); }
	float get_height() { return m_player_height; }
	void change_velocity(float vel_y);

private:
	const sf::Color sprite_color{ 255, 255, 255 };
	sf::RectangleShape m_player_shape;
	sf::Vector2f m_player_velocity{ 0.f, 0.f };
	const float m_player_width = 15.f;
	const float m_player_height = 120.f;
	const float m_player_speed = 500.f;
};

