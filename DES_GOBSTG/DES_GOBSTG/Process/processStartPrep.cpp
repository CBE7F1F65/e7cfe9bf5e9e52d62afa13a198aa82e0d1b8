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
	worldx = 0;
	worldy = 0;
	worldz = 0;
	frameskip = M_DEFAULT_FRAMESKIP;
	Scripter::stopEdefScript = false;
	FrontDisplay::fdisp.SetState(FDISP_PANEL, 1);

	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
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
	replayIndex = 0;

	SetCurrentDirectory(hge->Resource_MakePath(""));

	if(replaymode)
	{
		rpy.Load(rpyfilename, true);
		BYTE part = 0;
		seed = rpy.partinfo[part].seed;
		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
		{
			Player::p[i].SetChara(rpy.rpyinfo.usingchara[i][0], rpy.rpyinfo.usingchara[i][1], rpy.rpyinfo.usingchara[i][2]);
			Player::p[i].SetInitLife(rpy.rpyinfo.initlife[i]);
		}
		scene = rpy.rpyinfo.scene;

		replayIndex = rpy.partinfo[part].offset - 1;
	}
	else
	{
		seed = timeGetTime();
	}
	clearPrep();

	srandt(seed);

	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		Player::p[i].ClearNC();
//		Player::p[i].nHiScore = DataConnector::nHiScore();
	}

	//set

	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		Player::p[i].valueSet(i);
	}
	Player::ClearRound();
//	DataConnector::Try(true);

	if(!replaymode)
	{
		ZeroMemory(&rpy.rpyinfo, sizeof(replayInfo));

		//partinfo
		BYTE part = 0;
//		if(scene < S1200)
//			part = scene / M_STAGENSCENE - 1;
		for(int i=0;i<RPYPARTMAX;i++)
		{
			if(i != part)
			{
				ZeroMemory(&rpy.partinfo[i], sizeof(partInfo));
			}
			else
			{
				rpy.partFill(part);
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
				Player::p[i].changePlayerID(rpy.partinfo[part].nowID[i]);
			}
		}
	}

	BGLayer::ubg[UBGID_BGMASK].valueSetByName(SI_WHITE, M_CLIENT_CENTER_X, M_CLIENT_CENTER_Y, M_CLIENT_WIDTH, M_CLIENT_HEIGHT, 0);
	BGLayer::ubg[UBGID_FGPAUSE].valueSetByName(SI_WHITE, M_CLIENT_CENTER_X, M_CLIENT_CENTER_Y, M_CLIENT_WIDTH, M_CLIENT_HEIGHT, 0);
	BGLayer::ubg[UBGID_FGPAUSE].exist = false;

	stopflag = 0;
	stoptimer = 0;

	framecounter = 0;
	time = 0;
	alltime = 0;

	if (callinit)
	{
		scr.Execute(SCR_STAGE, SCRIPT_CON_POST, scene);
	}
}