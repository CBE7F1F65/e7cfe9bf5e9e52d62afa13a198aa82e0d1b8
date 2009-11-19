#ifndef _BRESOURCE_H
#define _BRESOURCE_H

#include "MainDependency.h"
#include "DataStruct.h"

#define RSIZE_RESOURCE		(sizeof(resourceData))
#define RSIZE_STRINGDESC	(sizeof(char) * M_STRMAX * STRINGDESCMAX)
#define RSIZE_CUSTOMCONST	(sizeof(customconstData) * SCR_CUSTOMCONSTMAX)
#define RSIZE_MUSIC			(sizeof(musicData) * MUSICMAX)
#define RSIZE_SCENE			(sizeof(sceneData) * SCENEMAX)
#define RSIZE_BULLET		(sizeof(bulletData) * BULLETTYPEMAX)
#define RSIZE_ENEMY			(sizeof(enemyData) * ENEMYTYPEMAX)
#define RSIZE_PLAYER		(sizeof(playerData) * PLAYERTYPEMAX)
#define RSIZE_SPRITE		(sizeof(spriteData) * SPRITEITEMMAX)
#define RSIZE_PLAYERBULLET	(sizeof(playerbulletData) * PLAYERBULLETSPRITEMAX)
#define RSIZE_PLAYERSHOOT	(sizeof(playershootData) * PLAYERSHOOTTYPEMAX)
#define RSIZE_PLAYERGHOST	(sizeof(playerghostData) * PLAYERGHOSTTYPEMAX)

class BResource
{
public:

	BResource();
	~BResource();

	bool Fill();
	bool Pack(void * pStrdesc, void * pCustomConstName);
	bool Gain(void * pStrdesc = NULL, void * pCustomConstName = NULL);
	void CopyData();
	void GetUIString();
	bool SetDataFile();
	bool LoadPackage();

	void ReleaseCustomConst();

public:

	musicData musdata[MUSICMAX];
	sceneData scenedata[SCENEMAX];
	resourceData resdata;
	vector<spellData> spelldata;
	bulletData bulletdata[BULLETTYPEMAX];
	enemyData enemydata[ENEMYTYPEMAX];
	playerData playerdata[PLAYERTYPEMAX];
	spriteData spritedata[SPRITEITEMMAX];
	playerbulletData playerbulletdata[PLAYERBULLETSPRITEMAX];
	playershootData playershootdata[PLAYERSHOOTTYPEMAX];
	playerghostData playerghostdata[PLAYERGHOSTTYPEMAX];
	customconstData * customconstdata;
};

extern BResource res;
extern HGE * hge;

#endif