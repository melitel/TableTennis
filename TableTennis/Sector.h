#pragma once
#include <vector>
#include <memory>
#include "Math.h"

class IPhysicActor;

class Sector
{
public:

	Sector(
		Vector2f min,
		Vector2f max,
		int id,
		std::vector<int> neightbours
	) :
		m_bbox(min, max),
		m_id(id),
		m_neightbours(neightbours)
	{}

	const BoundingBox& get_bounds() const{
		return m_bbox;
	}

	void add_dynamic_actor(const std::shared_ptr<IPhysicActor>& actor) {
		m_dynamic_actors.push_back(actor);
	}

	void delete_dynamic_actor(const std::shared_ptr<IPhysicActor>& actor);

	void add_static_actor(const std::shared_ptr<IPhysicActor>& actor) {
		m_static_actors.push_back(actor);
	}

	bool overlap(const BoundingBox& bb, 
		const std::shared_ptr<IPhysicActor>& actor, 
		bool dynamic, bool stat,
		std::vector<std::shared_ptr<IPhysicActor>>& actors_hit);

private:
	BoundingBox m_bbox;
	int m_id;
	std::vector<int> m_neightbours;
	std::vector<std::shared_ptr<IPhysicActor>> m_dynamic_actors;
	std::vector<std::shared_ptr<IPhysicActor>> m_static_actors;
};

