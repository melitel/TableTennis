#include "Ball.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


void Ball::initialize()
{
	m_ball_shape.setFillColor(sprite_color);
	m_ball_shape.setRadius(m_ball_radius);
	m_ball_shape.setPosition(m_ball_position);
	m_velocity = reset_ball({ 1.f, 0.f });
}

void Ball::draw(std::unique_ptr<sf::RenderWindow>& window)
{
	window->draw(m_ball_shape);
}

void Ball::update(float delta, float round_time)
{
	//ball_collision_processing(delta);
	object_move(delta, round_time);
}

void Ball::object_move(float delta, float round_time)
{
	uint32_t n = uint32_t(round_time / m_ball_speed_step_duration);
	m_ball_speed = m_ball_starting_speed + m_ball_speed_step * n;

	sf::Vector2f p0 = m_ball_shape.getPosition();
	sf::Vector2f vel = m_velocity * m_ball_speed;
	sf::Vector2f p1 = p0 + delta * vel;
	m_ball_shape.setPosition(p1);
}

sf::Vector2f Ball::reflect_ball(sf::Vector2f collision_type) const {

	sf::Vector2f normal = collision_type;
	sf::Vector2f reversed_move = -m_velocity;
	sf::Vector2f reflected = reflect(reversed_move, normal);
	reflected = normalize(reflected);

	return reflected;
}

sf::Vector2f Ball::reset_ball(sf::Vector2f velocity) {
		
	int random = distr(gen);
	float angle = ((m_ball_vel_sign ? -1 : 1) * 45.f) + random;
	float radians = angle * static_cast<float>(M_PI) / 180.0f;
	m_ball_vel_sign = !m_ball_vel_sign;

	// Rotate the vector manually
	float x = velocity.x * std::cos(radians) - velocity.y * std::sin(radians);
	float y = velocity.x * std::sin(radians) + velocity.y * std::cos(radians);

	// Update the velocity vector
	velocity.x = x;
	velocity.y = y;

	return velocity;
}

void Ball::ball_collision_processing(float mdt) {

	//sf::Vector2f vel = m_velocity * m_ball_speed * mdt;
	//sf::Vector2f pos0 = m_ball_shape.getPosition();
	//sf::Vector2f pos1 = m_ball_shape.getPosition() + vel;

	//std::array<sf::Vector2f, 8> points;
	//points[0] = pos0;
	//pos0.x += m_ball_size * 2;
	//points[1] = pos0;
	//pos0.y += m_ball_size * 2;
	//points[2] = pos0;
	//pos0.x -= m_ball_size * 2;
	//points[3] = pos0;

	//points[4] = pos1;
	//pos1.x += m_ball_size * 2;
	//points[5] = pos1;
	//pos1.y += m_ball_size * 2;
	//points[6] = pos1;
	//pos1.x -= m_ball_size * 2;
	//points[7] = pos1;

	//float min_x = points[0].x;
	//float max_x = points[0].x;
	//float min_y = points[0].y;
	//float max_y = points[0].y;

	//for (int i = 0; i < points.size(); ++i)
	//{
	//	if (points[i].x < min_x)
	//	{
	//		min_x = points[i].x;
	//	}
	//	if (points[i].x > max_x)
	//	{
	//		max_x = points[i].x;
	//	}
	//	if (points[i].y < min_y)
	//	{
	//		min_y = points[i].y;
	//	}
	//	if (points[i].y > max_y)
	//	{
	//		max_y = points[i].y;
	//	}
	//}

	//sf::Vector2f min_point(min_x, min_y);
	//sf::Vector2f max_point(max_x, max_y);

	//float big_box_width = max_x - min_x;
	//float big_box_heights = max_y - min_y;

	//sf::FloatRect big_box(min_point, sf::Vector2f(big_box_width, big_box_heights));

	//sf::Vector2f pos = m_ball_shape.getPosition();

	//if (pos.y <= (m_header_height + m_ball_size))
	//{
	//	m_velocity = reflect_ball(ct_top);
	//}
	//else if (pos.y >= (m_window_height - m_ball_size))
	//{
	//	m_velocity = reflect_ball(ct_bottom);
	//}
	//else if (big_box.intersects(player1.getGlobalBounds())) {
	//	m_velocity = reflect_ball(ct_left);

	//	// Get a random angle in degrees
	//	float angle = static_cast<float>(distr(gen));

	//	// Convert degrees to radians
	//	float radians = angle * static_cast<float>(M_PI) / 180.0f;
	//	// Rotate the vector manually
	//	float new_x = m_velocity.x * std::cos(radians) - m_velocity.y * std::sin(radians);
	//	float new_y = m_velocity.x * std::sin(radians) + m_velocity.y * std::cos(radians);

	//	m_velocity.x = new_x;
	//	m_velocity.y = new_y;
	//}
	//else if (big_box.intersects(player2.getGlobalBounds())) {
	//	m_velocity = reflect_ball(ct_right);

	//	// Get a random angle in degrees
	//	float angle = static_cast<float>(distr(gen));

	//	// Convert degrees to radians
	//	float radians = angle * static_cast<float>(M_PI) / 180.0f;
	//	// Rotate the vector manually
	//	float new_x = m_velocity.x * std::cos(radians) - m_velocity.y * std::sin(radians);
	//	float new_y = m_velocity.x * std::sin(radians) + m_velocity.y * std::cos(radians);

	//	m_velocity.x = new_x;
	//	m_velocity.y = new_y;
	//}

	//if (pos.x > m_window_width)
	//{
	//	m_ball_shape.setPosition(m_ball_position);
	//	m_velocity = reset_ball({ -1.f, 0.f });
	//	m_player_score[p_left]++;
	//}
	//else if (pos.x < 0)
	//{
	//	m_ball_shape.setPosition(m_ball_position);
	//	m_velocity = reset_ball({ 1.f, 0.f });
	//	m_player_score[p_right]++;
	//}
}


sf::Vector2f Ball::normalize(sf::Vector2f& vector) const {
	float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);

	if (length != 0.0f) {
		return sf::Vector2f(vector.x / length, vector.y / length);
	}
	else {
		// Handle the case where the length is zero to avoid division by zero
		return sf::Vector2f(0.0f, 0.0f);
	}
}

float Ball::dot(const sf::Vector2f& v1, const sf::Vector2f& v2) const {
	return v1.x * v2.x + v1.y * v2.y;
}

sf::Vector2f Ball::reflect(const sf::Vector2f& vector, const sf::Vector2f& normal) const {
	return 2.f * dot(normal, vector) * normal - vector;
}
