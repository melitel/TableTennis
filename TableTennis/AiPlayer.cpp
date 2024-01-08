#include "AiPlayer.h"
#include "Game.h"
#include "DynamicActor.h"
#include <iostream>

extern Game* g_Game;

void AiPlayer::initialize()
{
	m_speed = 500.f;
	isOfAiInterest = false;
	m_ai_shape.setSize(sf::Vector2f(m_ai_width, m_ai_height));
	m_ai_shape.setFillColor(m_sprite_color);
	m_ai_shape.setPosition(vec2sfml(m_position));
	m_intersectionPoint = Vector2f(m_position.x, m_position.y + m_ai_height / 2);
	m_physicActor = g_Game->create_dynamic_actor(m_entity_id);
	DynamicActor* dynactor = (DynamicActor*)m_physicActor.get();
	dynactor->initialize(
		m_position, m_velocity, false,
		PhysicActor::shape_type::rectangle,
		Vector2f(m_ai_width, m_ai_height), Vector2f(-1, 0));
}

void AiPlayer::draw(std::unique_ptr<sf::RenderWindow>& window)
{
	window->draw(m_ai_shape);
}

void AiPlayer::update(float delta, float round_time)
{
	move(delta, round_time);
}

void AiPlayer::move(float delta, float round_time)
{
	std::vector<std::shared_ptr<IPhysicActor>> actorsHit;
	Vector2f pos = m_physicActor->get_position();
	float ai_middle_y = pos.y + m_ai_height/2;
	Vector2f velocity;

	if (g_Game->overlap(m_vision_box, m_physicActor, true, false, actorsHit)) {
		for (int i = 0; i < actorsHit.size(); i++) {
			std::shared_ptr<IGameEntity> owner_entity = actorsHit[i]->get_owner().lock();
			if (owner_entity->is_of_ai_interest()) {
				DynamicActor* dynactor_of_interest = (DynamicActor*)actorsHit[i].get();				
				Vector2f actor_of_interest_pos = actorsHit[i]->get_position();
				Vector2f velocity_dir = dynactor_of_interest->get_velocity_dir();
				
				if (velocity_dir.x > 0 && !m_isResultY) {

					m_intersectionPoint = findIntersection(actor_of_interest_pos, velocity_dir, pos.x);
					m_isResultY = false;
				}
				if (velocity_dir.x < 0) {
					m_isResultY = false;
				}									

				break;
			}
		}
	}

	if (m_intersectionPoint.y < ai_middle_y - 20.f) {
		velocity.y = -1.f;
	}
	else if (m_intersectionPoint.y > ai_middle_y + 20.f) {
		velocity.y = 1.f;
	}
	else if (m_intersectionPoint.y = ai_middle_y) {
		velocity.y = 0.f;
	}
	
	Vector2f p0 = sfml2svec(m_ai_shape.getPosition());
	Vector2f vel = velocity * m_speed;
	Vector2f p1 = p0 + delta * vel;

	if (vel.length() > 0.001f && !g_Game->overlap(m_physicActor->get_bounds(p1), m_physicActor, false, true, actorsHit)) {
		m_physicActor->set_position(p1);
		m_ai_shape.setPosition(vec2sfml(p1));
	}
}

Vector2f AiPlayer::findIntersection(const Vector2f& pointOnLine, const Vector2f& lineDirection, float xValue) {
	// Check if the line is parallel to the y-axis
	if (lineDirection.x == 0) {
		std::cerr << "Error: The line is parallel to the y-axis." << std::endl;
		// You might want to handle this case differently, depending on your requirements.
		return Vector2f{ 0.0, 0.0 };  // Returning a default point for simplicity.
	}

	// Calculate the parameter t for the intersection
	double t = (xValue - pointOnLine.x) / lineDirection.x;

	// Calculate the intersection point
	Vector2f intersectionPoint;
	intersectionPoint.x = xValue;
	intersectionPoint.y = pointOnLine.y + t * lineDirection.y;

	return intersectionPoint;
}
