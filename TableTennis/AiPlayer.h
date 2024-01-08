#pragma once
#include "MovableEntity.h"

class AiPlayer : public MovableEntity
{
public:
	AiPlayer(Vector2f pos, uint32_t entity_id, entity_type entType) :
		MovableEntity(pos, entity_id, entType) {	}

	void initialize() override;
	void draw(std::unique_ptr<sf::RenderWindow>& window) override;
	void update(float delta, float round_time) override;
	void move(float delta, float round_time) override;

	Vector2f get_position() { return sfml2svec(m_ai_shape.getPosition()); }
	void set_position(Vector2f pos) { m_ai_shape.setPosition(vec2sfml(pos)); }
	float get_height() { return m_ai_height; }
	Vector2f findIntersection(const Vector2f& pointOnLine, const Vector2f& lineDirection, float xValue);

private:
	sf::RectangleShape m_ai_shape;
	bool m_isResultY = false;
	Vector2f m_intersectionPoint;
	const float m_ai_width = 15.f;
	const float m_ai_height = 120.f;
	BoundingBox m_vision_box = BoundingBox(Vector2f(350.f, 0.f), Vector2f(700.f, 700.f));
};

