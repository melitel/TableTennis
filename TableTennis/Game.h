#pragma once
#include "Logger.h"
#include "PhysicsScene.h"
#include "IGameEntity.h"
#include "GameEntity.h"
#include "Player.h"
#include "Ball.h"
#include "Wall.h"
#include "Observer.h"
#include "InputManager.h"
#include "IEvent.h"

class Game
{
public:
	void run();
	std::shared_ptr<IPhysicActor> create_dynamic_actor(uint32_t entity_id);
	std::shared_ptr<IPhysicActor> create_static_actor(uint32_t entity_id);
	void create_event(std::shared_ptr<IEvent>& event);
	bool overlap(const BoundingBox& bb, 
		const std::shared_ptr<IPhysicActor>& ignore_actor, 
		bool dynamic, bool stat, 
		std::vector<std::shared_ptr<IPhysicActor>>& actors_hit);

	float get_playerL_velocity_requested() const {
		return m_playerL_velocity_change;
	}

	void change_playerL_velocity(float vel) {
		m_playerL_velocity_change = vel;
	}

	float get_playerR_velocity_requested() const {
		return m_playerR_velocity_change;
	}

	void change_playerR_velocity(float vel) {
		m_playerR_velocity_change = vel;
	}

	const std::shared_ptr<PhysicsScene>& physic_scene() const {
		return m_physics_scene;
	}

	void game_pause();

	enum player { p_left, p_right, p_count };

	void add_score(player player_score);

private:	

	Observer observer;
	InputManager inputManager;
	std::shared_ptr<PhysicsScene> m_physics_scene;

	void initialize();
	void draw();
	void update();	
	
	enum class game_status {ingame, pause};	
	
	uint32_t m_window_width = 700;
	uint32_t m_window_height = 700;
	const float m_header_height = 100.f;
	float velocity_up = -1.f;
	float velocity_down = 1.f;
	float velocity_stop = 0.f;
	float m_playerL_velocity_change = 0.f;
	float m_playerR_velocity_change = 0.f;

	const sf::Color m_sprite_color{ 255, 255, 255 };	

	static std::unique_ptr<sf::RenderWindow> m_window;
	std::vector<std::shared_ptr<IGameEntity>> m_entities;
	std::vector<std::shared_ptr<IEvent>> m_events;

	sf::RectangleShape border;
	
	sf::Text m_score_text;
	sf::Font m_font;
	game_status m_game_status;
	std::array<uint32_t, p_count> m_player_score{ 0 };

	//time logic
	std::chrono::time_point<std::chrono::system_clock> m_time { std::chrono::system_clock::now() };
	std::chrono::time_point<std::chrono::system_clock> m_start_time{ std::chrono::system_clock::now() };
	std::chrono::duration<float> m_total_time{ 0 };
	std::chrono::duration<float> m_round_time{ 0 };
	std::chrono::duration<float> m_dt{ 0 };
	uint64_t m_frame_id{ 0 };

	logger m_logger{"game.log", logger::log_level::ll_INFO};
	
};