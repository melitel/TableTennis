#pragma once
#include "IEvent.h"

class InputEvent :
	public IEvent
{
public:
		
	enum event_type {
		first_player_up, 
		first_player_stop,
		first_player_down,
		second_player_up,
		second_player_stop,
		second_player_down,
		pause,
	};

	InputEvent(event_type type) : m_event_type(type) { }

	void onEvent() override;

	event_type get_type() const {
		return m_event_type;
	}

private:
	event_type m_event_type;
	float velocity_up = -1.f;
	float velocity_down = 1.f;
	float velocity_stop = 0.f;
};

//class RoundEndEvent :
//	public IEvent
//{
//public:
//	void onEvent() override;
//
//};