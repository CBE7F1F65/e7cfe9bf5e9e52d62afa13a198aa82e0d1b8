#include "Process.h"
#include "Bullet.h"
#include "Player.h"
#include "Scripter.h"
#include "BGLayer.h"
#include "SelectSystem.h"
#include "Replay.h"

int Process::processContinue()
{
	if(Player::p[0].ncCont >= M_PL_CONTINUEMAX || practicemode)
		goto exit;

	if(!scr.GetIntValue(SCR_RESERVEBEGIN))
	{
		BGLayer::ubg[UBGID_FGPAUSE].exist = true;
		BGLayer::ubg[UBGID_FGPAUSE].SetFlag(FG_PAUSEIN, FGMT_PAUSE);
		scr.SetIntValue(SCR_RESERVEBEGIN+1, M_PL_CONTINUEMAX-Player::p[0].ncCont);

		hge->Channel_Pause(channel);
	}

	scr.Execute(SCR_CONTROL, STATE_CONTINUE, SCRIPT_CON_INIT);
	//60 sec
	int tsec = scr.GetIntValue(SCR_RESERVEBEGIN);
	int tselsys = scr.GetIntValue(SCR_RESERVEBEGIN+2);

	if(hge->Input_GetDIKey(KS_FIRE, DIKEY_DOWN))
	{
		BGLayer::ubg[UBGID_FGPAUSE].SetFlag(FG_PAUSEOUT, FGMT_PAUSE);
	}
	else if(hge->Input_GetDIKey(KS_QUICK, DIKEY_DOWN))
	{
		selsys[tselsys].select = 1;
	}

	if(tsec == 0x10)
	{
		BGLayer::ubg[UBGID_FGPAUSE].exist = false;
		if(!spellmode && scene < S1200)
		{
			Player::p[0].valueSet(mainchara, subchara_1, subchara_2, PL_DEFAULTNPLAYER, true);
			Player::p[0].ncCont++;

			Bullet::IzeBuild(BULLETIZE_FADEOUT, Player::p[0].x, Player::p[0].y);

			hge->Channel_Resume(channel);
			hge->Channel_SetVolume(channel, 0);
			musicSlide(1.5f, -1);
			state = STATE_START;
			return PTURN;
		}
		else
		{
			scene = startscene;
			startPrep();
			if(spellmode)
			{
				hge->Channel_Resume(channel);
				hge->Channel_SetVolume(channel, 0);
				musicSlide(1.5f, -1);
			}
			state = STATE_START;
			return PTURN;
		}
	}
	else if(tsec == 0x11)
	{
exit:
		rpy.partFill(0xff);
		BGLayer::ubg[UBGID_FGPAUSE].exist = false;
//		musicChange(0);
		time = 0;
		state = STATE_OVER;
		return PTURN;
	}

	scr.SetIntValue(SCR_RESERVEBEGIN, tsec);

	return PGO;
}