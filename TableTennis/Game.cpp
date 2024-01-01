#include "Game.h"
#include<iostream>
#include <algorithm>

Game* g_Game = nullptr;
std::unique_ptr<sf::RenderWindow> Game::m_window = nullptr;

void Game::run()
{
	m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(m_window_width, m_window_height), "Ping-Pong");
	
	initialize();

	while (m_window->isOpen()) {	

		inputManager.gather_input(m_window);
		process_inputs(inputManager.get_current_input_state());
		update();
		draw();
	}
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

	m_entities.emplace_back(std::make_shared<Player>(Vector2f(100.f, 340.f), 
		m_entities.size(), GameEntity::entity_type::player, Player::player_type::left));
	m_entities.emplace_back(std::make_shared<Player>(Vector2f(600.f, 340.f), 
		m_entities.size(), GameEntity::entity_type::player, Player::player_type::right));
	m_entities.emplace_back(std::make_shared<Ball>(Vector2f(350.f, 400.f), m_entities.size(),
		GameEntity::entity_type::ball));
	m_entities.back()->addObserver(&observer);
	m_entities.emplace_back(std::make_shared<Wall>(Vector2f(0.f, 100.f), 
		m_entities.size(), GameEntity::entity_type::wall, Wall::type::top));
	m_entities.emplace_back(std::make_shared<Wall>(Vector2f(0.f, 698.f), 
		m_entities.size(), GameEntity::entity_type::wall, Wall::type::bottom));
	m_entities.emplace_back(std::make_shared<Wall>(Vector2f(0.f, 100.f),
		m_entities.size(), GameEntity::entity_type::wall, Wall::type::left));
	m_entities.emplace_back(std::make_shared<Wall>(Vector2f(698.f, 100.f), 
		m_entities.size(), GameEntity::entity_type::wall, Wall::type::right));
	
	for (auto& entity : m_entities) {
		entity->initialize();
	}

	m_physics_scene->initialize(m_window_width, m_window_height);

	if (!m_font.loadFromFile("arial.ttf"))
	{
		int ii = 10;
	}	

	m_score_text.setFont(m_font);
	m_score_text.setCharacterSize(40);
	m_score_text.setFillColor(m_sprite_color);
	m_score_text.setPosition(sf::Vector2f(245.f, 25.f));
	m_score_text.setString(std::string("Score ") + std::to_string (m_player_score[p_left]) + " : " + std::to_string(m_player_score[p_right]));
}

void Game::draw()
{	
	m_window->clear();
	for (auto& entity : m_entities) {
		entity->draw(m_window);
	}
	m_window->draw(m_score_text);
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

	float delta = std::min(m_dt.count(), 0.0166f);
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
		// handle hits
		std::vector<PhysicsScene::hit_info> hitInfos;
		m_physics_scene->get_hit_info(hitInfos);		
		for (int i = 0; i < hitInfos.size(); i++) {
			std::shared_ptr<IGameEntity> owner_entity =	hitInfos[i].actor->get_owner().lock();
			std::shared_ptr<IGameEntity> entity_hit = hitInfos[i].actor_hit->get_owner().lock();			

			if (owner_entity) {
				owner_entity->onHit(hitInfos[i].normal, entity_hit);
			}
		}

		m_score_text.setFillColor(sf::Color::Green);

		for (auto& entity : m_entities) {

			if (MovableEntity* mov_ent = entity->asMovableEntity()) {
				mov_ent->update(delta, m_round_time.count());
			}			
		}	

		m_physics_scene->update(delta, m_round_time.count());
	}
}

std::shared_ptr<IPhysicActor> Game::create_dynamic_actor(uint32_t entity_id)
{
	return m_physics_scene->create_dynamic_actor(m_entities[entity_id]);
}

std::shared_ptr<IPhysicActor> Game::create_static_actor(uint32_t entity_id)
{
	return m_physics_scene->create_static_actor(m_entities[entity_id]);
}

bool Game::overlap(const BoundingBox& bb, 
	const std::shared_ptr<IPhysicActor>& ignore_actor, 
	bool dynamic, bool stat,
	std::vector<std::shared_ptr<IPhysicActor>>& actors_hit)
{
	return m_physics_scene->overlap(bb, ignore_actor, dynamic, stat, actors_hit);
}

void Game::add_score(Game::player player_score)
{	
	m_player_score[player_score]++;
}

void Game::process_inputs(const InputManager::input_array& my_input_array)
{
	InputManager::input_array input_state = inputManager.get_previous_input_state();

	if (my_input_array[InputManager::input::key_Pause] && !input_state[InputManager::input::key_Pause])
	{
		if (m_game_status == game_status::ingame) {
			m_game_status = game_status::pause;
		}
		else {
			m_game_status = game_status::ingame;
		}
	}

	if (my_input_array[InputManager::input::key_W] != input_state[InputManager::input::key_W])
	{
		if (!input_state[InputManager::input::key_W] && my_input_array[InputManager::input::key_W])
		{
			m_playerL_velocity_change = velocity_up;
		}
		else if (!my_input_array[InputManager::input::key_S]) {
			m_playerL_velocity_change = velocity_stop;
		}
		else if (my_input_array[InputManager::input::key_S])
		{
			m_playerL_velocity_change = velocity_down;
		}
	}

	if (my_input_array[InputManager::input::key_S] != input_state[InputManager::input::key_S])
	{
		if (!input_state[InputManager::input::key_S] && my_input_array[InputManager::input::key_S])
		{
			m_playerL_velocity_change = velocity_down;
		}
		else if (!my_input_array[InputManager::input::key_W]) {
			m_playerL_velocity_change = velocity_stop;
		}
		else if (my_input_array[InputManager::input::key_W])
		{
			m_playerL_velocity_change = velocity_up;
		}
	}

	if (my_input_array[InputManager::input::key_Up] != input_state[InputManager::input::key_Up])
	{
		if (!input_state[InputManager::input::key_Up] && my_input_array[InputManager::input::key_Up])
		{
			m_playerR_velocity_change = velocity_up;
		}
		else if (!my_input_array[InputManager::input::key_Down]) {

			m_playerR_velocity_change = velocity_stop;
		}
		else if (my_input_array[InputManager::input::key_Down])
		{
			m_playerR_velocity_change = velocity_down;
		}
	}

	if (my_input_array[InputManager::input::key_Down] != input_state[InputManager::input::key_Down])
	{
		if (!input_state[InputManager::input::key_Down] && my_input_array[InputManager::input::key_Down])
		{
			m_playerR_velocity_change = velocity_down;
		}
		else if (!my_input_array[InputManager::input::key_Up]) {

			m_playerR_velocity_change = velocity_stop;
		}
		else if (my_input_array[InputManager::input::key_Up])
		{
			m_playerR_velocity_change = velocity_up;
		}
	}
}




