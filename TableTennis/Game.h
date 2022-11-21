#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <array>
#include <random>
#include "Logger.h"

class Game
{
public:
	void run();

private:

	enum input { key_A, key_D, key_Left, key_Right, key_Pause, key_count };
	using input_array = std::array<bool, key_count>;

	void initialize();
	void draw();
	void update();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed, input_array& my_input_array);
	void process_inputs(const input_array& my_input_array);
	void object_move(sf::Shape& shape, const sf::Vector2f& velocity, float speed, float delta);	
	
	bool intersects(sf::Shape& rect1, sf::Shape& rect2);

	void ball_collision_processing();
	enum player { p_left, p_right, p_count };
	
	enum class game_status {ingame, pause};
	enum collision_type {ct_left, ct_right, ct_top, ct_bottom, ct_count};
	std::array <sf::Vector2f, ct_count> m_collision_normals;
	sf::Vector2f reflect_ball(Game::collision_type type) const;
	sf::Vector2f reset_ball(sf::Vector2f velocity);
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen{ rd() }; // seed the generator
	std::uniform_int_distribution<> distr{ -10, 10 }; // define the range
	bool m_ball_vel_sign{ false };
	input_array m_input_state{ false }; 
	

	//SFML graphics objects
	const uint32_t m_window_width = 700;
	const uint32_t m_window_height = 700;
	const float m_player_width = 15.f;
	const float m_player_height = 120.f;
	const float m_header_height = 100.f;
	const float m_player_speed = 500.f;
	float m_ball_speed;
	const float m_ball_speed_step = 50.f;
	const float m_ball_starting_speed = 100.f;
	const uint32_t m_ball_speed_step_duration = 3;
	const float m_ball_size = 7.f;

	sf::RenderWindow m_window{ sf::VideoMode(sf::Vector2u(m_window_width, m_window_height)), "My window" };
	const sf::Color sprite_color{ 255, 255, 255 };
	sf::RectangleShape player1;
	sf::RectangleShape player2;
	sf::RectangleShape border;
	sf::CircleShape m_ball{ m_ball_size };
	sf::Text m_score_text;
	sf::Font m_font;
	sf::Vector2f m_velocity{ 1.f, 1.f };
	sf::Vector2f m_player1_velocity{ 0.f, 0.f };
	sf::Vector2f m_player2_velocity{ 0.f, 0.f };
	sf::Vector2f m_ball_position{ 350.f, 400.f };
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