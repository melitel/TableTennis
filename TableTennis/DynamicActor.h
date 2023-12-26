#pragma once
#include "PhysicActor.h"

class DynamicActor :
    public PhysicActor
{
public:

	DynamicActor(std::weak_ptr<PhysicsScene> scene, std::weak_ptr<IGameEntity> owner) : PhysicActor (scene, owner) {}

	void initialize(
		Vector2f pos,
		Vector2f vel,
		bool isPureDynamic,
		shape_type shape,
		const std::variant<Vector2f, float>& size
	);

	const Vector2f& get_velocity_dir() const {
		return m_velocity.normalized();
	};

	const Vector2f& get_velocity() const {
		return m_velocity;
	};

	void set_velocity(const Vector2f& vel) {
		m_velocity = vel;
	};

	bool isPureDynamic() {
		return m_PureDynamic;
	}

private:

	Vector2f m_velocity {0.f, 0.f};
	bool m_PureDynamic = false;

};

