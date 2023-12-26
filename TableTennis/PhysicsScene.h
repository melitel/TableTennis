#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include <memory>
#include "Sector.h"
#include "IPhysicActor.h"

class IGameEntity;

class PhysicsScene
{
public:
	void initialize(int width, int height);
	void update(float delta, float round_time);
	void simulate(float delta, float round_time);
	const std::shared_ptr<IPhysicActor>& create_dynamic_actor(const std::weak_ptr<IGameEntity>& owner);
	const std::shared_ptr<IPhysicActor>& create_static_actor(const std::weak_ptr<IGameEntity>& owner);
	void collision_processing(const std::shared_ptr<IPhysicActor>& actor);
	bool overlap(const BoundingBox& bb, const std::shared_ptr<IPhysicActor>& actor, bool dynamic, bool stat);

private:

	std::vector<int> get_sector_from_bb(const BoundingBox& bb);
	enum collision_type { ct_left, ct_right, ct_top, ct_bottom, ct_count };
	std::array <Vector2f, ct_count> m_collision_normals;
	std::vector<Sector> m_sectors;
	std::vector<std::shared_ptr<IPhysicActor>> m_dynamic_actors;
	std::vector<std::shared_ptr<IPhysicActor>> m_static_actors;
};

