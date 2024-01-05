#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include "Events.h"
#include <variant>

class InputManager
{
public:
	enum input { key_W, key_S, key_Up, key_Down, key_Pause, mouse_left, key_count };
	using input_array = std::array<bool, key_count>;
	enum input_type {keyboard, mouse};

	void gather_input(std::unique_ptr<sf::RenderWindow>& window);
	const input_array& get_previous_input_state() const {
		return m_previous_input_state;
	}
	const input_array& get_current_input_state() const {
		return m_current_input_state;
	}

	void check_for_keyboard_events();
	void check_for_mouse_events(sf::Vector2i pos);

private:
	
	void createEvent(InputEvent::event_type type);
	input_array m_current_input_state{ false };
	input_array m_previous_input_state{ false };
	void update_input_states(std::variant<sf::Keyboard::Key, sf::Mouse::Button> input, input_type inputType, bool isPressed, sf::Vector2i pos);
};

