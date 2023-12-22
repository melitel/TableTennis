#include "Game.h"
#include<iostream>

Game* g_Game = nullptr;
std::unique_ptr<sf::RenderWindow> Game::m_window = nullptr;

void Game::run()
{
	m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(m_window_width, m_window_height), "Ping-Pong");
	
	initialize();

	while (m_window->isOpen()) {	

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		input_array my_input_array{ m_input_state };
		

		while (m_window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed: handlePlayerInput(event.key.code, true, my_input_array); break;
			case sf::Event::KeyReleased: handlePlayerInput(event.key.code, false, my_input_array); break;
			}
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
			m_window->close();
		}

		// process events
		process_inputs(my_input_array);
		my_input_array.swap(m_input_state);
		update();
		draw();
	}
}

std::shared_ptr<PhysicActor> Game::create_physic_actor(uint32_t entity_id)
{
	return m_physics_scene->create_actor(m_entities[entity_id]);
}

void Game::initialize()
{
	g_Game = this;
	m_physics_scene = std::make_shared<PhysicsScene>();
	m_window->setVerticalSyncEnabled(true);
	m_start_time = std::chrono::system_clock::now();
	// clear the window with black color
	m_window->clear(sf::Color::Black);
	m_game_status = game_status::pause;

	m_entities.emplace_back(std::make_shared<Player>(sf::Vector2f(100.f, 340.f), m_entities.size()));
	m_entities.emplace_back(std::make_shared<Ball>(sf::Vector2f(350.f, 400.f), m_entities.size()));
	m_entities.emplace_back(std::make_shared<Wall>(sf::Vector2f(0.f, 102.f), m_entities.size()));
	m_entities.emplace_back(std::make_shared<Wall>(sf::Vector2f(0.f, 699.f), m_entities.size()));
	
	for (auto& entity : m_entities) {
		entity->initialize();
	}

	m_physics_scene->initialize(m_window_width, m_window_height - m_header_height);

	if (!m_font.loadFromFile("arial.ttf"))
	{
		int ii = 10;
	}	

	m_score_text.setFont(m_font);
	m_score_text.setCharacterSize(40);
	m_score_text.setFillColor(m_sprite_color);
	m_score_text.setPosition(sf::Vector2f(245.f, 25.f));
	m_score_text.setString(std::string("Score ") + std::to_string (m_player_score[p_left]) + " : " + std::to_string(m_player_score[p_right]));

	border.setSize(sf::Vector2f((float)m_window_width, 2.f));
	border.setFillColor(m_sprite_color);
	border.setPosition(sf::Vector2f(0.f, 100.f));
}

void Game::draw()
{	
	m_window->clear();
	for (auto& entity : m_entities) {
		entity->draw(m_window);
	}
	m_window->draw(m_score_text);
	m_window->draw(border);
	m_window->display();
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

	m_score_text.setString(std::string("Score ") + std::to_string(m_player_score[p_left]) + " : " + std::to_string(m_player_score[p_right]));
	
	if (m_game_status == game_status::pause)
	{
		m_score_text.setFillColor(sf::Color::Red);
	}
	else
	{
		m_score_text.setFillColor(sf::Color::Green);
		for (auto& entity : m_entities) {
			entity->update(delta, m_round_time.count());
		}

		//m_ball_sprite.update(delta, m_round_time.count());
		//m_player_sprite.update(delta, m_round_time.count());
		//Add update for second player or Ai

		/* this is the check for player if he is within the bounding box
			should be moved to Physics Scene*/
		//sf::Vector2f pos = m_player_sprite.get_position();
		//pos.y = std::clamp(pos.y, m_header_height, m_window_height - m_player_sprite.get_height());
		//m_player_sprite.set_position(pos);

		//m_physics_scene.update(delta, m_round_time.count());
	}

}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed, input_array& my_input_array)
{
	if (key == sf::Keyboard::W) {
		my_input_array[key_W] = isPressed;
	}
	else if (key == sf::Keyboard::S) {
		my_input_array[key_S] = isPressed;
	}
	else if (key == sf::Keyboard::Up) {
		my_input_array[key_Up] = isPressed;
	}
	else if (key == sf::Keyboard::Down) {
		my_input_array[key_Down] = isPressed;
	}
	else if (key == sf::Keyboard::Space) {
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

	if (my_input_array[key_W] != m_input_state[key_W])
	{
		if (!m_input_state[key_W] && my_input_array[key_W])
		{
			m_player_velocity_change = velocity_up;
		}
		else if (!my_input_array[key_S]) {
			m_player_velocity_change = velocity_stop;
		}
		else if (my_input_array[key_S])
		{
			m_player_velocity_change = velocity_down;
		}
	}

	if (my_input_array[key_S] != m_input_state[key_S])
	{
		if (!m_input_state[key_S] && my_input_array[key_S])
		{
			m_player_velocity_change = velocity_down;
		}
		else if (!my_input_array[key_W]) {
			m_player_velocity_change = velocity_stop;
		}
		else if (my_input_array[key_W])
		{
			m_player_velocity_change = velocity_up;
		}
	}

	//process input for second player or Ai

	//if (my_input_array[key_Left] != m_input_state[key_Left])
	//{
	//	if (!m_input_state[key_Left] && my_input_array[key_Left])
	//	{
	//		m_player2_velocity.y = -1.f;
	//	}
	//	else if (!my_input_array[key_Right]) {

	//		m_player2_velocity.y = 0.f;
	//	}
	//	else if (my_input_array[key_Right])
	//	{
	//		m_player2_velocity.y = 1.f;
	//	}
	//}

	//if (my_input_array[key_Right] != m_input_state[key_Right])
	//{
	//	if (!m_input_state[key_Right] && my_input_array[key_Right])
	//	{
	//		m_player2_velocity.y = 1.f;
	//	}
	//	else if (!my_input_array[key_Left]) {

	//		m_player2_velocity.y = 0.f;
	//	}
	//	else if (my_input_array[key_Left])
	//	{
	//		m_player2_velocity.y = -1.f;
	//	}
	//}
}


