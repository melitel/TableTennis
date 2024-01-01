#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <array>

class InputManager
{
public:
	enum input { key_W, key_S, key_Up, key_Down, key_Pause, key_count };
	using input_array = std::array<bool, key_count>;

	void gather_input(std::unique_ptr<sf::RenderWindow>& window);
	const input_array& get_previous_input_state() const {
		return m_previous_input_state;
	}
	const input_array& get_current_input_state() const {
		return m_current_input_state;
	}

private:

	input_array m_current_input_state{ false };
	input_array m_previous_input_state{ false };
	void update_input_states(sf::Keyboard::Key key, bool isPressed);	
};

