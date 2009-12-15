#include "Process.h"
#include "Scripter.h"
#include "BGLayer.h"
#include "SelectSystem.h"
#include "BGLayer.h"
#include "Player.h"
#include "SE.h"
#include "BossInfo.h"
#include "FrontDisplay.h"
#include "GameInput.h"

int Process::processStart()
{
//	frameStart();
	
	if (replaymode && (!Player::able/* || scene == S1*/))
	{
		replayend = true;
		replaymode = false;
//		scene = S1;
		gametime = 0;
		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
		{
			BGLayer::KillOtherLayer(i);
			BGLayer::ubg[i][UBGID_BGMASK].exist = false;
		}
		SelectSystem::ClearAll();
		FrontDisplay::fdisp.SetState(FDISP_PANEL, 0);
		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
		{
			Player::p[i].exist = false;
		}
		state = STATE_REPLAY;
		return PTURN;
	}
	if(!Player::able && !replaymode)
	{
//		Scripter::scr.SetIntValue(SCR_RESERVEBEGIN, 0);
		state = STATE_CONTINUE;
		return PTURN;
	}
	else
	{
		frameStart();
		if (state == STATE_START)
		{
			Scripter::scr.Execute(SCR_CONTROL, STATE_START, gametime);
		}
	}

	/*
	if(GameInput::GetKey(0, KSI_PAUSE, DIKEY_DOWN) && state != STATE_CLEAR)
	{
		SE::push(SE_SYSTEM_PAUSE);

		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
		{
			BGLayer::ubg[i][UBGID_FGPAUSE].exist = true;
			BGLayer::ubg[i][UBGID_FGPAUSE].SetFlag(FG_PAUSEIN, FGMT_PAUSE);
		}

		state = STATE_PAUSE;
		return PTURN;
	}
	*/

	/*
	if(scene > S1 && state != STATE_CLEAR)
	{
		gametime = 0;
		state = STATE_CLEAR;
		return PTURN;
	}
	*/
// Script::Stage

	return PGO;
}
