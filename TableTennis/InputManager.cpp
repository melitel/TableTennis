#include "InputManager.h"
#include "Game.h"

extern Game* g_Game;

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

	check_for_events();
}

void InputManager::check_for_events()
{
	if (m_current_input_state[key_W] != m_previous_input_state[key_W])
	{
		if (!m_previous_input_state[key_W] && m_current_input_state[key_W])
		{
			//first player up Event
			createEvent(InputEvent::first_player_up);
		}
		else if (!m_current_input_state[key_S]) {
			//first player stop event
			createEvent(InputEvent::first_player_stop);
		}
		else if (m_current_input_state[key_S])
		{
			//first player down event
			createEvent(InputEvent::first_player_down);
		}
	}
	if (m_current_input_state[key_S] != m_previous_input_state[key_S])
	{
		if (!m_previous_input_state[key_S] && m_current_input_state[key_S])
		{
			//first player down event
			createEvent(InputEvent::first_player_down);
		}
		else if (!m_current_input_state[key_W]) {
			//first player stop event
			createEvent(InputEvent::first_player_stop);
		}
		else if (m_current_input_state[key_W])
		{
			//first player up Event
			createEvent(InputEvent::first_player_up);
		}
	}
	if (m_current_input_state[key_Up] != m_previous_input_state[key_Up])
	{
		if (!m_previous_input_state[key_Up] && m_current_input_state[key_Up])
		{
			//second player up Event
			createEvent(InputEvent::second_player_up);
		}
		else if (!m_current_input_state[key_Down]) {

			//second player stop Event
			createEvent(InputEvent::second_player_stop);
		}
		else if (m_current_input_state[key_Down])
		{
			//second player down Event
			createEvent(InputEvent::second_player_down);
		}
	}
	if (m_current_input_state[key_Down] != m_previous_input_state[key_Down])
	{
		if (!m_previous_input_state[key_Down] && m_current_input_state[key_Down])
		{
			//second player down Event
			createEvent(InputEvent::second_player_down);
		}
		else if (!m_current_input_state[key_Up]) {

			//second player stop Event
			createEvent(InputEvent::second_player_stop);
		}
		else if (m_current_input_state[key_Up])
		{
			//second player up Event
			createEvent(InputEvent::second_player_up);
		}
	}
	if (m_current_input_state[key_Pause] && !m_previous_input_state[key_Pause]) {
		//pause Event	
		createEvent(InputEvent::pause);
	}

}

void InputManager::createEvent(InputEvent::event_type type)
{
	std::shared_ptr<IEvent> event = std::make_shared<InputEvent>(type);
	g_Game->create_event(event);
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




