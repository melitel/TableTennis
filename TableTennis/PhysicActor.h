#pragma once
#include "IPhysicActor.h"
#include "Sector.h"
#include "Math.h"

class PhysicsScene;
class IGameEntity;

class PhysicActor : 
	public IPhysicActor
{
public:

	PhysicActor(std::weak_ptr<PhysicsScene> scene, std::weak_ptr<IGameEntity> owner) : m_scene(scene), m_owner(owner) {}

	enum shape_type {
		rectangle,
		circle
	};

	struct Rectangle {
		float width;
		float height;
		BoundingBox calculate_bbox() const {
			return BoundingBox(Vector2f(0.f, 0.f), Vector2f(width, height));
		}
	};

	struct Circle {
		float radius;
		float get_radius() const {
			return radius;
		}
		BoundingBox calculate_bbox() const {
			return BoundingBox(Vector2f(0.f, 0.f), Vector2f(2.f * radius, 2.f * radius));
		}
	};

	void set_position(const Vector2f& pos) override {
		m_position = pos;
	};

	const Vector2f& get_position() const override {
		return m_position;
	};

	shape_type get_shape() {	
		return m_shape_type;
	}

	BoundingBox get_bounds() const override;

	BoundingBox get_bounds(const Vector2f& pos) const override;
	
	void set_sector(int sector_id) override {
		m_sectors.push_back(sector_id);
	}

	void swap_sectors(std::vector<int>& sector_id) {
		m_sectors.swap(sector_id);
	}

	Vector2f get_hit_normal() const override{
		return m_hit_normal;
	}

	const std::weak_ptr<IGameEntity>& get_owner() const override {
		return m_owner;
	}

	std::vector<int>& get_sectors() {
		return m_sectors;
	}

protected:
	std::weak_ptr<PhysicsScene> m_scene;
	std::weak_ptr<IGameEntity> m_owner;
	std::variant <Rectangle, Circle> m_shapeVariant;
	shape_type m_shape_type;
	Vector2f m_position;	
	std::vector<int> m_sectors;
	Vector2f m_hit_normal;
};

