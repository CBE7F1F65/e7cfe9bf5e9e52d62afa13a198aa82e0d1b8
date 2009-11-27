#include "processPrep.h"

bool Process::reload()
{
	SetCurrentDirectory(hge->Resource_MakePath(""));

	BGLayer::Init(tex);
	Enemy::ClearAll();
	Ghost::ClearAll();
	Target::ClearAll();
	SelectSystem::Init();
	Effectsys::ClearAll();
	Chat::chatitem.Clear();
	BossInfo::Clear();
	Player::Init();
	EventZone::Clear();

	frameskip = M_DEFAULT_FRAMESKIP;
	strcpy(rpyfilename, "");
	replayIndex = 0;
	pauseinit = false;
	replaymode = false;
	replayFPS = 0;
	scene = 0;
//	scene = S100;
	worldx = 0;
	worldy = 0;
	worldz = 0;
	worldshaketimer = 0;
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		if (rendertar[i])
		{
			hge->Target_Free(rendertar[i]);
		}
		if (sprendertar[i])
		{
			delete sprendertar[i];
			sprendertar[i] = NULL;
		}
		rendertar[i] = hge->Target_Create(M_CLIENT_WIDTH, M_CLIENT_HEIGHT, false);
	}

	Bullet::Init(tex[TEX_BULLET]);
	Enemy::Init(tex);
	Item::Init();
	Beam::Init();
	PlayerBullet::Init(tex);
	SpriteItemManager::Init(tex);
	EffectSp::Init();

	BossInfo::Init();
	InfoQuad::Init(tex[TEX_WHITE]);

	FrontDisplay::fdisp.Init();
	Fontsys::Init(FrontDisplay::fdisp.info.normalfont);
	Fontsys::HeatUp();

#ifdef __DEBUG
	HGELOG("\nCleared up.\n");
#endif

	SetCurrentDirectory(hge->Resource_MakePath(""));

	return true;
}