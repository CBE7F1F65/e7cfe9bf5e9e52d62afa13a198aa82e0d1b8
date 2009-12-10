#include "GameInput.h"

GameInput GameInput::gameinput[M_PL_MATCHMAXPLAYER];

GameInput::GameInput()
{
	KS_UP_(0)			= RESCONFIGDEFAULT_KEYUP_1;
	KS_DOWN_(0)			= RESCONFIGDEFAULT_KEYDOWN_1;
	KS_LEFT_(0)			= RESCONFIGDEFAULT_KEYLEFT_1;
	KS_RIGHT_(0)		= RESCONFIGDEFAULT_KEYRIGHT_1;
	KS_FIRE_(0)			= RESCONFIGDEFAULT_KEYFIRE_1;
	KS_QUICK_(0)		= RESCONFIGDEFAULT_KEYQUICK_1;
	KS_SLOW_(0)			= RESCONFIGDEFAULT_KEYSLOW_1;
	KS_DRAIN_(0)		= RESCONFIGDEFAULT_KEYDRAIN_1;
	KS_PAUSE_(0)		= RESCONFIGDEFAULT_KEYPAUSE;
	KS_SKIP_(0)			= RESCONFIGDEFAULT_KEYSKIP;
	KS_ENTER_(0)		= RESCONFIGDEFAULT_KEYENTER;
	KS_ESCAPE_(0)		= RESCONFIGDEFAULT_KEYESCAPE;
	KS_CAPTURE_(0)		= RESCONFIGDEFAULT_KEYCAPTURE;

	KS_UP_(1)			= RESCONFIGDEFAULT_KEYUP_2;
	KS_DOWN_(1)			= RESCONFIGDEFAULT_KEYDOWN_2;
	KS_LEFT_(1)			= RESCONFIGDEFAULT_KEYLEFT_2;
	KS_RIGHT_(1)		= RESCONFIGDEFAULT_KEYRIGHT_2;
	KS_FIRE_(1)			= RESCONFIGDEFAULT_KEYFIRE_2;
	KS_QUICK_(1)		= RESCONFIGDEFAULT_KEYQUICK_2;
	KS_SLOW_(1)			= RESCONFIGDEFAULT_KEYSLOW_2;
	KS_DRAIN_(1)		= RESCONFIGDEFAULT_KEYDRAIN_2;
	KS_PAUSE_(1)		= RESCONFIGDEFAULT_KEYPAUSE;
	KS_SKIP_(1)			= RESCONFIGDEFAULT_KEYSKIP;
	KS_ENTER_(1)		= RESCONFIGDEFAULT_KEYENTER;
	KS_ESCAPE_(1)		= RESCONFIGDEFAULT_KEYESCAPE;
	KS_CAPTURE_(1)		= RESCONFIGDEFAULT_KEYCAPTURE;
}

GameInput::~GameInput()
{

}

