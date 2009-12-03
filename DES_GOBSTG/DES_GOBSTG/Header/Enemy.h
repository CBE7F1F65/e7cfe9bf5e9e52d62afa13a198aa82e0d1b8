#ifndef _ENEMY_H
#define _ENEMY_H

#include "BObject.h"
#include "EffectSp.h"
#include "Effectsys.h"
#include "Target.h"

#define ENEMYMAX			0x40

#define ENEMY_MAINBOSSINDEX	0

#define ENID_LEFTIDBEGIN	0x0
#define ENID_LEFTIDUNTIL	(ENEMYMAX/2)
#define ENID_RIGHTIDBEGIN	ENID_LEFTIDUNTIL
#define ENID_RIGHTIDUNTIL	ENEMYMAX

#define ENEMY_TEXMAX		4
#define ENEMY_PARAMAX		4

#define ENEMY_BOSSMAX		ENEMY_TEXMAX

#define ENEMY_BOSSTYPEBEGIN	20

#define ENEMY_ANIMATIONSPEED	8

#define ENEMY_BOSSINFITIMER		240
#define ENEMY_BOSSMOVELIMIT		0.01f
#define ENEMY_ENEMYMOVELIMIT	0.2f

#define ENEMY_FRAME_STAND		0
#define ENEMY_FRAME_RIGHTPRE	1
#define ENEMY_FRAME_RIGHT		2
#define ENEMY_FRAME_LEFTPRE		3
#define ENEMY_FRAME_LEFT		4
#define ENEMY_FRAME_ATTACKPRE	5
#define ENEMY_FRAME_ATTACK		6
#define ENEMY_FRAME_STOREPRE	7
#define ENEMY_FRAME_STORE		8

#define ENEMY_FRAME_STATEMAX	9

//#define ENEMY_COLLISIONR		8

#define ENEMY_BOSSX_FADERANGE	32

#define	ENEMYACTION_ATTACK		0x01
#define	ENEMYACTION_STORE		0x02

#define ENAC_NONE			0x00

#define ENAC_DIRECTSET_XYAS		0x01
#define ENAC_CHASEPLAYER_TFR	0x02
#define ENAC_ATTENUATION_TFER	0x03
#define ENAC_CIRCLE_TXYE		0x04
#define ENAC_BROKENLINE_CATE	0x05
#define ENAC_STOPANDSTRIKE_TEA	0x06

#define ENAC_REPOSITION_T		0x80
#define ENAC_OVERPLAYER_CXYT	0x81
#define ENAC_CHASETO_CXY		0x82

class Enemy : public BObject
{
public:
	Enemy();
	virtual ~Enemy();

	static Enemy * Build(WORD eID, BYTE playerindex, float x, float y, int angle, float speed, BYTE type, float life, int infitimer);
	static void Init(HTEXTURE * tex);
	static void Action(bool notinstop);
	static void ClearAll();
	static void RenderAll(BYTE renderflag);

	static void GetIDBeginUntil(BYTE renderflag, int & idbegin, int & iduntil);

	void Clear();
	bool isInRange(float x, float y, float r);

	void valueSet(BYTE playerindex, WORD eID, float x, float y, int angle, float speed, BYTE type, float life, int infitimer);

	void setTar(BYTE tarID=0xff);
	void setTake(DWORD take=0);
	void setAction(WORD ac=ENAC_NONE, float para0=0, float para1=0, float para2=0, float para3=0);

	void initFrameIndex();
	void setFrame(BYTE frameenum);
	BYTE getFrameIndex(BYTE frameenum);
	void setIndexFrame(BYTE index);
	void updateFrame(BYTE frameenum, int usetimer = -1);
	void updateFrameAsMove();

	void DoShot();

	virtual void action();
	void actionInStop();
	void matchAction();
	void updateAction();

	void GetBlastInfo(BYTE * maxtime=NULL, float * r=NULL, float * power=NULL);

	void GetCollisionRect(float * w, float * h);
	void CostLife(float power);

	void giveItem(BYTE playerindex);

	void Render();
	void RenderEffect();

public:
	Effectsys	effCollapse;
	Effectsys	effShot;

//	EffectSp	esCircle;

	hgeSprite * sprite;

	float	para[ENEMY_PARAMAX];
	Target	aim;
	float	lastx;
	float	life;
	float	defrate;
	DWORD	take;

	BYTE	playerindex;

	bool	fadeout;
	bool	able;
	bool	damage;
	int		infitimer;
	float	maxlife;

	WORD	ac;
	BYTE	type;
	BYTE	damagetimer;

	bool	flipx;
	BYTE	frameoffset;
	BYTE	nowstate;
	BYTE	faceindex;

	BYTE	frameindex[ENEMY_FRAME_STATEMAX];

	static HTEXTURE * tex;
	static BYTE actionflag[ENEMY_BOSSMAX];
	static BYTE spelluptimer[ENEMY_BOSSMAX];
	static BYTE storetimer[ENEMY_BOSSMAX];

	static VectorList<Enemy> en[M_PL_MATCHMAXPLAYER];
};

#endif