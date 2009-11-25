#ifndef _EFFECTSP_H
#define _EFFECTSP_H

#include "BObject.h"

#define EFFSPSET_FREEBEGIN	0x0
#define EFFSPSET_FREEUNTIL	0x100
#define EFFSPSET_PLAYERUSE	0x100

#define	EFFSP_PLAYERCHANGE		0x01
#define	EFFSP_PLAYERSHOT		0x02
#define	EFFSP_PLAYERBORDER		0x03
#define EFFSP_PLAYERBORDERZONE	0x04
#define	EFFSP_PLAYERPOINT		0x05
#define	EFFSP_PLAYERCOLLAPSE	0x06

#define EFFSP_CHASE_NULL		0x00
#define EFFSP_CHASE_PLAYER_0	0x01
#define EFFSP_CHASE_PLAYER_1	0x02
#define EFFSP_CHASE_PLAYER_(X)	((X)?EFFSP_CHASE_PLAYER_1:EFFSP_CHASE_PLAYER_0)
#define EFFSP_CHASE_TARGET		0x10
#define EFFSP_CHASE_FREE		0x20

class EffectSp : public BObject
{
public:
	EffectSp();
	~EffectSp();

	static void Init();
	static void ClearItem();
	static void Build(int setID, WORD ID, int siid, float x, float y, int headangle=0, float hscale=1.0f, float vscale=0.0f);
	static void Action();
	static void RenderAll();

	void valueSet(int setID, WORD ID, int siid, float x, float y, int headangle=0, float hscale=1.0f, float vscale=0.0f);
	void actionSet(int angle, float speed, int headangleadd=0);
	void chaseSet(BYTE chaseflag, float aimx, float aimy, int chasetimer=-1, BYTE chaseaim=0xff);
	void colorSet(DWORD color, int blend=BLEND_DEFAULT);

	void EffectSpOff(int setID, int ID=-1);

	void action();
	void Render();

	float GetWidth();
	float GetHeight();

public:
	hgeSprite * sprite;

	int setID;

	int chasetimer;
	int headangleadd;
	float aimx;
	float aimy;
	BYTE chaseflag;
	BYTE chaseaim;

	static VectorList<EffectSp> effsp;
};

#endif