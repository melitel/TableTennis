#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>

class GameEntity
{
public:

	virtual void initialize() = 0;
	virtual void draw(std::unique_ptr<sf::RenderWindow>& window) = 0;
	virtual void update(float delta, float round_time) = 0;
	virtual void object_move(float delta, float round_time) = 0;
	virtual ~GameEntity() {};

private:	

};

