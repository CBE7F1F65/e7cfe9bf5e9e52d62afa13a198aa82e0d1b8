#include "Process.h"
#include "Scripter.h"
#include "SelectSystem.h"
#include "SE.h"

int Process::processTitle()
{
	time++;
	if(time == 1)
	{
		reload();
		for (int i=0; i<SELSYSTEMMAX; i++)
		{
			SelectSystem::selsys[i].select = titleselect;
		}
	}
	retvalue = PGO;
	Scripter::scr.Execute(SCR_CONTROL, STATE_TITLE, time);
	int tselsys = Scripter::scr.GetIntValue(SCR_RESERVEBEGIN);
	titleselect = SelectSystem::selsys[tselsys].select;
	return retvalue;
}