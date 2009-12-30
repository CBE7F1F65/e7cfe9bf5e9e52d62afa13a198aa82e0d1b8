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
		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
		{
//			Player::SetAble(false);
			Player::p[i].exist = false;
		}
	}
	processStart();
	Scripter::scr.Execute(SCR_CONTROL, STATE_CLEAR, gametime-alltime);

	return PGO;
}