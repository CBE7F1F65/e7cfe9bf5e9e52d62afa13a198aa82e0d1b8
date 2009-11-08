#include "Process.h"

int Process::getInput()
{
	if(!(replaymode && !replayend && (state == STATE_START || state == STATE_CLEAR)))
	{
		if(	hge->Input_GetDIJoy(JOY_LEFT))
			hge->Input_SetDIKey(KS_LEFT);
		if(	hge->Input_GetDIJoy(JOY_RIGHT))
			hge->Input_SetDIKey(KS_RIGHT);
		if(	hge->Input_GetDIJoy(JOY_UP))
			hge->Input_SetDIKey(KS_UP);
		if(	hge->Input_GetDIJoy(JOY_DOWN))
			hge->Input_SetDIKey(KS_DOWN);

		if(	hge->Input_GetDIJoy(JS_FIRE))
			hge->Input_SetDIKey(KS_FIRE);
		if(	hge->Input_GetDIJoy(JS_QUICK))
			hge->Input_SetDIKey(KS_QUICK);
		if(	hge->Input_GetDIJoy(JS_SLOW))
			hge->Input_SetDIKey(KS_SLOW);
		if(	hge->Input_GetDIJoy(JS_CHARGE))
			hge->Input_SetDIKey(KS_CHARGE);
	}
	else
	{
		hge->Input_SetDIKey(KS_LEFT, false);
		hge->Input_SetDIKey(KS_RIGHT, false);
		hge->Input_SetDIKey(KS_UP, false);
		hge->Input_SetDIKey(KS_DOWN, false);
		hge->Input_SetDIKey(KS_FIRE, false);
		hge->Input_SetDIKey(KS_QUICK, false);
		hge->Input_SetDIKey(KS_CHARGE, false);
		hge->Input_SetDIKey(KS_SLOW, false);
	}

	if(	hge->Input_GetDIJoy(JS_PAUSE))
		hge->Input_SetDIKey(KS_PAUSE);

	nowInput = 0;
	if(hge->Input_GetDIKey(KS_LEFT))
		nowInput |= 0x1;
	if(hge->Input_GetDIKey(KS_RIGHT))
		nowInput |= 0x2;
	if(hge->Input_GetDIKey(KS_UP))
		nowInput |= 0x4;
	if(hge->Input_GetDIKey(KS_DOWN))
		nowInput |= 0x8;
	if(hge->Input_GetDIKey(KS_FIRE))
		nowInput |= 0x10;
	if(hge->Input_GetDIKey(KS_QUICK))
		nowInput |= 0x20;
	if(hge->Input_GetDIKey(KS_CHARGE))
		nowInput |= 0x40;
	if(hge->Input_GetDIKey(KS_SLOW))
		nowInput |= 0x80;

	return PGO;
}