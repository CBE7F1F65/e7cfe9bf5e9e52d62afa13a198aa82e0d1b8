#include "Process.h"
#include "Player.h"
#include "DataConnector.h"
#include "BGLayer.h"
#include "Replay.h"
#include "FrontDisplay.h"
#include "Data.h"
#include "Scripter.h"

#define _PCLEAR_FDISP_TIME			240
#define _PCLEAR_FDIPS_CANCELTIME	60

int Process::processClear()
{
	if (!alltime)
	{
		alltime = gametime;
	}
	processStart();
	Scripter::scr.Execute(SCR_CONTROL, STATE_CLEAR, gametime-alltime);
	/*
	if(gametime == 1)
	{
		frameskip = M_DEFAULT_FRAMESKIP;

		BGLayer::ubg[UBGID_FGPAUSE].exist = true;
		BGLayer::ubg[UBGID_FGPAUSE].SetFlag(FG_PAUSEIN);

		LONGLONG tscore = 0;

		BYTE tstage;
		bool islast = false;
		if(scene - SCLEAR > S1)
		{
			tstage = 0xff;
			islast = true;
		}
		else
			tstage = (scene - SCLEAR) / M_STAGENSCENE;

		musicSlide(1.0f);
		if(islast)
		{
			DataConnector::Clear();
			tscore += Player::p[0].getAllClearBonusLife();
			tscore += Player::p[0].getAllClearBonusPower();
		}
		tscore += Player::p[0].getClearBonusPoint();
		tscore += Player::p[0].getClearBonusGraze();
		tscore += Player::p[0].getClearBonusFaith();
		tscore += Player::p[0].getClearBonusStage(tstage);

		Player::p[0].nScore += tscore;

		FrontDisplay::fdisp.SetValue(tscore, 0, 0, (!islast) && (!practicemode));
		FrontDisplay::fdisp.SetState(FDISP_NEXTSTAGE, _PCLEAR_FDISP_TIME);
	}

	if (gametime == _PCLEAR_FDIPS_CANCELTIME)
	{
//		musicChange(0, true);
	}

	if(gametime > _PCLEAR_FDISP_TIME  || gametime > _PCLEAR_FDIPS_CANCELTIME && hge->Input_GetDIKey(KS_FIRE, DIKEY_DOWN))
	{
		FrontDisplay::fdisp.SetState(FDISP_NEXTSTAGE, 0);
		BGLayer::ubg[UBGID_FGPAUSE].exist = false;

		scene -= SCLEAR;
		BYTE tpart;
		bool islast = false;

		if(scene > S1)
		{
			tpart = 0xff;
			islast = true;
		}
		else
		{
			if (scene > S1200)
			{
				tpart = RPYPARTMAX - 1;
			}
			else
			{
				tpart = data.getStage(scene) - 1;
			}
		}

		if(!replaymode)
		{
			seed = timeGetTime();
			rpy.partFill(tpart);
		}
		gametime = 0;
		if (!replaymode)
		{
			if (practicemode)
			{
				state = STATE_OVER;
				return PTURN;
			}
			else if (islast)
			{
				state = STATE_ENDING;
				return PTURN;
			}
		}
		state = STATE_START;
		if(islast)
		{
			scene = S1;
		}
		else
		{
			DataConnector::Try();
		}

		clearPrep();
		if(replaymode && tpart != 0xff)
		{
			seed = rpy.partinfo[tpart].seed;
		}

		srandt(seed);

		return PTURN;
	}
	*/

	return PGO;
}