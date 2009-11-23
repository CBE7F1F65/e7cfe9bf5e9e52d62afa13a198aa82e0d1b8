#include "processPrep.h"

void Process::clearPrep(bool bclearkey)
{
	SelectSystem::ClearAll();
	Effectsys::ClearAll();
	BGLayer::Init(tex);
	Enemy::ClearAll();
	Ghost::ClearAll();
	Target::ClearAll();
	Bullet::ClearItem();
	Item::ClearItem();
	PlayerBullet::ClearItem();
	Beam::ClearItem();
	Chat::chatitem.Clear();
	BossInfo::Clear();

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
	hge->Input_SetDIKey(KS_CHARGE_(0), false);
	hge->Input_SetDIKey(KS_SLOW_(0), false);

	hge->Input_SetDIKey(KS_UP_(1), false);
	hge->Input_SetDIKey(KS_DOWN_(1), false);
	hge->Input_SetDIKey(KS_LEFT_(1), false);
	hge->Input_SetDIKey(KS_RIGHT_(1), false);
	hge->Input_SetDIKey(KS_FIRE_(1), false);
	hge->Input_SetDIKey(KS_QUICK_(1), false);
	hge->Input_SetDIKey(KS_CHARGE_(1), false);
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
		if(scene < S1200)
			part = data.getStage(scene) - 1;
		/*
		else
			part = RPYPARTMAX - 1;
			*/
		seed = rpy.partinfo[part].seed;
		scene = rpy.partinfo[part].scene;
		mainchara = rpy.rpyinfo.usingchara[0];
		subchara_1 = rpy.rpyinfo.usingchara[1];
		subchara_2 = rpy.rpyinfo.usingchara[2];
		spellmode = rpy.rpyinfo.modeflag & M_RPYMODE_SPELL;
		practicemode = (bool)(rpy.rpyinfo.modeflag & M_RPYMODE_PRACTICE);

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
		Player::p[i].nHiScore = DataConnector::nHiScore();
	}

	//set

	startscene = scene;
	nowdifflv = data.getDiffi(scene);
	if(!practicemode)
	{
		Player::p[0].valueSet(0, mainchara, subchara_1, subchara_2);
		Player::p[1].valueSet(1, mainchara, subchara_1, subchara_2);
	}
	else if(!spellmode)
	{
		Player::p[0].valueSet(0, mainchara, subchara_1, subchara_2, PL_NPLAYERMAX);
		Player::p[1].valueSet(1, mainchara, subchara_1, subchara_2, PL_NPLAYERMAX);
	}
	else
	{
		Player::p[0].valueSet(0, mainchara, subchara_1, subchara_2, 0);
		Player::p[1].valueSet(1, mainchara, subchara_1, subchara_2, 0);
	}
	DataConnector::Try(true);

	if(!replaymode)
	{
		ZeroMemory(&rpy.rpyinfo, sizeof(replayInfo));

		//partinfo
		BYTE part = 0;
		if(scene < S1200)
			part = scene / M_STAGENSCENE - 1;
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
		if(scene < S1200)
			part = data.getStage(scene) - 1;
		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
		{
			if (part)
			{
				Player::p[i].nScore = rpy.partinfo[part].nowscore;
				Player::p[i].nPoint = Player::p[i].nLastPoint = rpy.partinfo[part].nowpoint;
				Player::p[i].nFaith = Player::p[i].nLastFaith = rpy.partinfo[part].nowfaith;
				Player::p[i].nGraze = Player::p[i].nLastGraze = rpy.partinfo[part].nowgraze;
				Player::p[i].nPower = rpy.partinfo[part].nowpower;
				Player::p[i].nNext = Player::p[i].getnNext();
				Player::p[i].changePlayerID(rpy.partinfo[part].nowID);
			}
			Player::p[i].nLife = rpy.partinfo[part].nowplayer;
			if(Player::p[i].nHiScore < Player::p[i].nScore)
				Player::p[i].nHiScore = Player::p[i].nScore;
		}
	}

	BGLayer::ubg[UBGID_BGMASK].valueSetByName(SI_NULL, M_ACTIVECLIENT_CENTER_X, M_ACTIVECLIENT_CENTER_Y, M_ACTIVECLIENT_WIDTH, M_ACTIVECLIENT_HEIGHT, 0);
	BGLayer::ubg[UBGID_FGPAUSE].valueSetByName(SI_NULL, M_ACTIVECLIENT_CENTER_X, M_ACTIVECLIENT_CENTER_Y, M_ACTIVECLIENT_WIDTH, M_ACTIVECLIENT_HEIGHT, 0);
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