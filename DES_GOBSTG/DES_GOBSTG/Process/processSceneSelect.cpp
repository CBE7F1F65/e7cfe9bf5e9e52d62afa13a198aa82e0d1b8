#include "Process.h"
#include "Scripter.h"

int Process::processSceneSelect()
{
	time++;
	if(time == 1)
	{
		scr.Execute(SCR_EVENT, SCR_EVENT_ENTERSTATE, STATE_SCENE_SELECT);
	}
	retvalue = PGO;
	scr.Execute(SCR_CONTROL, STATE_SCENE_SELECT, time);
	return retvalue;
}
