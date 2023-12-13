#include "PhysicsScene.h"

void PhysicsScene::initialize(int width, int height)
{
	m_collision_normals[ct_left] = sf::Vector2f(1.f, 0.f);
	m_collision_normals[ct_right] = sf::Vector2f(-1.f, 0.f);
	m_collision_normals[ct_top] = sf::Vector2f(0.f, 1.f);
	m_collision_normals[ct_bottom] = sf::Vector2f(0.f, -1.f);

	m_scene.push_back(BoundingBox(0, (int)(width * 0.2), 0, height, 0, std::vector<int>{1}));
	m_scene.push_back(BoundingBox((int)(width * 0.2), (int)(width - width * 0.2), 0, height, 1, std::vector<int>{0, 2}));
	m_scene.push_back(BoundingBox((int)(width - width * 0.2), width, 0, height, 2, std::vector<int>{1}));
}

void PhysicsScene::update(float delta, float round_time)
{

}

void PhysicsScene::collision()
{
}
