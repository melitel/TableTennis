#pragma once
#include "Ball.h"
#include "Player.h"
#include "BoundingBox.h"

class PhysicsScene
{
public:
	void initialize(int width, int height);
	void update(float delta, float round_time);
	void collision();
private:

	enum collision_type { ct_left, ct_right, ct_top, ct_bottom, ct_count };
	std::array <sf::Vector2f, ct_count> m_collision_normals;
	std::vector<BoundingBox> m_scene;


	


};

