#include "Game.h"
#include<iostream>

void Game::run()
{
	initialize();

	while (m_window.isOpen()) {	

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		input_array my_input_array{ m_input_state };
		

		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed: handlePlayerInput(event.key.code, true, my_input_array); break;
			case sf::Event::KeyReleased: handlePlayerInput(event.key.code, false, my_input_array); break;
			}
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
			m_window.close();
		}

		// process events
		process_inputs(my_input_array);
		my_input_array.swap(m_input_state);
		update();
		draw();
	}
}

void Game::initialize()
{
	m_window.setVerticalSyncEnabled(true);
	m_start_time = std::chrono::system_clock::now();
	// clear the window with black color
	m_window.clear(sf::Color::Black);
	m_game_status = game_status::pause;
	m_collision_normals[ct_left] = sf::Vector2f(1.f, 0.f);
	m_collision_normals[ct_right] = sf::Vector2f(-1.f, 0.f);
	m_collision_normals[ct_top] = sf::Vector2f(0.f, 1.f);
	m_collision_normals[ct_bottom] = sf::Vector2f(0.f, -1.f);

	if (!m_font.loadFromFile("arial.ttf"))
	{
		int ii = 10;
	}

	player1.setSize(sf::Vector2f(m_player_width, m_player_height));
	player2.setSize(sf::Vector2f(m_player_width, m_player_height));

	player1.setFillColor(sprite_color);
	player2.setFillColor(sprite_color);

	player1.setPosition(sf::Vector2f(100.f, 340.f));
	player2.setPosition(sf::Vector2f(600.f, 340.f));

	m_ball.setFillColor(sprite_color);
	m_ball.setPosition(m_ball_position);

	m_score_text.setFont(m_font);
	m_score_text.setCharacterSize(40);
	m_score_text.setFillColor(sprite_color);
	m_score_text.setPosition(sf::Vector2f(245.f, 25.f));
	m_score_text.setString(std::string("Score ") + std::to_string (m_player_score[p_left]) + " : " + std::to_string(m_player_score[p_right]));

	border.setSize(sf::Vector2f((float)m_window_width, 2.f));
	border.setFillColor(sprite_color);
	border.setPosition(sf::Vector2f(0.f, 100.f));	

	m_velocity = reset_ball({ 1.f, 0.f });

	m_window.draw(player1);
	m_window.draw(player2);
	m_window.draw(m_ball);
	m_window.draw(m_score_text);
	m_window.draw(border);


	m_window.display();

}

void Game::draw()
{	
	m_window.clear();

	m_window.draw(player1);
	m_window.draw(player2);
	m_window.draw(m_ball);
	m_window.draw(m_score_text);
	m_window.draw(border);

	m_window.display();
}

void Game::update()
{
	// Time logic 
	m_frame_id++;
	std::chrono::time_point t = std::chrono::system_clock::now();
	m_dt = t - m_time;
	m_time = t;
	m_total_time = t - m_start_time;


	float delta = m_dt.count();
	if (m_game_status != game_status::pause)
	{
		m_round_time += m_dt;
	}

	uint32_t n = uint32_t (m_round_time.count() / m_ball_speed_step_duration);

	m_ball_speed = m_ball_starting_speed + m_ball_speed_step*n;
	ball_collision_processing();
	
	object_move(m_ball, m_velocity, m_ball_speed, delta);
	object_move(player1, m_player1_velocity, m_player_speed, delta);
	object_move(player2, m_player2_velocity, m_player_speed, delta);

	sf::Vector2f pos = player1.getPosition();
	pos.y = std::clamp(pos.y, m_header_height, m_window_height-m_player_height);
	player1.setPosition(pos);

	pos = player2.getPosition();
	pos.y = std::clamp(pos.y, m_header_height, m_window_height - m_player_height);
	player2.setPosition(pos);

	m_score_text.setString(std::string("Score ") + std::to_string(m_player_score[p_left]) + " : " + std::to_string(m_player_score[p_right]));
	
	if (m_game_status == game_status::pause)
	{
		m_score_text.setFillColor(sf::Color::Red);
	}
	else
	{
		m_score_text.setFillColor(sf::Color::Green);
	}

}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed, input_array& my_input_array)
{
	if (key == sf::Keyboard::A) {
		my_input_array[key_A] = isPressed;
	}

	if (key == sf::Keyboard::D) {
		my_input_array[key_D] = isPressed;
	}

	if (key == sf::Keyboard::Left) {
		my_input_array[key_Left] = isPressed;
	}

	if (key == sf::Keyboard::Right) {
		my_input_array[key_Right] = isPressed;
	}

	if (key == sf::Keyboard::Space) {
		my_input_array[key_Pause] = isPressed;		
	}	
}

