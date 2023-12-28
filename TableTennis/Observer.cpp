#include "Observer.h"
#include "Game.h"
#include "Ball.h"

extern Game* g_Game;

void Observer::ballOut(Ball* ball, const Vector2f& vel, int player_score)
{
	ball->reset(vel);

	if (player_score == 1) {
		g_Game->add_score(Game::player::p_right);	
	}
	else if (player_score == 0){
		g_Game->add_score(Game::player::p_left);
	}

}
