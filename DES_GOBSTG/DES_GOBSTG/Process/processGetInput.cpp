#include "Process.h"

void Process::SyncInput()
{
	if (hge)
	{
		if (hge->Input_GetDIKey(KS_SKIP_(0)) || hge->Input_GetDIKey(KS_SKIP_(1)))
		{
			hge->Input_SetDIKey(KS_SKIP_(0));
			hge->Input_SetDIKey(KS_SKIP_(1));
		}
		if (hge->Input_GetDIKey(KS_ENTER_(0)) || hge->Input_GetDIKey(KS_ENTER_(1)))
		{
			hge->Input_SetDIKey(KS_ENTER_(0));
			hge->Input_SetDIKey(KS_ENTER_(1));
		}
		if (hge->Input_GetDIKey(KS_ESCAPE_(0)) || hge->Input_GetDIKey(KS_ESCAPE_(1)))
		{
			hge->Input_SetDIKey(KS_ESCAPE_(0));
			hge->Input_SetDIKey(KS_ESCAPE_(1));
		}
		if (hge->Input_GetDIKey(KS_CAPTURE_(0)) || hge->Input_GetDIKey(KS_CAPTURE_(1)))
		{
			hge->Input_SetDIKey(KS_CAPTURE_(0));
			hge->Input_SetDIKey(KS_CAPTURE_(1));
		}
	}
}