bool GameInput::InitInput(HGE * _hge)
{
	hge = _hge;

	KS_UP_(0)			= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYUP, RESCONFIGDEFAULT_KEYUP_1);
	KS_DOWN_(0)			= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYDOWN, RESCONFIGDEFAULT_KEYDOWN_1);
	KS_LEFT_(0)			= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYLEFT, RESCONFIGDEFAULT_KEYLEFT_1);
	KS_RIGHT_(0)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYRIGHT, RESCONFIGDEFAULT_KEYRIGHT_1);	
	KS_FIRE_(0)			= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYFIRE, RESCONFIGDEFAULT_KEYFIRE_1);
	KS_QUICK_(0)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYQUICK, RESCONFIGDEFAULT_KEYQUICK_1);	
	KS_SLOW_(0)			= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYSLOW, RESCONFIGDEFAULT_KEYSLOW_1);
	KS_DRAIN_(0)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYDRAIN, RESCONFIGDEFAULT_KEYDRAIN_1);	
	KS_PAUSE_(0)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYPAUSE, RESCONFIGDEFAULT_KEYPAUSE);	
	KS_SKIP_(0)			= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYSKIP, RESCONFIGDEFAULT_KEYSKIP);
	KS_ENTER_(0)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYENTER, RESCONFIGDEFAULT_KEYENTER);	
	KS_ESCAPE_(0)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYESCAPE, RESCONFIGDEFAULT_KEYESCAPE);	

	KS_UP_(1)			= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYUP, RESCONFIGDEFAULT_KEYUP_2);
	KS_DOWN_(1)			= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYDOWN, RESCONFIGDEFAULT_KEYDOWN_2);
	KS_LEFT_(1)			= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYLEFT, RESCONFIGDEFAULT_KEYLEFT_2);
	KS_RIGHT_(1)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYRIGHT, RESCONFIGDEFAULT_KEYRIGHT_2);	
	KS_FIRE_(1)			= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYFIRE, RESCONFIGDEFAULT_KEYFIRE_2);
	KS_QUICK_(1)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYQUICK, RESCONFIGDEFAULT_KEYQUICK_2);	
	KS_SLOW_(1)			= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYSLOW, RESCONFIGDEFAULT_KEYSLOW_2);
	KS_DRAIN_(1)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYDRAIN, RESCONFIGDEFAULT_KEYDRAIN_2);	
	KS_PAUSE_(1)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYPAUSE, RESCONFIGDEFAULT_KEYPAUSE);	
	KS_SKIP_(1)			= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYSKIP, RESCONFIGDEFAULT_KEYSKIP);
	KS_ENTER_(1)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYENTER, RESCONFIGDEFAULT_KEYENTER);	
	KS_ESCAPE_(1)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYESCAPE, RESCONFIGDEFAULT_KEYESCAPE);	

	JS_FIRE_(0)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_JOYFIRE, RESCONFIGDEFAULT_JOYFIRE);
	JS_QUICK_(0)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_JOYQUICK, RESCONFIGDEFAULT_JOYQUICK);
	JS_SLOW_(0)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_JOYSLOW, RESCONFIGDEFAULT_JOYSLOW);
	JS_DRAIN_(0)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_JOYDRAIN, RESCONFIGDEFAULT_JOYDRAIN);
	JS_PAUSE_(0)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_JOYPAUSE, RESCONFIGDEFAULT_JOYPAUSE);

	JS_FIRE_(1)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_JOYFIRE, RESCONFIGDEFAULT_JOYFIRE);
	JS_QUICK_(1)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_JOYQUICK, RESCONFIGDEFAULT_JOYQUICK);
	JS_SLOW_(1)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_JOYSLOW, RESCONFIGDEFAULT_JOYSLOW);
	JS_DRAIN_(1)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_JOYDRAIN, RESCONFIGDEFAULT_JOYDRAIN);
	JS_PAUSE_(1)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_JOYPAUSE, RESCONFIGDEFAULT_JOYPAUSE);

#ifdef __DEBUG
	JS_DEBUG_SPEEDUP_(0) = hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_DEBUG_JOYSPEEDUP, RESCONFIGDEFAULT_DEBUG_JOYSPEEDUP);
	JS_DEBUG_SPEEDUP_(1) = hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_DEBUG_JOYSPEEDUP, RESCONFIGDEFAULT_DEBUG_JOYSPEEDUP);
#endif
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		for (int i=0; i<13; i++)
		{
			if (keyKey[j][i] < 0 || keyKey[j][i] >= M_KEYKEYMAX)
			{
				return false;
			}
		}
		for (int i=0; i<5; i++)
		{
			if(joyKey[j][i] < 0 || joyKey[j][i] >= M_JOYKEYMAX)
			{
				return false;
			}
		}
	}
#ifdef __DEBUG
	if(JS_DEBUG_SPEEDUP_(0) < 0 || JS_DEBUG_SPEEDUP_(0) >= M_JOYKEYMAX ||
		JS_DEBUG_SPEEDUP_(1) < 0 || JS_DEBUG_SPEEDUP_(1) >= M_JOYKEYMAX)
		return false;
#endif
	return true;
}

