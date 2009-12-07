#include "Process.h"
#include "Scripter.h"

int Process::processPlayerSelect()
{
	time++;
	if(time == 1)
	{
		Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_ENTERSTATE, STATE_PLAYER_SELECT);
	}
	retvalue = PGO;
	Scripter::scr.Execute(SCR_CONTROL, STATE_PLAYER_SELECT, time);
	return retvalue;
}