int Process::getInput()
{
	if(!(replaymode && !replayend && (state == STATE_START || state == STATE_CLEAR)))
	{
		if(	hge->Input_GetDIJoy(JOY_LEFT, DIKEY_PRESSED, 0))
			hge->Input_SetDIKey(KS_LEFT_(0));
		if(	hge->Input_GetDIJoy(JOY_RIGHT, DIKEY_PRESSED, 0))
			hge->Input_SetDIKey(KS_RIGHT_(0));
		if(	hge->Input_GetDIJoy(JOY_UP, DIKEY_PRESSED, 0))
			hge->Input_SetDIKey(KS_UP_(0));
		if(	hge->Input_GetDIJoy(JOY_DOWN, DIKEY_PRESSED, 0))
			hge->Input_SetDIKey(KS_DOWN_(0));
		if(	hge->Input_GetDIJoy(JS_FIRE_(0), DIKEY_PRESSED, 0))
			hge->Input_SetDIKey(KS_FIRE_(0));
		if(	hge->Input_GetDIJoy(JS_QUICK_(0), DIKEY_PRESSED, 0))
			hge->Input_SetDIKey(KS_QUICK_(0));
		if(	hge->Input_GetDIJoy(JS_SLOW_(0), DIKEY_PRESSED, 0))
			hge->Input_SetDIKey(KS_SLOW_(0));
		if(	hge->Input_GetDIJoy(JS_CHARGE_(0), DIKEY_PRESSED, 0))
			hge->Input_SetDIKey(KS_CHARGE_(0));

		if(	hge->Input_GetDIJoy(JOY_LEFT, DIKEY_PRESSED, 1))
			hge->Input_SetDIKey(KS_LEFT_(1));
		if(	hge->Input_GetDIJoy(JOY_RIGHT, DIKEY_PRESSED, 1))
			hge->Input_SetDIKey(KS_RIGHT_(1));
		if(	hge->Input_GetDIJoy(JOY_UP, DIKEY_PRESSED, 1))
			hge->Input_SetDIKey(KS_UP_(1));
		if(	hge->Input_GetDIJoy(JOY_DOWN, DIKEY_PRESSED, 1))
			hge->Input_SetDIKey(KS_DOWN_(1));
		if(	hge->Input_GetDIJoy(JS_FIRE_(1), DIKEY_PRESSED, 1))
			hge->Input_SetDIKey(KS_FIRE_(1));
		if(	hge->Input_GetDIJoy(JS_QUICK_(1), DIKEY_PRESSED, 1))
			hge->Input_SetDIKey(KS_QUICK_(1));
		if(	hge->Input_GetDIJoy(JS_SLOW_(1), DIKEY_PRESSED, 1))
			hge->Input_SetDIKey(KS_SLOW_(1));
		if(	hge->Input_GetDIJoy(JS_CHARGE_(1), DIKEY_PRESSED, 1))
			hge->Input_SetDIKey(KS_CHARGE_(1));
	}
	else
	{
		hge->Input_SetDIKey(KS_LEFT_(0), false);
		hge->Input_SetDIKey(KS_RIGHT_(0), false);
		hge->Input_SetDIKey(KS_UP_(0), false);
		hge->Input_SetDIKey(KS_DOWN_(0), false);
		hge->Input_SetDIKey(KS_FIRE_(0), false);
		hge->Input_SetDIKey(KS_QUICK_(0), false);
		hge->Input_SetDIKey(KS_CHARGE_(0), false);
		hge->Input_SetDIKey(KS_SLOW_(0), false);

		hge->Input_SetDIKey(KS_LEFT_(1), false);
		hge->Input_SetDIKey(KS_RIGHT_(1), false);
		hge->Input_SetDIKey(KS_UP_(1), false);
		hge->Input_SetDIKey(KS_DOWN_(1), false);
		hge->Input_SetDIKey(KS_FIRE_(1), false);
		hge->Input_SetDIKey(KS_QUICK_(1), false);
		hge->Input_SetDIKey(KS_CHARGE_(1), false);
		hge->Input_SetDIKey(KS_SLOW_(1), false);
	}

	if(	hge->Input_GetDIJoy(JS_PAUSE_(0), DIKEY_PRESSED, 0))
		hge->Input_SetDIKey(KS_PAUSE_(0));
	if(	hge->Input_GetDIJoy(JS_PAUSE_(1), DIKEY_PRESSED, 1))
		hge->Input_SetDIKey(KS_PAUSE_(1));

	if (hge->Input_GetDIKey(KS_PAUSE_(0)) || hge->Input_GetDIKey(KS_PAUSE_(1)))
	{
		hge->Input_SetDIKey(KS_PAUSE_(0));
		hge->Input_SetDIKey(KS_PAUSE_(1));
	}

	nowInput = 0;

	if(hge->Input_GetDIKey(KS_LEFT_(0)))
		nowInput |= 0x0100;
	if(hge->Input_GetDIKey(KS_RIGHT_(0)))
		nowInput |= 0x0200;
	if(hge->Input_GetDIKey(KS_UP_(0)))
		nowInput |= 0x0400;
	if(hge->Input_GetDIKey(KS_DOWN_(0)))
		nowInput |= 0x0800;
	if(hge->Input_GetDIKey(KS_FIRE_(0)))
		nowInput |= 0x1000;
	if(hge->Input_GetDIKey(KS_QUICK_(0)))
		nowInput |= 0x2000;
	if(hge->Input_GetDIKey(KS_CHARGE_(0)))
		nowInput |= 0x4000;
	if(hge->Input_GetDIKey(KS_SLOW_(0)))
		nowInput |= 0x8000;

	if(hge->Input_GetDIKey(KS_LEFT_(1)))
		nowInput |= 0x0001;
	if(hge->Input_GetDIKey(KS_RIGHT_(1)))
		nowInput |= 0x0002;
	if(hge->Input_GetDIKey(KS_UP_(1)))
		nowInput |= 0x0004;
	if(hge->Input_GetDIKey(KS_DOWN_(1)))
		nowInput |= 0x0008;
	if(hge->Input_GetDIKey(KS_FIRE_(1)))
		nowInput |= 0x0010;
	if(hge->Input_GetDIKey(KS_QUICK_(1)))
		nowInput |= 0x0020;
	if(hge->Input_GetDIKey(KS_CHARGE_(1)))
		nowInput |= 0x0040;
	if(hge->Input_GetDIKey(KS_SLOW_(1)))
		nowInput |= 0x0080;

	if (state != STATE_START && state != STATE_PLAYER_SELECT)
	{
		WORD _nowInput = ((nowInput & 0xff) << 8) | (nowInput >> 8);
		nowInput |= _nowInput;

		if(nowInput & 0x0100)
			hge->Input_SetDIKey(KS_LEFT_(0));
		if(nowInput & 0x0200)
			hge->Input_SetDIKey(KS_RIGHT_(0));
		if(nowInput & 0x0400)
			hge->Input_SetDIKey(KS_UP_(0));
		if(nowInput & 0x0800)
			hge->Input_SetDIKey(KS_DOWN_(0));
		if(nowInput & 0x1000)
			hge->Input_SetDIKey(KS_FIRE_(0));
		if(nowInput & 0x2000)
			hge->Input_SetDIKey(KS_QUICK_(0));
		if(nowInput & 0x4000)
			hge->Input_SetDIKey(KS_CHARGE_(0));
		if(nowInput & 0x8000)
			hge->Input_SetDIKey(KS_SLOW_(0));

		if(nowInput & 0x0001)
			hge->Input_SetDIKey(KS_LEFT_(1));
		if(nowInput & 0x0002)
			hge->Input_SetDIKey(KS_RIGHT_(1));
		if(nowInput & 0x0004)
			hge->Input_SetDIKey(KS_UP_(1));
		if(nowInput & 0x0008)
			hge->Input_SetDIKey(KS_DOWN_(1));
		if(nowInput & 0x0010)
			hge->Input_SetDIKey(KS_FIRE_(1));
		if(nowInput & 0x0020)
			hge->Input_SetDIKey(KS_QUICK_(1));
		if(nowInput & 0x0040)
			hge->Input_SetDIKey(KS_CHARGE_(1));
		if(nowInput & 0x0080)
			hge->Input_SetDIKey(KS_SLOW_(1));
	}

	return PGO;
}