#include "Process.h"
#include "Scripter.h"

int Process::processSceneSelect()
{
	time++;
	if(time == 1)
	{
		Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_ENTERSTATE, STATE_SCENE_SELECT);
	}
	retvalue = PGO;
	Scripter::scr.Execute(SCR_CONTROL, STATE_SCENE_SELECT, time);
	return retvalue;
}
