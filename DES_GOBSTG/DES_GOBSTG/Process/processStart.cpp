#include "Process.h"
#include "Scripter.h"
#include "BGLayer.h"
#include "SelectSystem.h"
#include "BGLayer.h"
#include "Player.h"
#include "SE.h"
#include "BossInfo.h"
#include "FrontDisplay.h"

int Process::processStart()
{
	/*
	if (replaymode && (!Player::p[0].exist || scene == S1))
	{
		replayend = true;
		replaymode = false;
		scene = S1;
		time = 0;
//		musicChange(0, true);
		BGLayer::KillOtherLayer();
		SelectSystem::ClearAll();
		BGLayer::ubg[UBGID_BGMASK].exist = false;
		Fdisp.SetState(FDISP_PANEL, 0);
		Fdisp.SetState(FDISP_NEXTSTAGE, 0);
		Player::p[0].exist = false;
//		getInput();
		state = STATE_REPLAY;
		return PTURN;
	}
	if(!Player::p[0].exist && !replaymode)
	{
		if(spellmode && time != 0)
		{
			time = 0;
			clearPrep(false);
			Player::p[0].exist = false;
			hge->Input_SetDIKey(KS_PAUSE);
		}
		else
		{
			scr.SetIntValue(SCR_RESERVEBEGIN, 0);
			state = STATE_CONTINUE;
			return PTURN;
		}
	}
	else
		frameStart();

	if(hge->Input_GetDIKey(KS_PAUSE, DIKEY_DOWN) && !(Player::p[0].flag & PLAYER_SHOT) && state != STATE_CLEAR && !BossInfo::allover)
	{
		saveInput = nowInput;
		SE::push(SE_SYSTEM_PAUSE);

		BGLayer::ubg[UBGID_FGPAUSE].exist = true;
		BGLayer::ubg[UBGID_FGPAUSE].SetFlag(FG_PAUSEIN, FGMT_PAUSE);

		state = STATE_PAUSE;
	}

	if(scene > S1 && state != STATE_CLEAR)
	{
		time = 0;
		state = STATE_CLEAR;
		return PTURN;
	}

	if(time != lasttime && state != STATE_CLEAR)
	{
		if (!(stopflag & FRAME_STOPFLAG_ENEMYSET))
		{
			scr.Execute(SCR_STAGE, scene, time);
		}
	}
	*/
	return PGO;
}
