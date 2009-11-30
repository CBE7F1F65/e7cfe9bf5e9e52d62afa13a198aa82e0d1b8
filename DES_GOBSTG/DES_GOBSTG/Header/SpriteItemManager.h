#ifndef _SPRITEITEMMANAGER_H
#define _SPRITEITEMMANAGER_H

#include "MainDependency.h"
#include "DataStruct.h"

#define FRONTSPRITEMAX		0x40

struct FrontSprite
{
	hgeSprite * sprite;
	float x;
	float y;
	float rot;
	float hscale;
	float vscale;
};

class SpriteItemManager
{
public:
	SpriteItemManager();
	~SpriteItemManager();

	static void Init(HTEXTURE * tex);
	static void Release();
	static hgeSprite * CreateSprite(int index);
	static bool CreateSprite(int index, hgeSprite ** sprite);
	static bool ChangeSprite(int index, hgeSprite * sprite);
	static int GetIndexByName(const char * spritename);
	static hgeSprite * CreateSpriteByName(const char * spritename);
	static bool CreateSpriteByName(const char * spritename, hgeSprite ** sprite);
	static void FreeSprite(hgeSprite ** sprite);
	static spriteData * CastSprite(int index);

	static hgeSprite * BuildFrontSprite(int ID, int index);
	static hgeSprite * BuildFrontSpriteByName(int ID, const char * spritename);
	static void SetFrontSpriteValue(int ID, float x, float y, int angle=0, float hscale=1.0f, float vscale=0.0f);
	static void FreeFrontSprite(int ID=-1);
	static void RenderFrontSprite();

	static bool SetSprite(int index, hgeSprite * sprite, HTEXTURE * tex);

	static HTEXTURE GetTexture(int index);
	static float GetTexX(int index);
	static float GetTexY(int index);
	static float GetTexW(int index);
	static float GetTexH(int index);

	static bool ptFace(int index, hgeSprite * sprite, bool enemy = true);
	static bool ptName(int index, hgeSprite * sprite, bool enemy = true);

public:
	static HTEXTURE * tex;

	static int faceIndexEnemy;
	static int nameIndexEnemy;
	static int faceIndexPlayer;
	static int nameIndexPlayer;

	static int yesIndex;
	static int noIndex;
	static int cancelIndex;
	static int confirmIndex;

	static FrontSprite frontsprite[FRONTSPRITEMAX];
};

#endif