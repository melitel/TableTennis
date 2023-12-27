#include "PhysicsScene.h"
#include "PhysicActor.h"
#include "DynamicActor.h"
#include "StaticActor.h"
#include "Game.h"

extern Game* g_Game;

void PhysicsScene::initialize(int width, int height)
{
	m_scene_width = width;
	m_sectors.emplace_back(Vector2f(0, 0), Vector2f(width * 0.2, height), 0, std::vector<int>{1});
	m_sectors.emplace_back(Vector2f(width * 0.2, 0), Vector2f((width - width * 0.2), height), 1, std::vector<int>{0, 2});
	m_sectors.emplace_back(Vector2f((width - width * 0.2), 0), Vector2f(width, height), 2, std::vector<int>{1});

	for (int i = 0; i < m_sectors.size(); i++) {
		for (auto dynactor : m_dynamic_actors) {
			if (m_sectors[i].get_bounds().intersects(dynactor->get_bounds())) {
				dynactor->set_sector(i);
				m_sectors[i].add_dynamic_actor(dynactor);
			}
		}
		for (auto statactor : m_static_actors) {
			if (m_sectors[i].get_bounds().intersects(statactor->get_bounds())) {
				statactor->set_sector(i);
				m_sectors[i].add_static_actor(statactor);
			}
		}
	}
}

void PhysicsScene::update(float delta, float round_time)
{
	simulate(delta, round_time);
}

void PhysicsScene::simulate(float delta, float round_time)
{
	//for m_actors
	for (auto& actor : m_dynamic_actors) {

		DynamicActor* dynactor = (DynamicActor*) actor.get();
		
		if (dynactor->isPureDynamic()) {			
			collision_processing(actor, delta);		
		}
	}
}

const std::shared_ptr<IPhysicActor>& PhysicsScene::create_dynamic_actor(const std::weak_ptr<IGameEntity>& owner)
{
	m_dynamic_actors.push_back(std::make_shared<DynamicActor>(g_Game->physic_scene(), owner));
	return m_dynamic_actors.back();
}

const std::shared_ptr<IPhysicActor>& PhysicsScene::create_static_actor(const std::weak_ptr<IGameEntity>& owner)
{
	m_static_actors.push_back(std::make_shared<StaticActor>(g_Game->physic_scene(), owner));
	return m_static_actors.back();
}

void PhysicsScene::collision_processing(const std::shared_ptr<IPhysicActor>& actor, float delta) {

	DynamicActor* dynactor = (DynamicActor*)actor.get();
	Vector2f p0 = dynactor->get_position();
	Vector2f vel = dynactor->get_velocity();
	Vector2f distance = delta * vel;
	float dist_length = distance.length();
	float step = dynactor->get_radius() * 2;
	Vector2f p1 = p0 + distance;
	std::vector<std::shared_ptr<IPhysicActor>> actors_hit;
	
	if (dist_length < step) {
		if (!g_Game->overlap(dynactor->get_bounds(p1), actor, true, true, actors_hit)) {
			dynactor->set_position(p1);
		}
		else {
			for (int i = 0; i < actors_hit.size(); i++) {
				m_onHit.actor = actor;
				m_onHit.normal = actors_hit[i]->get_hit_normal();
				m_hitInfo.push_back(m_onHit);			
			}
		}
	}
	else {

	}
}

bool PhysicsScene::overlap(const BoundingBox& bb, 
	const std::shared_ptr<IPhysicActor>& ignore_actor, 
	bool dynamic, bool stat,
	std::vector<std::shared_ptr<IPhysicActor>>& actors_hit)
{	
	std::vector<int> sectors_id = get_sector_from_bb(bb);
	bool isOverlap = false;	

	for (int i = 0; i < sectors_id.size(); i++) {
		isOverlap = m_sectors[sectors_id[i]].overlap(bb, ignore_actor, dynamic, stat, actors_hit);
		if (isOverlap) {			
			break;
		}		
	}
	return isOverlap;
}

std::vector<int> PhysicsScene::get_sector_from_bb(const BoundingBox& bb)
{
	std::vector<int> sectors_id;

	for (int i = 0; i < m_sectors.size(); i++) {
		
		if (m_sectors[i].get_bounds().intersects(bb)) {
			sectors_id.push_back(i);
		}		
	}
	
	return sectors_id;
}
