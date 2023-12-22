#include "PhysicsScene.h"
#include "Game.h"

extern Game* g_Game;

void PhysicsScene::initialize(int width, int height)
{
	m_collision_normals[ct_left] = sf::Vector2f(1.f, 0.f);
	m_collision_normals[ct_right] = sf::Vector2f(-1.f, 0.f);
	m_collision_normals[ct_top] = sf::Vector2f(0.f, 1.f);
	m_collision_normals[ct_bottom] = sf::Vector2f(0.f, -1.f);

	m_sector.emplace_back(Vector2f(0, 0), Vector2f(width * 0.2, height), 0, std::vector<int>{1});
	m_sector.emplace_back(Vector2f(width * 0.2, 0), Vector2f((width - width * 0.2), height), 1, std::vector<int>{0, 2});
	m_sector.emplace_back(Vector2f((width - width * 0.2), 0), Vector2f(width, height), 2, std::vector<int>{1});

	for (int i = 0; i < m_sector.size(); i++) {
		for (auto actor : m_actors) {
			if (m_sector[i].get_bounds().intersects(actor->get_bounds())) {
				actor->set_sector(i);
				m_sector[i].add_actor(actor);
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
	for (auto& actor : m_actors) {		
		if (actor->get_motion_type() == PhysicActor::motion_type::dynamic) {
			sf::Vector2f p0 = actor->get_position();
			sf::Vector2f p1 = p0 + delta * actor->get_velocity();
			collision_processing(actor);
			//actor->set_position(p1);		
		}
	}
}

const std::shared_ptr<PhysicActor>& PhysicsScene::create_actor(const std::weak_ptr<GameEntity>& owner)
{
	m_actors.push_back(std::make_shared<PhysicActor>(g_Game->physic_scene(), owner));
	return m_actors.back();
}

void PhysicsScene::collision_processing(const std::shared_ptr<PhysicActor>& actor) {
	

}
