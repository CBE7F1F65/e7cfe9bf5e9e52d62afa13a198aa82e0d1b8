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

	if(selsys[scr.GetIntValue(SCR_RESERVEBEGIN+1)].sel.size() && hge->Input_GetDIKey(KS_QUICK, DIKEY_UP))
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
			hge->Input_SetDIKey(KS_LEFT_(0), (bool)(saveInput & 0x0100));
			hge->Input_SetDIKey(KS_RIGHT_(0), (bool)(saveInput & 0x0200));
			hge->Input_SetDIKey(KS_UP_(0), (bool)(saveInput & 0x0400));
			hge->Input_SetDIKey(KS_DOWN_(0), (bool)(saveInput & 0x0800));
			hge->Input_SetDIKey(KS_FIRE_(0), (bool)(saveInput & 0x1000));
			hge->Input_SetDIKey(KS_QUICK_(0), (bool)(saveInput & 0x2000));
			hge->Input_SetDIKey(KS_CHARGE_(0), (bool)(saveInput & 0x4000));
			hge->Input_SetDIKey(KS_SLOW_(0), (bool)(saveInput & 0x8000));

			hge->Input_SetDIKey(KS_LEFT_(1), (bool)(saveInput & 0x0001));
			hge->Input_SetDIKey(KS_RIGHT_(1), (bool)(saveInput & 0x0002));
			hge->Input_SetDIKey(KS_UP_(1), (bool)(saveInput & 0x0004));
			hge->Input_SetDIKey(KS_DOWN_(1), (bool)(saveInput & 0x0008));
			hge->Input_SetDIKey(KS_FIRE_(1), (bool)(saveInput & 0x0010));
			hge->Input_SetDIKey(KS_QUICK_(1), (bool)(saveInput & 0x0020));
			hge->Input_SetDIKey(KS_CHARGE_(1), (bool)(saveInput & 0x0040));
			hge->Input_SetDIKey(KS_SLOW_(1), (bool)(saveInput & 0x0080));

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
