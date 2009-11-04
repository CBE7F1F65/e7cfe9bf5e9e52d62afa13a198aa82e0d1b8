#include "Process.h"
#include "Scripter.h"
#include "SelectSystem.h"
#include "SE.h"

int Process::processSpell()
{
	time++;
	if(time == 1)
	{
		scr.Execute(SCR_EVENT, SCR_EVENT_ENTERSTATE, STATE_SPELL);
	}
	retvalue = PGO;
	scr.Execute(SCR_CONTROL, STATE_SPELL, time);
	return retvalue;
}