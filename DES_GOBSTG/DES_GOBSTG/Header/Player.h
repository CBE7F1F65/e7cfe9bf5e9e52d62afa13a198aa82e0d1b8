#ifndef _PLAYER_H
#define _PLAYER_H

#include "BObject.h"
#include "EffectSp.h"
#include "PlayerGhost.h"
#include "PlayerBullet.h"
#include "Effectsys.h"

#define PLAYER_FRAME_STAND		0
#define PLAYER_FRAME_LEFTPRE	1
#define PLAYER_FRAME_LEFT		2
#define PLAYER_FRAME_RIGHTPRE	3
#define PLAYER_FRAME_RIGHT		4

// add
#define PLAYER_DEFAULTINITLIFE	10

#define PL_HITONFACTORDEFAULT	50

#define PL_ITEMDRAINY		144

#define PLAYER_FRAME_STATEMAX	5
#define PLAYER_ANIMATIONSPEED	8

#define PLAYER_BORDEROFFPRE	8

#define PL_DEFAULTNFAITH	10000
#define PL_DEFAULTNPLAYER	2
#define PL_NPLAYERMAX		7

#define PL_MOVABLEDGE_X		8
#define PL_MOVABLEDGE_Y		16
#define PL_MOVABLE_LEFT_(X)		(M_GAMESQUARE_LEFT_(X)+PL_MOVABLEDGE_X)
#define PL_MOVABLE_RIGHT_(X)	(M_GAMESQUARE_RIGHT_(X)-PL_MOVABLEDGE_X)
#define PL_MOVABLE_TOP		(M_GAMESQUARE_TOP+PL_MOVABLEDGE_Y)
#define PL_MOVABLE_BOTTOM	(M_GAMESQUARE_BOTTOM-PL_MOVABLEDGE_Y)

#define PL_MERGEPOS_X_(X)		M_GAMESQUARE_CENTER_X_(X)
#define PL_MERGEPOS_Y		(M_GAMESQUARE_BOTTOM + 40)

#define PL_SAVELASTMAX		0x20

#define	PLAYER_MERGE				0x1
#define	PLAYER_SHOT					0x2
#define	PLAYER_COLLAPSE				0x4
#define	PLAYER_SHOOT				0x8
#define	PLAYER_BORDER				0x10
#define	PLAYER_BOMB					0x20
#define	PLAYER_SLOWCHANGE			0x40
#define	PLAYER_FASTCHANGE			0x80
#define	PLAYER_PLAYERCHANGE			0x100
#define	PLAYER_GRAZE				0x200

#define PLBONUS_GRAZE	0x01
#define PLBONUS_SHOOT	0x02
#define PLBONUS_TIME	0x04

class Player : public BObject
{
public:
	Player();
	virtual ~Player();

	void valueSet(BYTE playerindex, bool bContinue = false);
	void ClearSet();
	void ClearNC();
	void UpdatePlayerData();
	void ResetPlayerGhost(bool move = false);

	virtual void action();

	void RenderEffect();

	bool Merge();
	bool Shot();
	bool Collapse();
	bool Shoot();
	bool Border();
	bool Bomb();
	bool SlowChange();
	bool FastChange();
	bool PlayerChange();
	bool Graze();

	void initFrameIndex();
	void setFrame(BYTE frameenum);
	BYTE getFrameIndex(BYTE frameenum);
	void setIndexFrame(BYTE index);
	void updateFrame(BYTE frameenum, int usetimer = -1);

	void callCollapse();
	bool callBomb(bool onlyborder = false);
	void callSlowFastChange(bool toslow);
	void callPlayerChange();

	void _Shoot();
	void _Bomb();

	void bombAction();

	void Render();

	LONGLONG getItemBonus(WORD itemtype);

	void DoGraze(float x, float y);
	void DoPlayerBulletHit(int hitonfactor = PL_HITONFACTORDEFAULT);
	void DoShot();

	bool HavePlayer(WORD ID);

	void changePlayerID(WORD toID, bool moveghost=false);

	int GrazeRegain(int grazenum);
	void GetScoreLife(float maxlife, bool isenemy = true);

	// add
	void SetInitLife(BYTE initlife);
	void SetChara(WORD id, WORD id_sub_1=0xffff, WORD id_sub_2=0xffff);
	static void AddLostStack();
	static void Action(bool * notinstop);
	static void SetAble(bool setable);
	static bool CheckAble();
	static void RenderAll(BYTE renderflag);

	static void Init();

public:
	WORD	ID_sub_1;
	WORD	ID_sub_2;
	WORD	nowID;

	bool	flipx;
	BYTE	frameoffset;
	BYTE	nowstate;

	float	lastx[PL_SAVELASTMAX];
	float	lasty[PL_SAVELASTMAX];
	float	lastmx[PL_SAVELASTMAX];
	float	lastmy[PL_SAVELASTMAX];

	PlayerGhost pg[PLAYERGHOSTMAX];

	EffectSp	esBorder;
	EffectSp	esBorderZone;
	EffectSp	esChange;
	EffectSp	esShot;
	EffectSp	esPoint;
	EffectSp	esCollapse;

	Effectsys	effGraze;
	Effectsys	effChange;
	Effectsys	effInfi;
	Effectsys	effCollapse;
	Effectsys	effMerge;
	Effectsys	effBorder;
	Effectsys	effBorderOn;
	Effectsys	effBorderOff;

	float	slowspeed;
	float	speedfactor;
	float	r;
	float	graze_r;

	bool	bSlow;
	bool	bInfi;

	hgeSprite * sprite;
	BYTE	frameindex[M_PL_ONESETPLAYER][PLAYER_FRAME_STATEMAX];
	BYTE	faceindex[M_PL_ONESETPLAYER];

	WORD	flag;

	WORD	mergetimer;
	WORD	shottimer;
	WORD	collapsetimer;
	WORD	shoottimer;
	WORD	bordertimer;
	WORD	bombtimer;
	WORD	slowtimer;
	WORD	fasttimer;
	WORD	playerchangetimer;

	BYTE	shotdelay;

	BYTE	nLife;

	// add
	BYTE	initlife;
	BYTE	playerindex;

	int nExPoint;
	int nGhostPoint;
	int nBulletPoint;
	int	nSpellPoint;

	BYTE cardlevel;
	BYTE bosslevel;
	BYTE damagelevel;
	int combogage;
	int charge;

	static BYTE rank;
	static int lilycount;

	static float lostStack;
	static bool able;

	static Player p[M_PL_MATCHMAXPLAYER];

};
#endif