void Game::process_inputs(const input_array& my_input_array) {

	if (my_input_array[key_Pause] && !m_input_state[key_Pause])
	{
		if (m_game_status == game_status::ingame) {
			m_game_status = game_status::pause;
		}
		else {
			m_game_status = game_status::ingame;
		}
	}

	if (my_input_array[key_A] != m_input_state[key_A])
	{
		if (!m_input_state[key_A] && my_input_array[key_A])
		{
			m_player1_velocity.y = -1.f;
		}
		else if (!my_input_array[key_D]) {

			m_player1_velocity.y = 0.f;
		}
		else if (my_input_array[key_D])
		{
			m_player1_velocity.y = 1.f;
		}
	}

	if (my_input_array[key_D] != m_input_state[key_D])
	{
		if (!m_input_state[key_D] && my_input_array[key_D])
		{
			m_player1_velocity.y = 1.f;
		}
		else if (!my_input_array[key_A]) {

			m_player1_velocity.y = 0.f;
		}
		else if (my_input_array[key_A])
		{
			m_player1_velocity.y = -1.f;
		}
	}

	if (my_input_array[key_Left] != m_input_state[key_Left])
	{
		if (!m_input_state[key_Left] && my_input_array[key_Left])
		{
			m_player2_velocity.y = -1.f;
		}
		else if (!my_input_array[key_Right]) {

			m_player2_velocity.y = 0.f;
		}
		else if (my_input_array[key_Right])
		{
			m_player2_velocity.y = 1.f;
		}
	}

	if (my_input_array[key_Right] != m_input_state[key_Right])
	{
		if (!m_input_state[key_Right] && my_input_array[key_Right])
		{
			m_player2_velocity.y = 1.f;
		}
		else if (!my_input_array[key_Left]) {

			m_player2_velocity.y = 0.f;
		}
		else if (my_input_array[key_Left])
		{
			m_player2_velocity.y = -1.f;
		}
	}
}

void Game::object_move(sf::Shape& shape, const sf::Vector2f& velocity, float speed, float delta) {
	if (m_game_status == game_status::ingame)
	{
		sf::Vector2f p0 = shape.getPosition();
		sf::Vector2f vel = velocity * speed;
		sf::Vector2f p1 = p0 + delta * vel;
		shape.setPosition(p1);
	}
}

void Game::ball_collision_processing() {
	sf::Vector2f vel = m_velocity * m_ball_speed * m_dt.count();
	sf::Vector2f pos0 = m_ball.getPosition();
	sf::Vector2f pos1 = m_ball.getPosition() + vel;

	std::array<sf::Vector2f, 8> points;
	points[0] = pos0;
	pos0.x += m_ball_size * 2;
	points[1] = pos0;
	pos0.y += m_ball_size * 2;
	points[2] = pos0;
	pos0.x -= m_ball_size * 2;
	points[3] = pos0;

	points[4] = pos1;
	pos1.x += m_ball_size * 2;
	points[5] = pos1;
	pos1.y += m_ball_size * 2;
	points[6] = pos1;
	pos1.x -= m_ball_size * 2;
	points[7] = pos1;

	float min_x = points[0].x;
	float max_x = points[0].x;
	float min_y = points[0].y;
	float max_y = points[0].y;

	for (int i=0; i < points.size(); ++i)
	{
		if (points[i].x < min_x)
		{
			min_x = points[i].x;
		}
		if (points[i].x > max_x)
		{
			max_x = points[i].x;
		}
		if (points[i].y < min_y)
		{
			min_y = points[i].y;
		}
		if (points[i].y > max_y)
		{
			max_y = points[i].y;
		}
	}

	sf::Vector2f min_point(min_x, min_y);
	sf::Vector2f max_point(max_x, max_y);

	float big_box_width = max_x - min_x;
	float big_box_heights = max_y - min_y;

	sf::FloatRect big_box(min_point, sf::Vector2f(big_box_width, big_box_heights));

	sf::Vector2f pos = m_ball.getPosition();
	if (pos.y <= (m_header_height + m_ball_size))
	{
		m_velocity = reflect_ball(ct_top);
	}
	else if (pos.y >= (m_window_height - m_ball_size))
	{
		m_velocity = reflect_ball(ct_bottom);
	}
	else if (big_box.findIntersection(player1.getGlobalBounds())) {
		m_velocity = reflect_ball(ct_left);
		m_velocity = m_velocity.rotatedBy(sf::degrees((float)distr(gen)));
	}
	else if (big_box.findIntersection(player2.getGlobalBounds())) {
		m_velocity = reflect_ball(ct_right);
		m_velocity = m_velocity.rotatedBy(sf::degrees((float)distr(gen)));
	}

	if (pos.x > m_window_width)
	{
		m_ball.setPosition(m_ball_position);
		m_velocity = reset_ball({ -1.f, 0.f });
		m_player_score[p_left]++;
	}
	else if (pos.x < 0)
	{
		m_ball.setPosition(m_ball_position);
		m_velocity = reset_ball({ 1.f, 0.f });
		m_player_score[p_right]++;
	}
}


