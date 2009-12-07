#include "processPrep.h"

void Process::clearPrep(bool bclearkey)
{
	SelectSystem::ClearAll();
	Effectsys::ClearAll();
	BGLayer::Init(tex);
	Enemy::ClearAll();
//	Ghost::ClearAll();
	Target::ClearAll();
	Bullet::ClearItem();
	Item::ClearItem();
	PlayerBullet::ClearItem();
	Beam::ClearItem();
	Chat::chatitem.Clear();
	BossInfo::Clear();
	EffectSp::ClearItem();
	EventZone::Clear();

	pauseinit = false;
	frameskip = M_DEFAULT_FRAMESKIP;
	FrontDisplay::fdisp.SetState(FDISP_PANEL, 1);

	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		SetShake(i, 0, true);
		Player::p[i].ClearSet();
	}

	if(!bclearkey)
		return;

	hge->Input_SetDIKey(KS_UP_(0), false);
	hge->Input_SetDIKey(KS_DOWN_(0), false);
	hge->Input_SetDIKey(KS_LEFT_(0), false);
	hge->Input_SetDIKey(KS_RIGHT_(0), false);
	hge->Input_SetDIKey(KS_FIRE_(0), false);
	hge->Input_SetDIKey(KS_QUICK_(0), false);
	hge->Input_SetDIKey(KS_DRAIN_(0), false);
	hge->Input_SetDIKey(KS_SLOW_(0), false);

	hge->Input_SetDIKey(KS_UP_(1), false);
	hge->Input_SetDIKey(KS_DOWN_(1), false);
	hge->Input_SetDIKey(KS_LEFT_(1), false);
	hge->Input_SetDIKey(KS_RIGHT_(1), false);
	hge->Input_SetDIKey(KS_FIRE_(1), false);
	hge->Input_SetDIKey(KS_QUICK_(1), false);
	hge->Input_SetDIKey(KS_DRAIN_(1), false);
	hge->Input_SetDIKey(KS_SLOW_(1), false);
}

void Process::startPrep(bool callinit)
{
	replayend = false;

	SetCurrentDirectory(hge->Resource_MakePath(""));

	BYTE part = 0;
	if(replaymode)
	{
		Replay::rpy.Load(rpyfilename, true);
		seed = Replay::rpy.partinfo[part].seed;
		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
		{
			Player::p[i].SetChara(Replay::rpy.rpyinfo.usingchara[i][0], Replay::rpy.rpyinfo.usingchara[i][1], Replay::rpy.rpyinfo.usingchara[i][2]);
			Player::p[i].SetInitLife(Replay::rpy.rpyinfo.initlife[i]);
		}
		scene = Replay::rpy.rpyinfo.scene;
	}
	else
	{
		seed = timeGetTime();
	}

	Replay::rpy.InitReplayIndex(replaymode, part);

	clearPrep();

	srandt(seed);

	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		Player::p[i].ClearNC();
	}

	//set

	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		Player::p[i].valueSet(i);
	}
	Player::ClearRound();

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

	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		BGLayer::ubg[i][UBGID_BGMASK].valueSetByName(SI_WHITE, M_CLIENT_CENTER_X, M_CLIENT_CENTER_Y, M_CLIENT_WIDTH, M_CLIENT_HEIGHT, 0);
		BGLayer::ubg[i][UBGID_FGPAUSE].valueSetByName(SI_WHITE, M_CLIENT_CENTER_X, M_CLIENT_CENTER_Y, M_CLIENT_WIDTH, M_CLIENT_HEIGHT, 0);
		BGLayer::ubg[i][UBGID_FGPAUSE].exist = false;
	}

	framecounter = 0;
	time = 0;

	if (callinit)
	{
		Scripter::scr.Execute(SCR_STAGE, SCRIPT_CON_POST, scene);
	}
}