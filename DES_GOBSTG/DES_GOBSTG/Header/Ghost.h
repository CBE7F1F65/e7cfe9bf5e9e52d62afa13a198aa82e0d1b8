#ifndef _GHOST_H
#define _GHOST_H

#include "BObject.h"
#include "Effectsys.h"
#include "Target.h"

#define GHOSTMAX			0x80
#define GHID_LEFTIDBEGIN	0x0
#define GHID_LEFTIDUNTIL	(GHOSTMAX/2)
#define GHID_RIGHTIDBEGIN	GHID_LEFTIDUNTIL
#define GHID_RIGHTIDUNTIL	GHOSTMAX

#define GHOST_COLLISIONR	8

#define GHOST_IZER(LIFE, MAXLIFE)	((LIFE) / (MAXLIFE) * 32.0f)

class Ghost : public BObject
{
public:
	Ghost();
	virtual ~Ghost();

	static bool Build(WORD gID, BYTE tarID, BYTE belong, float x, float y, int angle, float speed, BYTE type, float life, int ac);
	static void ClearAll();
	static void Action(bool notinstop);
	static void RenderAll(BYTE renderflag);

	void Clear();
	void valueSet(WORD ID, float x, float y, int angle, float speed, BYTE type, float life, int ac);
	void valueSet(WORD ID, BYTE belong, int angle, float speed, BYTE type, float life, int ac);
	
	BYTE getPlayerIndex();

	void CostLife(float power);

	void DoShot(BYTE playerindex);

	virtual void action();
	void actionInStop();
	void Render();

public:

	Effectsys effghost;

	Target aim;

	float	life;
	float	maxlife;
	float	cenx;
	float	ceny;
	bool	half;
	bool	gave;
	int		ac;
	bool	fadeout;
	bool	able;
	bool	damage;
	bool	lastborderstate;

	WORD	gID;

	BYTE	belong;
	BYTE	type;

	static WORD index;

	static Ghost gh[GHOSTMAX];
};

#endif
