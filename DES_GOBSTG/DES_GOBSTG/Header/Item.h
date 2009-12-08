#ifndef _ITEM_H
#define _ITEM_H

#include "BObject.h"

class Player;

//#define ITEMINFOFONTMAX		0x40

#define ITEMTYPEMAX			0x04
#define ITEMSPRITEMAX		ITEMTYPEMAX

#define ITEM_STARTSPEED		-5

#define	ITEM_POWER			0x0
#define	ITEM_POINT			0x1
#define	ITEM_FAITH			0x2
#define	ITEM_BIGPOWER		0x3
#define	ITEM_BOMB			0x4
#define	ITEM_FULL			0x5
#define	ITEM_EXTEND			0x6
#define	ITEM_SMALLFAITH		0x7


class Item : public BObject
{
public:
	Item();
	~Item();

	static void Init();
	static void ClearItem();
	static void Action(DWORD stopflag);
	static void RenderAll(BYTE playerindex);

	static int Build(BYTE playerindex, WORD type, float x, float y, bool bDrained = false, int angle = 9000, float speed = ITEM_STARTSPEED);

	void valueSet(WORD type, float x, float y, bool bDrained = false, int angle = 9000, float speed = ITEM_STARTSPEED);

//	static void ChangeItemID(WORD oriID, WORD toID);
	static void Release();

	void Render();

//	void action();
	void action(BYTE playerindex);
/*
	static void undrainAll();
	static void drainAll();
*/
public:
	bool bDrained;
	bool bFast;

	static hgeSprite *sprite[ITEMSPRITEMAX];
//	static VectorList<infoFont>infofont;

	static VectorList<Item>mi[M_PL_MATCHMAXPLAYER];
};

#endif