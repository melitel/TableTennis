#pragma once
#include "PhysicActor.h"

class DynamicActor :
    public PhysicActor
{
public:

	void initialize(
		sf::Vector2f pos,
		sf::Vector2f vel,
		bool isPureDynamic,
		shape_type shape,
		const std::variant<sf::Vector2f, float>& size
	);

	const sf::Vector2f& get_velocity() const {
		return m_velocity;
	};

	void set_velocity(const sf::Vector2f& vel) {
		m_velocity = vel;
	};

	bool isPureDynamic() {
		return m_PureDynamic;
	}

private:

    sf::Vector2f m_velocity;
	bool m_PureDynamic = false;

};

