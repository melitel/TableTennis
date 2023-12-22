#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include <memory>
#include "Sector.h"
#include "PhysicActor.h"

class GameEntity;

class PhysicsScene
{
public:
	void initialize(int width, int height);
	void update(float delta, float round_time);
	void simulate(float delta, float round_time);
	const std::shared_ptr<PhysicActor>& create_actor(const std::weak_ptr<GameEntity>& owner);
	void collision_processing(const std::shared_ptr<PhysicActor>& actor);
private:

	enum collision_type { ct_left, ct_right, ct_top, ct_bottom, ct_count };
	std::array <sf::Vector2f, ct_count> m_collision_normals;
	std::vector<Sector> m_sector;
	std::vector<std::shared_ptr<PhysicActor>> m_actors;
};

