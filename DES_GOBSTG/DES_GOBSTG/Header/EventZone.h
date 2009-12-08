#ifndef _EVENTZONE_H
#define _EVENTZONE_H

#include "MainDependency.h"

#define EVENTZONE_EVENT_NULL	0x0

#define EVENTZONE_TYPE_NULL			0x0000
#define EVENTZONE_TYPE_BULLETFADEOUT	0x0001
#define EVENTZONE_TYPE_SENDBULLET	0x0002
#define EVENTZONE_TYPE_ENEMYDAMAGE	0x0004
#define EVENTZONE_TYPE_NOSEND		0x0008
#define EVENTZONE_TYPE_PLAYERSPEED	0x0010
#define EVENTZONE_TYPE_PLAYERDAMAGE	0x0020

#define EVENTZONE_TYPE_BULLETEVENT	0x00010000
#define EVENTZONE_TYPE_PLAYEREVENT	0x00020000
#define EVENTZONE_TYPE_ENEMYEVENT	0x00040000
#define EVENTZONE_TYPE_GHOSTEVENT	0x00080000

#define EVENTZONE_CHECK_CONTINUEFLAG	0x80000000

#define EVENTZONE_OVERZONE	((M_GAMESQUARE_WIDTH + M_GAMESQUARE_HEIGHT) / 2)

#define EVENTZONE_TYPEMASK_BULLET	(EVENTZONE_TYPE_BULLETFADEOUT|EVENTZONE_TYPE_SENDBULLET|EVENTZONE_TYPE_BULLETEVENT)
#define EVENTZONE_TYPEMASK_PLAYER	(EVENTZONE_TYPE_PLAYERSPEED|EVENTZONE_TYPE_PLAYERDAMAGE|EVENTZONE_TYPE_PLAYEREVENT)
#define EVENTZONE_TYPEMASK_ENEMY	(EVENTZONE_TYPE_ENEMYDAMAGE|EVENTZONE_TYPE_ENEMYEVENT)

class EventZone
{
public:
	EventZone();
	~EventZone();

	static void Clear();
	static void RenderAll(BYTE playerindex);
	static void Build(DWORD type, BYTE playerindex, float x, float y, int maxtime=1, float r=EVENTZONE_OVERZONE, float power=0, DWORD eventID=EVENTZONE_EVENT_NULL, float rspeed=0, int inittimer=0, int siid=-1, int turnangle=0);
	static void Action(DWORD stopflag);

	bool action();
	void Render();

public:
	BYTE playerindex;
	float x;
	float y;
	float r;
	float rspeed;
	float power;
	float width;
	int timer;
	int maxtime;
	int turnangle;
	DWORD type;
	DWORD eventID;
	hgeSprite * sprite;

	static list<EventZone>ezone[M_PL_MATCHMAXPLAYER];
};

#endif