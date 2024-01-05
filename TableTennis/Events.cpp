#include "Events.h"
#include "Game.h"

extern Game* g_Game;

void InputEvent::onEvent()
{
	switch (m_event_type)
	{
	case first_player_up:
		g_Game->change_playerL_velocity(velocity_up);
		break;
	case first_player_stop:
		g_Game->change_playerL_velocity(velocity_stop);
		break;
	case first_player_down:
		g_Game->change_playerL_velocity(velocity_down);
		break;
	case second_player_up:
		g_Game->change_playerR_velocity(velocity_up);
		break;
	case second_player_stop:
		g_Game->change_playerR_velocity(velocity_stop);
		break;
	case second_player_down:
		g_Game->change_playerR_velocity(velocity_down);
		break;
	case pause:
		g_Game->game_pause();
		break;
	case playerVSplayer_start:
		g_Game->playerVSplayer_start();
		break;
	case playerVSai_start:
		g_Game->playerVSai_start();
		break;
	default:
		break;
	}
}

void RoundEndEvent::onEvent()
{
	switch (m_event_type)
	{
		case first_player_point:
			g_Game->add_score(Game::player::p_left);
			break;
		case second_player_point:
			g_Game->add_score(Game::player::p_right);
			break;
		default:
			break;
	}
}