/*void Game::ball_collision_processing() {*/

// 	Segment segment1;
// 	Segment segment2;
// 	Segment segment_ball;
// 	Segment segment_ball2;
// 	sf::Vector2f intersection_point;
// 	sf::Vector2f player1_pos = player1.getPosition();
// 
// 	segment1.p1 = player1_pos;
// 	player1_pos.x += m_player_width;
// 	player1_pos.y += m_player_height;
// 	segment1.p2 = player1_pos;
// 
// 	sf::Vector2f player2_pos = player2.getPosition();
// 	segment2.p1 = player2_pos;
// 	player2_pos.y += m_player_height;
// 	player2_pos.x += m_player_width;
// 	segment2.p2 = player2_pos;

// 	uint32_t n = uint32_t(m_round_time.count() / m_ball_speed_step_duration);
// 
// 	float new_ball_speed = m_ball_starting_speed + m_ball_speed_step * n;

// 	segment_ball.p1 = m_ball.getPosition();
// 	sf::Vector2f vel = m_velocity * new_ball_speed;
// 	segment_ball.p2 = segment_ball.p1 + m_dt.count() * vel;		
// 
// 	segment_ball2.p1 = m_ball.getPosition();
// 	segment_ball2.p1.x += m_ball_size*2;
// 
// 	segment_ball2.p2 = segment_ball2.p1 + m_dt.count() * vel;
// 
// 	sf::Vector2f pos = m_ball.getPosition();
// 	LOG_INFO("[%d] ball_collision_processing() seg1[p1=(%f,%f), p2=(%f,%f)], seg_ball[p1=(%f,%f), p2=(%f,%f)]", m_frame_id, v2push(segment1.p1), v2push(segment1.p2), v2push(segment_ball.p1), v2push(segment_ball.p2));
// 	//LOG_INFO("[%d] dist=%f", m_frame_id, (segment_ball.p1 - segment_ball.p2).length());
// 	LOG_INFO("[%d] ball_pos(%f,%f), seg.p1=(%f,%f)", m_frame_id, pos.x, pos.y, segment_ball.p1.x, segment_ball.p1.y);
// 	if (pos.y <= (m_header_height + m_ball_size))
// 	{
// 		m_velocity = reflect_ball(ct_top);
// 	}
// 	else if (pos.y >= (m_window_height-m_ball_size))
// 	{
// 		m_velocity = reflect_ball(ct_bottom);
// 	}
// 	else if (Intersect(segment1, segment_ball, intersection_point) != IntersectionResult::None) {
// 		m_velocity = reflect_ball(ct_left);
// 		m_velocity = m_velocity.rotatedBy(sf::degrees((float)distr(gen)));
// 		LOG_INFO("intersected p1");
// 	}
// 	else if (Intersect(segment2, segment_ball2, intersection_point) != IntersectionResult::None) {
// 		m_velocity = reflect_ball(ct_right);
// 		m_velocity = m_velocity.rotatedBy(sf::degrees((float)distr(gen)));
// 		LOG_INFO("intersected p2");
// 	}
// 
// 	if (pos.x > m_window_width )
// 	{
// 		m_ball.setPosition(m_ball_position);
// 		m_velocity = reset_ball({ -1.f, 0.f });
// 		m_player_score[p_left]++;
// 	}
// 	else if (pos.x < 0)
// 	{
// 		m_ball.setPosition(m_ball_position);
// 		m_velocity = reset_ball({ 1.f, 0.f });
// 		m_player_score[p_right]++;
// 	}
// 
// 	if (player1.getGlobalBounds().findIntersection(m_ball.getGlobalBounds()))
// 	{
// 		LOG_INFO("intersection SFML p1");
// 	}
// 	if (player2.getGlobalBounds().findIntersection(m_ball.getGlobalBounds()))
// 	{
// 		LOG_INFO("intersection SFML p2");
// 	}
// }

sf::Vector2f Game::reflect_ball(Game::collision_type type) const{

	sf::Vector2f normal = m_collision_normals[type];
	sf::Vector2f reversed_move = -m_velocity;
	sf::Vector2f reflected = (2.f * (normal.dot(reversed_move))) * normal - reversed_move;
	reflected = reflected.normalized();

	return reflected;
}

sf::Vector2f Game::reset_ball(sf::Vector2f velocity){
	m_round_time = std::chrono::nanoseconds::zero();
	int random = distr(gen);
	sf::Angle ang = sf::degrees(((m_ball_vel_sign ? -1 : 1) * 45.f) + random);
	m_ball_vel_sign = !m_ball_vel_sign;
	velocity = velocity.rotatedBy(ang);
	return velocity;
}


