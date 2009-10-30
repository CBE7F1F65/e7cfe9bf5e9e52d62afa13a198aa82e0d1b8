#include "Player.h"
#include "Scripter.h"

void Player::_Bomb()
{
	scr.Execute(SCR_EVENT, SCR_EVENT_PLAYERBOMB, bombtimer);
}