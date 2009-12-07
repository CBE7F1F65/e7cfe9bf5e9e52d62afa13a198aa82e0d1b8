#include "Process.h"
#include "Scripter.h"
#include "Chat.h"
#include "DataConnector.h"
#include "BossInfo.h"

int Process::frame()
{
	if(hge->Input_GetKeyState(HGEK_ALT) && hge->Input_GetKeyState(HGEK_ENTER)) 
	{
		screenmode = 1 - screenmode;
		hge->System_SetState(HGE_WINDOWED, !(bool)screenmode);
		hge->System_SetState(HGE_HIDEMOUSE, (bool)screenmode);
		if(!screenmode)
		{
			Export::clientAdjustWindow();
		}
		return PSKIP;
	}
#ifdef __DEBUG
	if(hge->Input_GetKeyState(HGEK_BACKSPACE))
	{
		Scripter::scr.LoadAll(tex);
		state = STATE_TITLE;
		time = 0;
		return PTURN;
	}
#endif
	if(
		hge->Input_GetDIKey(KS_SKIP)
#ifdef __DEBUG
		|| hge->Input_GetKeyState(HGEK_CTRL)
		|| hge->Input_GetDIJoy(JS_DEBUG_SPEEDUP)
#endif
		)
	{
		if (!replaymode)
		{
			if (Chat::chatitem.IsChatting())
			{
				hge->Input_SetDIKey(KS_FIRE, (bool)(time%5 == 0));
			}
		}
#ifndef __DEBUG
		else
#endif
			frameskip = M_FRAMESKIP_FASTSKIP;
	}
	else if(frameskip < M_DEFAULT_FRAMESKIP)
	{
		frameskip = M_DEFAULT_FRAMESKIP;
	}
	else if (BossInfo::allover)
	{
		frameskip = M_FRAMESKIP_SLOWSKIP;
	}
	hge->System_SetState(HGE_FRAMESKIP, frameskip);

	getInput();
	lasttime = time;

	playing = false;

	int rv = 0xffffffff;
	switch(state)
	{
		
	case STATE_START:
		rv = processStart();
		break;
	case STATE_PAUSE:
		rv = processPause();
		break;
	case STATE_CONTINUE:
		rv = processContinue();
		break;
	case STATE_CLEAR:
		rv = processClear();
		break;
	case STATE_ENDING:
		rv = processEnding();
		break;
	case STATE_TITLE:
		rv = processTitle();
		break;
	case STATE_MATCH_SELECT:
		rv = processMatchSelect();
		break;
	case STATE_PLAYER_SELECT:
		rv = processPlayerSelect();
		break;
	case STATE_SCENE_SELECT:
		rv = processSceneSelect();
		break;
	case STATE_OVER:
		rv = processOver();
		break;
	case STATE_SPELL:
		rv = processSpell();
		break;
	case STATE_REPLAY:
		rv = processReplay();
		break;
	case STATE_RESULT:
		rv = processResult();
		break;
	case STATE_OPTION:
		rv = processOption();
		break;
	case STATE_MUSIC:
		rv = processMusic();
		break;
	case STATE_INIT:
		rv = processInit();
		break;
	}

	if(playing && !playtimeStart)
	{
		SYSTEMTIME tsystime;
		FILETIME tfiletime;
		GetLocalTime(&tsystime);
		SystemTimeToFileTime(&tsystime, &tfiletime);

		playtimeStart = (((LONGLONG)tfiletime.dwHighDateTime) << 32) | tfiletime.dwLowDateTime;
	}
	else if(!playing && playtimeStart)
	{
		DataConnector::addPlayTime();
	}
	
	if(rv == 0xffffffff)
	{
		time = 0;
		state = STATE_TITLE;
		rv = PTURN;
	}

	if (rv == PTURN)
	{
		return PTURN;
	}

	if(rv == PQUIT)
		return PQUIT;

	frameEnd();
	for (int i=0; i<FRAME_STOPINFOMAX; i++)
	{
		if (stopflag[i])
		{
			stoptimer[i]--;
			if (stoptimer[i] == 0)
			{
				stopflag[i] = 0;
			}
		}
	}

	return PGO;
}