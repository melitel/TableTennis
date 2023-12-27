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
	struct hit_info {
		Vector2f normal;
		std::shared_ptr<IPhysicActor> actor;
	};
	void initialize(int width, int height);
	void update(float delta, float round_time);
	void simulate(float delta, float round_time);
	const std::shared_ptr<IPhysicActor>& create_dynamic_actor(const std::weak_ptr<IGameEntity>& owner);
	const std::shared_ptr<IPhysicActor>& create_static_actor(const std::weak_ptr<IGameEntity>& owner);
	void collision_processing(const std::shared_ptr<IPhysicActor>& actor, float delta);
	bool overlap(const BoundingBox& bb, 
		const std::shared_ptr<IPhysicActor>& actor, 
		bool dynamic, bool stat,
		std::vector<std::shared_ptr<IPhysicActor>>& actors_hit);
	void get_hit_info(std::vector<hit_info>& hitInfo) {
		m_hitInfo.swap(hitInfo);
	}

private:

	hit_info m_onHit;
	std::vector<int> get_sector_from_bb(const BoundingBox& bb);
	std::vector<Sector> m_sectors;
	std::vector<std::shared_ptr<IPhysicActor>> m_dynamic_actors;
	std::vector<std::shared_ptr<IPhysicActor>> m_static_actors;
	std::vector<hit_info> m_hitInfo;
	int m_scene_width;
};

