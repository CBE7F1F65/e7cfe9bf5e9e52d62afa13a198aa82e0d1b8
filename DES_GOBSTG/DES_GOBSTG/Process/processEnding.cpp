#include "Process.h"
#include "BGLayer.h"
#include "Player.h"
#include "Scripter.h"
#include "Data.h"
#include "SelectSystem.h"
#include "FrontDisplay.h"

int Process::processEnding()
{
	gametime++;
	return PGO;
	/*
	if (gametime == 1)
	{
		BGLayer::KillOtherLayer();

		Player::p[0].exist = false;
		BGLayer::ubg[UBGID_BGMASK].exist = false;
		Fdisp.SetState(FDISP_PANEL, 0);
		musicChange(0, true);

		scr.SetIntValue(SCR_RESERVEBEGIN, 0);
		scr.SetIntValue(SCR_RESERVEBEGIN+1, 0);
	}
	retvalue = PGO;
	retvalue = scr.Execute(SCR_CONTROL, STATE_ENDING, gametime);
	//pushtimer depth
	int tpushtimer = scr.GetIntValue(SCR_RESERVEBEGIN);
	int tdepth = scr.GetIntValue(SCR_RESERVEBEGIN+1);

	if (tdepth == 0)
	{
	}
	else if (tdepth == 0xff)
	{
		SelectSystem::ClearAll();
		gametime = 0;
		state = STATE_OVER;
		return PTURN;
	}
	if(hge->Input_GetDIKey(KS_FIRE) || hge->Input_GetDIKey(KS_QUICK))
	{
		tpushtimer++;
		if(tpushtimer == 120)
		{
			tdepth = 0xff;
		}
	}
	else
	{
		tpushtimer = 0;
	}
	scr.SetIntValue(SCR_RESERVEBEGIN, tpushtimer);
	scr.SetIntValue(SCR_RESERVEBEGIN+1, tdepth);

	return retvalue;
	*/
}