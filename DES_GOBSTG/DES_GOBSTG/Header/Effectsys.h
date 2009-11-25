#ifndef _EFFECTSYS_H
#define _EFFECTSYS_H

#include "MainDependency.h"
#include "Const.h"
#include "BObject.h"

#define EFFECTSYSMAX		0x100
#define EFFID_LEFTIDBEGIN	0x0
#define EFFID_LEFTIDUNTIL	(EFFECTSYSMAX/2)
#define EFFID_RIGHTIDBEGIN	EFFID_LEFTIDUNTIL
#define EFFID_RIGHTIDUNTIL	EFFECTSYSMAX

#define EFFSYS_AUTOFADEOUT_TIME	120

class Effectsys : public BObject
{
public:
	Effectsys();
	virtual ~Effectsys();

	static bool Init(HTEXTURE * tex, const char * foldername, char name[][M_PATHMAX]);
	static void ClearAll();
	static void Action();
	static void RenderAll(BYTE renderflag);

	static void GetIDBeginUntil(BYTE renderflag, int & idbegin, int & iduntil);

	void Clear();
	void valueSet(WORD ID, BYTE renderflag, float x, float y, int lifetime = -1);
	void valueSet(WORD ID, BYTE renderflag, int lifetime, float x, float y, float z, BYTE tarID, int angle, float speed, float zSpeed);
	void valueSet(WORD ID, BYTE renderflag, int lifetime, float x, float y, BYTE tarID, int chasetimer, BYTE tarAim);
	void valueSet(WORD ID, BYTE renderflag, BObject & owner);
	void SetRenderFlag(BYTE renderflag);

	void MoveTo(float x, float y, float z = 0, bool bForce = false);
	void Fire();
	void Stop(bool bKill = false);
	void action();

	void Render();

public:
	hgeEffectSystem * eff;

	int lifetime;
	int chasetimer;
	float z;
	float zSpeed;

	BYTE tarAim;
	BYTE renderflag;

	static hgeEffectSystem efftype[EFFECTSYSTYPEMAX];
	static Effectsys effsys[EFFECTSYSMAX];
};

#endif