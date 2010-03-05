#include "../Header/processPrep.h"

void Process::clearPrep(bool bclearkey)
{
	gametime = 0;
	lasttime = 0;

	ClearAll();

	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		BGLayer::ubg[i][UBGID_BGMASK].valueSetByName(SI_WHITE, M_CLIENT_CENTER_X, M_CLIENT_CENTER_Y, M_CLIENT_WIDTH, M_CLIENT_HEIGHT, 0);
		BGLayer::ubg[i][UFGID_FGPAUSE].valueSetByName(SI_WHITE, M_CLIENT_CENTER_X, M_CLIENT_CENTER_Y, M_CLIENT_WIDTH, M_CLIENT_HEIGHT, 0);
	}
	
	FrontDisplay::fdisp.SetState(FDISP_PANEL, FDISPSTATE_ON);
	for (int i=0; i<M_PL_ONESETPLAYER; i++)
	{
		FrontDisplay::fdisp.SetState(FDISP_SPELLNAME_0+i, FDISPSTATE_OFF);
	}

	if(!bclearkey)
		return;

	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		hge->Input_SetDIKey(GameInput::KS_UP_(i), false);
		hge->Input_SetDIKey(GameInput::KS_DOWN_(i), false);
		hge->Input_SetDIKey(GameInput::KS_LEFT_(i), false);
		hge->Input_SetDIKey(GameInput::KS_RIGHT_(i), false);
		hge->Input_SetDIKey(GameInput::KS_FIRE_(i), false);
		hge->Input_SetDIKey(GameInput::KS_QUICK_(i), false);
		hge->Input_SetDIKey(GameInput::KS_DRAIN_(i), false);
		hge->Input_SetDIKey(GameInput::KS_SLOW_(i), false);

		GameInput::SetKey(i, KSI_UP, false);
		GameInput::SetKey(i, KSI_DOWN, false);
		GameInput::SetKey(i, KSI_LEFT, false);
		GameInput::SetKey(i, KSI_RIGHT, false);
		GameInput::SetKey(i, KSI_FIRE, false);
		GameInput::SetKey(i, KSI_QUICK, false);
		GameInput::SetKey(i, KSI_SLOW, false);
		GameInput::SetKey(i, KSI_DRAIN, false);
	}

	alltime = 0;
}

void Process::startPrep(bool callinit)
{
	replayend = false;
	SetState(STATE_START);

	SetCurrentDirectory(hge->Resource_MakePath(""));

	BYTE part = 0;
	if (replaymode)
	{
		Replay::rpy.Load(rpyfilename, true);
		seed = Replay::rpy.partinfo[part].seed;
		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
		{
			Player::p[i].SetChara(Replay::rpy.rpyinfo.usingchara[i][0], Replay::rpy.rpyinfo.usingchara[i][1], Replay::rpy.rpyinfo.usingchara[i][2]);
			Player::p[i].SetInitLife(Replay::rpy.rpyinfo.initlife[i]);
		}
		SetScene(Replay::rpy.rpyinfo.scene);
		SetMatchMode(Replay::rpy.rpyinfo.matchmode);
	}
	else
	{
		seed = timeGetTime();
	}
	srandt(seed);
	hge->Random_Seed(seed);

	Replay::rpy.InitReplayIndex(replaymode, part);

	clearPrep();
	if (matchmode == M_MATCHMODE_P2C)
	{
		GameAI::ai[1].SetAble(true);
#ifdef __DEBUG
		GameAI::ai[0].SetAble(true);
#endif
	}
	else
	{
		GameAI::ai[1].SetAble(false);
	}
	if (matchmode == M_MATCHMODE_C2P)
	{
		GameAI::ai[0].SetAble(true);
	}
#ifndef __DEBUG
	else
	{
		GameAI::ai[0].SetAble(false);
	}
#endif
	SetInputSwap();

	//set
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		Player::p[i].valueSet(i);
	}
	Player::ClearRound();
	FrontDisplay::fdisp.SignUpSpell();
	musicChange(BResource::res.playerdata[scene].musicID);

	if(!replaymode)
	{
		ZeroMemory(&Replay::rpy.rpyinfo, sizeof(replayInfo));

		//partinfo
		BYTE part = 0;
//		if(scene < S1200)
//			part = scene / M_STAGENSCENE - 1;
		for(int i=0;i<RPYPARTMAX;i++)
		{
			if(i != part)
			{
				ZeroMemory(&Replay::rpy.partinfo[i], sizeof(partInfo));
			}
			else
			{
				Replay::rpy.partFill(part);
			}
		}
	}
	else
	{
		BYTE part = 0;
//		if(scene < S1200)
//			part = data.getStage(scene) - 1;
		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
		{
			if (part)
			{
				Player::p[i].changePlayerID(Replay::rpy.partinfo[part].nowID[i]);
			}
		}
	}

	for (int i=0; i<FRAME_STOPINFOMAX; i++)
	{
		SetStop(0, 0);
	}

	framecounter = 0;
	gametime = 0;

	if (callinit)
	{
		Scripter::scr.Execute(SCR_STAGE, SCRIPT_CON_POST, scene);
	}
}