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
			selsys[i].select = titleselect;
		}
	}
	retvalue = PGO;
	scr.Execute(SCR_CONTROL, STATE_TITLE, time);
	int tselsys = scr.GetIntValue(SCR_RESERVEBEGIN);
	titleselect = selsys[tselsys].select;
	return retvalue;
}