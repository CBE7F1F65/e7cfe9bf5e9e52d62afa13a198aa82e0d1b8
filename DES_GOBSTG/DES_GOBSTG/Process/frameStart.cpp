#include "Process.h"
#include "Player.h"
#include "Data.h"
#include "DataConnector.h"
#include "Replay.h"

void Process::frameStart()
{
	time++;
	if(!replaymode)
	{
		playing = true;
		Replay::rpy.WriteInput(nowInput);
	}
	else if(true/*!Player::p[0].ncCont*/)
	{
		nowInput = Replay::rpy.ReadInput();
		replayFPS = Replay::rpy.GetReplayFPS();

		if(nowInput == 0xffff)
		{
			replayend = true;
//			scene = S1;
			clearPrep();
			hge->Input_SetDIKey(KS_PAUSE);
		}
		else
		{
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
				hge->Input_SetDIKey(KS_DRAIN_(0));
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
				hge->Input_SetDIKey(KS_DRAIN_(1));
			if(nowInput & 0x0080)
				hge->Input_SetDIKey(KS_SLOW_(1));

		}
	}
	active = true;
}