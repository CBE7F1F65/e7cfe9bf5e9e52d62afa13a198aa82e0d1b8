#ifndef _BULLET_H
#define _BULLET_H

#include "BObject.h"
#include "BulletListActionConst.h"

#define BULLETMAX			0x1000
#define BULLETCOLORMAX		0x10
#define BULLETTYPECOLORMAX	(BULLETTYPEMAX * BULLETCOLORMAX)

#define BULLETACTIONMAX		0x20
#define BULLETIZELISTMAX	0x04

#define BULLET_FADEINTYPE	(BULLETTYPEMAX - 3)
#define BULLET_FADEOUTTYPE	(BULLETTYPEMAX - 2)
#define BULLET_BONUSTYPE	(BULLETTYPEMAX - 1)
#define BULLET_ANGLEOFFSET	9000

#define BULLET_FADECOLOR_16	160
#define BULLET_FADECOLOR_8	80

#define BULLET_COLLISION_NONE		0
#define BULLET_COLLISION_CIRCLE		1
#define BULLET_COLLISION_ELLIPSE	2
#define BULLET_COLLISION_SQURE		3

#define BULLET_ANIMATIONSPEED	4

#define BULLET_FADEINTIME	8
#define BULLET_TYPECHANGETIME 16

#define BULLETZONE_ERASE	0
#define BULLETZONE_SEND		1
#define BULLETZONE_EVENT	2

#define BULLET_EVENTMAX		4

#define BULLETACT_FLOATSCALE	100.0f
#define BULLETACT_ANGLECHANGESE	3000

typedef struct tagRenderDepth{
	int startIndex;
	int endIndex;
	bool haveType;
}RenderDepth;

class Bullet : public BObject
{
public:
	Bullet();
	virtual ~Bullet();

	static void Init(HTEXTURE tex);
	static void Release();
	static void ClearItem();
	static void Action(bool noninstop);
	static void RenderAll(BYTE renderflag);
	void Render();

//	virtual void action();
	void action(BYTE playerindex);
	void actionInStop(BYTE playerindex);

	void DoIze(BYTE playerindex);
	void DoCollision(BYTE playerindex);
	void DoGraze(BYTE playerindex);
	void DoUpdateRenderDepth(BYTE playerindex);

	bool HaveGray();

	BYTE getRenderDepth();

	bool isInRect(float r,float aimx,float aimy);

	bool valueSet(WORD ID, float x, float y, bool absolute, int angle, float speed, BYTE type, BYTE color, int fadeinTime, float avoid = 0, BYTE tarID = 0xff);

	static int Build(BYTE playerindex, float x, float y, bool absolute, int angle, float speed, BYTE type, BYTE color, int fadeinTime=BULLET_FADEINTIME, float avoid=0, BYTE tarID=0xff);
	static void BuildCircle(BYTE playerindex, int num, int baseangle, float baser, float x, float y, float speed, BYTE type, BYTE color, int fadeinTime, float avoid);
	static void BuildLine(BYTE playerindex, int num, int baseangle, float space, int baseindex, float x, float y, int angle, float anglefactor, float speed, float speedfactor, BYTE type, BYTE color, int fadeinTime, float avoid);

	void matchFadeInColorType();
	void matchFadeOutColorType();

	static void SendBullet(BYTE playerindex, float x, float y, BYTE setID, BYTE * sendtime=NULL, float * speed = NULL);
	void AddSendInfo(BYTE sendsetID, BYTE _sendtime);

	bool passedEvent(BYTE eventID);
	void passEvent(BYTE eventID);

	void ChangeAction(BYTE playerindex);

public:
	int		actionList[BULLETACTIONMAX];

	float	xplus;
	float	yplus;
	float	lastx;
	float	lasty;
	float	lastspeed;
	int		lastangle;
	int		fadeinTime;

	bool	fadeout;
	bool	able;
	bool	grazed;
	bool	remain;
	bool	cancelable;

	BYTE	type;
	BYTE	oldtype;
	BYTE	color;
	BYTE	oldcolor;
	BYTE	toafter;
	BYTE	typechangetimer;
	BYTE	eventID[BULLET_EVENTMAX];

	BYTE	sendtime;
	BYTE	sendsetID;

	static int _actionList[BULLETACTIONMAX];

	static RenderDepth renderDepth[M_PL_MATCHMAXPLAYER][BULLETTYPEMAX];
	static hgeSprite * sprite[BULLETTYPECOLORMAX];
	static HTEXTURE tex;
	static WORD index;
	static VectorList<Bullet>bu[M_PL_MATCHMAXPLAYER];
};

#endif