#pragma once
#include <vector>
#include <memory>
#include "Math.h"

class PhysicActor;

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

	void add_actor(const std::shared_ptr<PhysicActor>& actor) {
		m_actors.push_back(actor);
	}

private:
	BoundingBox m_bbox;
	int m_id;
	std::vector<int> m_neightbours;
	std::vector<std::shared_ptr<PhysicActor>> m_actors;
};

