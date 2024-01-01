#include "InputManager.h"

void InputManager::gather_input(std::unique_ptr<sf::RenderWindow>& window)
{
	// check all the window's events that were triggered since the last iteration of the loop
	sf::Event event;
	m_previous_input_state = m_current_input_state;

	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed: update_input_states(event.key.code, true); break;
		case sf::Event::KeyReleased: update_input_states(event.key.code, false); break;
		}
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

void InputManager::update_input_states(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W) {
		m_current_input_state[key_W] = isPressed;
	}
	else if (key == sf::Keyboard::S) {
		m_current_input_state[key_S] = isPressed;
	}
	else if (key == sf::Keyboard::Up) {
		m_current_input_state[key_Up] = isPressed;
	}
	else if (key == sf::Keyboard::Down) {
		m_current_input_state[key_Down] = isPressed;
	}
	else if (key == sf::Keyboard::Space) {
		m_current_input_state[key_Pause] = isPressed;
	}
}