bool GameInput::UpdateInput()
{
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		gameinput[j].lastInput = gameinput[j].input;
		gameinput[j].input = 0;
		for (int i=0; i<GAMEINPUTKEYMAX; i++)
		{
			gameinput[j].input |= (hge->Input_GetDIKey(keyKey[i])?1:0)<<i;
		}
		if (hge->Input_GetDIJoy(JOY_UP, DIKEY_PRESSED, j))
		{
			gameinput[j].input |= 1<<KSI_UP;
		}
		if (hge->Input_GetDIJoy(JOY_DOWN, DIKEY_PRESSED, j))
		{
			gameinput[j].input |= 1<<KSI_DOWN;
		}
		if (hge->Input_GetDIJoy(JOY_LEFT, DIKEY_PRESSED, j))
		{
			gameinput[j].input |= 1<<KSI_LEFT;
		}
		if (hge->Input_GetDIJoy(JOY_RIGHT, DIKEY_PRESSED, j))
		{
			gameinput[j].input |= 1<<KSI_RIGHT;
		}
		if (hge->Input_GetDIJoy(keyJS.joyFire, DIKEY_PRESSED, j))
		{
			gameinput[i].input |= 1<<KSI_FIRE;
		}
		if (hge->Input_GetDIJoy(keyJS.joyQuick, DIKEY_PRESSED, j))
		{
			gameinput[i].input |= 1<<KSI_QUICK;
		}
		if (hge->Input_GetDIJoy(keyJS.joySlow, DIKEY_PRESSED, j))
		{
			gameinput[i].input |= 1<<KSI_SLOW;
		}
		if (hge->Input_GetDIJoy(keyJS.joyDrain, DIKEY_PRESSED, j))
		{
			gameinput[i].input |= 1<<KSI_DRAIN;
		}
		if (hge->Input_GetDIJoy(keyJS.joyPause, DIKEY_PRESSED, j))
		{
			gameinput[i].input |= 1<<KSI_PAUSE;
		}
		if (hge->Input_GetDIJoy(keyJS.debug_joySpeedUp, DIKEY_PRESSED, j))
		{
			gameinput[i].input |= 1<<KSI_SKIP;
		}
	}
	return true;
}

WORD GameInput::UpdateActiveInput(bool copylast/* =false */)
{
	if (copylast)
	{
		activeInput = lastActiveInput;
	}
	else
	{
		lastActiveInput = activeInput;
		activeInput = 0;
		for (int i=0; i<GAMEACTIVEINPUTMAX; i++)
		{
			activeInput |= (input&(1<<i));
		}
	}
	return activeInput;
}

bool GameInput::GetKey(BYTE playerindex, int ksi, int type/* =DIKEY_PRESSED */, bool active/* =true */)
{
	if (playerindex != 1)
	{
		playerindex = 0;
	}
	return gameinput[playerindex].getKey(ksi, type, active);
}

void GameInput::SetKey(BYTE playerindex, int ksi, bool set/* =true */, bool active/* =true */)
{
	if (playerindex != 1)
	{
		playerindex = 0;
	}
	gameinput[playerindex].setKey(ksi, set, active);
}

bool GameInput::getKey(int ksi, int type/* =DIKEY_PRESSED */, bool active/* =true */)
{
	bool bnow;
	bool blast;
	if (active)
	{
		bnow = input & (1<<ksi);
		blast = lastInput & (1<<ksi);
	}
	else
	{
		bnow = activeInput & (1<<ksi);
		blast = lastActiveInput & (1<<ksi);
	}
	switch (type)
	{
	case DIKEY_DOWN:
		if (bnow && !blast)
		{
			return true;
		}
		break;
	case DIKEY_UP:
		if (!bnow && blast)
		{
			return true;
		}
		break;
	default:
		if (bnow)
		{
			return true;
		}
		break;
	}
	return false;
}

void GameInput::setKey(int ksi, bool set/* =true */, bool active/* =true */)
{
	if (active)
	{
		if (set)
		{
			activeInput |= 1<<ksi;
		}
		else
		{
			activeInput &= ~(1<<ksi);
		}
	}
	else
	{
		if (set)
		{
			input |= 1<<ksi;
		}
		else
		{
			input &= ~(1<<ksi);
		}
	}
}