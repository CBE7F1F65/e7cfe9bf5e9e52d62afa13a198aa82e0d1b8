#include "processPrep.h"

bool Process::reload()
{
	SetCurrentDirectory(hge->Resource_MakePath(""));

	frameskip = M_DEFAULT_FRAMESKIP;

	strcpy(rpyfilename, "");
	replayIndex = 0;

	fdisp.SetState(FDISP_PANEL, 0);
	BGLayer::Init();
	Enemy::ClearAll();
	Ghost::ClearAll();
	Target::ClearAll();
	SelectSystem::Init();
	InfoSelect::Clear();
	chat.Clear();
	BossInfo::Clear();
	Player::Init();

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

	Ghost::index = 0;
	
	Item::Init();
	Beam::Init();
	PlayerBullet::Init(tex);
	SpriteItemManager::Init(tex);

	BossInfo::Init();
	InfoQuad::tex = tex[TEX_WHITE];

	fdisp.Init();
	Fontsys::Init(fdisp.info.normalfont);
	Fontsys::HeatUp();

#ifdef __DEBUG
	HGELOG("\nCleared up.\n");
#endif

	SetCurrentDirectory(hge->Resource_MakePath(""));

	return true;
}