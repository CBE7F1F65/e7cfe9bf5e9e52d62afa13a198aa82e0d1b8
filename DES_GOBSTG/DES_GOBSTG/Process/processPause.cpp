#include "Process.h"
#include "Scripter.h"
#include "SelectSystem.h"
#include "Player.h"
#include "InfoSelect.h"
#include "SE.h"
#include "BGLayer.h"
#include "BossInfo.h"
#include "FrontDisplay.h"

int Process::processPause()
{
	BYTE tstate = state;
	if(!pauseinit)
	{
		hge->Channel_Pause(channel);

		scr.d[SCR_RESERVEBEGIN].bfloat = false;
		scr.SetIntValue(SCR_RESERVEBEGIN, 0x00);
		pauseinit = true;

		if(replaymode)
		{
			if (replayend)
			{
				time = 0;
			}
		}
		else if (Player::p.exist && Player::p.ncPause < 0xff)
		{
			Player::p.ncPause++;
		}
	}
	if(scr.GetIntValue(SCR_RESERVEBEGIN) < 0x100)
		scr.Execute(SCR_CONTROL, STATE_PAUSE, SCRIPT_CON_INIT);

	if(selsys[scr.GetIntValue(SCR_RESERVEBEGIN+1)].sel.size() && hge->Input_GetDIKey(KS_SPECIAL, DIKEY_UP))
	{
		SelectSystem::ClearAll();
		if(scr.GetIntValue(SCR_RESERVEBEGIN) == 0x10)
		{
			scr.SetIntValue(SCR_RESERVEBEGIN, 0xff);
			if(replaymode && replayend || spellmode && !replaymode && time == 0)
				state = STATE_TITLE;
			else
				state = STATE_START;
		}
		else
			scr.SetIntValue(SCR_RESERVEBEGIN, 0x01);
		SE::push(SE_SYSTEM_CANCEL);
//		state = STATE_START;
	}
	if(hge->Input_GetDIKey(KS_PAUSE, DIKEY_DOWN))
	{
		SelectSystem::ClearAll();
		scr.SetIntValue(SCR_RESERVEBEGIN, 0xff);
		SE::push(SE_SYSTEM_CANCEL);
		if(replaymode && replayend)
			state = STATE_TITLE;
		else
			state = STATE_START;
	}

	if(scr.GetIntValue(SCR_RESERVEBEGIN) == 0xff)
	{
		fgpause.SetFlag(FG_PAUSEOUT, FGMT_PAUSE);
		scr.SetIntValue(SCR_RESERVEBEGIN, 0x100|state);
		state = STATE_PAUSE;
	}
	else if(scr.GetIntValue(SCR_RESERVEBEGIN) >= 0x100 && !fgpause.flag)
	{
		fgpause.exist = false;
		pauseinit = false;
		state = scr.GetIntValue(SCR_RESERVEBEGIN) & 0xff;
		if(state == STATE_START)
		{
			if(time == 0)
			{
				scene = startscene;
				startPrep();
				return PTURN;
			}
			hge->Input_SetDIKey(KS_LEFT, (bool)(saveInput & 0x1));
			hge->Input_SetDIKey(KS_RIGHT, (bool)(saveInput & 0x2));
			hge->Input_SetDIKey(KS_UP, (bool)(saveInput & 0x4));
			hge->Input_SetDIKey(KS_DOWN, (bool)(saveInput & 0x8));
			hge->Input_SetDIKey(KS_FIRE, (bool)(saveInput & 0x10));
			hge->Input_SetDIKey(KS_SPECIAL, (bool)(saveInput & 0x20));
			hge->Input_SetDIKey(KS_CHANGE, (bool)(saveInput & 0x40));
			hge->Input_SetDIKey(KS_SLOW, (bool)(saveInput & 0x80));

			if (musicID >= 0)
			{
				hge->Channel_SetVolume(channel, 0);
				hge->Channel_Resume(channel);
				musicSlide(1.5f, -1);
			}

			return PTURN;
		}
		else if(state == STATE_TITLE)
		{
			time = 0;
			if(replaymode)
			{
				BGLayer::KillOtherLayer();
				SelectSystem::ClearAll();
				InfoSelect::Clear();
				bgmask.exist = false;
				fdisp.SetState(FDISP_PANEL, 0);
				Player::p.exist = false;
				BossInfo::Clear();
				getInput();
				replaymode = false;
				state = STATE_REPLAY;
				return PTURN;
			}
			if(practicemode || spellmode)
			{
				BGLayer::KillOtherLayer();
				SelectSystem::ClearAll();
				InfoSelect::Clear();
				bgmask.exist = false;
				fdisp.SetState(FDISP_PANEL, 0);
				BossInfo::Clear();
				if(spellmode && !replaymode && time == 0)
					state = STATE_CONTINUE;
				else
					state = STATE_DIFFICULT_SELECT;
			}
			scene = startscene;
			Player::p.exist = false;
//			startPrep();
			return PTURN;
		}
	}
	return PGO;
}
