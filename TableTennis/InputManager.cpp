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
		case sf::Event::KeyPressed: update_input_states(event.key.code, input_type::keyboard, true, sf::Vector2i(0, 0)); break;
		case sf::Event::KeyReleased: update_input_states(event.key.code, input_type::keyboard, false, sf::Vector2i(0, 0)); break;
		case sf::Event::MouseButtonReleased: 
			sf::Vector2i pos = sf::Mouse::getPosition(*window);
			update_input_states(event.mouseButton.button, input_type::mouse, true, pos); 
			break;
		}
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
			window->close();
	}

	check_for_keyboard_events();
}

void InputManager::check_for_keyboard_events()
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

void InputManager::check_for_mouse_events(sf::Vector2i pos)
{
	sf::FloatRect btn1_bounds = g_Game->get_menu_button1_bounds();
	sf::FloatRect btn2_bounds = g_Game->get_menu_button2_bounds();

	if (btn1_bounds.contains(sf::Vector2f(pos)))
	{
		createEvent(InputEvent::playerVSplayer_start);
	}
	if (btn2_bounds.contains(sf::Vector2f(pos)))
	{
		createEvent(InputEvent::playerVSai_start);
	}
}

void InputManager::createEvent(InputEvent::event_type type)
{
	std::shared_ptr<IEvent> event = std::make_shared<InputEvent>(type);
	g_Game->create_event(event);
}

void InputManager::update_input_states(input_event input,
	input_type inputType, bool isPressed, sf::Vector2i pos)
{
	if (inputType == keyboard) {

		sf::Keyboard::Key key = std::get<sf::Keyboard::Key>(input);

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
	else if (inputType == mouse) {

		sf::Mouse::Button button = std::get<sf::Mouse::Button>(input);		
	
		if (button == sf::Mouse::Left) {
			check_for_mouse_events(pos);
		}
	}

}




