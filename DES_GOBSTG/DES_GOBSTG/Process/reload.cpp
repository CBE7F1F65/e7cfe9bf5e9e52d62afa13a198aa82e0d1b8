#include "processPrep.h"

bool Process::reload()
{
	SetCurrentDirectory(hge->Resource_MakePath(""));

	BGLayer::Init();
	Enemy::ClearAll();
	Ghost::ClearAll();
	Target::ClearAll();
	SelectSystem::Init();
	Effectsys::ClearAll();
	ChatItem.Clear();
	BossInfo::Clear();
	Player::Init();

	frameskip = M_DEFAULT_FRAMESKIP;
	strcpy(rpyfilename, "");
	replayIndex = 0;
	pauseinit = false;
	practicemode = false;
	spellmode = false;
	replaymode = false;
	replayFPS = 0;
	scene = S100;
	worldx = 0;
	worldy = 0;
	worldz = 0;
	worldshaketimer = 0;

	Bullet::Init(tex[TEX_BULLET]);
	Enemy::Init(tex[TEX_ENEMY]);
	Item::Init();
	Beam::Init();
	PlayerBullet::Init(tex);
	SpriteItemManager::Init(tex);

	BossInfo::Init();
	InfoQuad::Init(tex[TEX_WHITE]);

	Fdisp.Init();
	Fontsys::Init(Fdisp.info.normalfont);
	Fontsys::HeatUp();

#ifdef __DEBUG
	HGELOG("\nCleared up.\n");
#endif

	SetCurrentDirectory(hge->Resource_MakePath(""));

	return true;
}