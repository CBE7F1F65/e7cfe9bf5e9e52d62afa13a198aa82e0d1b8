#include "Effectsys.h"
#include "Main.h"
#include "Export.h"
#include "Player.h"
#include "Target.h"

Effectsys Effectsys::effsys[EFFECTSYSMAX];
hgeEffectSystem Effectsys::efftype[EFFECTSYSTYPEMAX];

Effectsys::Effectsys()
{
	exist = false;
}

Effectsys::~Effectsys()
{
	Clear();
	eff.FreeList();
}

void Effectsys::Clear()
{
	exist = false;
	eff.Stop(true);
}

void Effectsys::ClearAll()
{
	for (int i=0; i<EFFECTSYSMAX; i++)
	{
		effsys[i].Clear();
	}
}

void Effectsys::Action()
{
	for (int i=0; i<EFFECTSYSMAX; i++)
	{
		if (effsys[i].exist)
		{
			effsys[i].action();
		}
	}
}

void Effectsys::GetIDBeginUntil(BYTE renderflag, int & idbegin, int & iduntil)
{
	if (renderflag == M_RENDER_NULL)
	{
		idbegin = 0x0;
		iduntil = EFFECTSYSMAX;
	}
	else if (renderflag == M_RENDER_LEFT)
	{
		idbegin = EFFID_LEFTIDBEGIN;
		iduntil = EFFID_LEFTIDUNTIL;
	}
	else if (renderflag == M_RENDER_RIGHT)
	{
		idbegin = EFFID_RIGHTIDBEGIN;
		iduntil = EFFID_RIGHTIDUNTIL;
	}
}

void Effectsys::RenderAll(BYTE _renderflag)
{
	int idbegin;
	int iduntil;
	GetIDBeginUntil(_renderflag, idbegin, iduntil);
	for (int i=idbegin; i<iduntil; i++)
	{
		if (effsys[i].exist)
		{
			effsys[i].Render();
		}
	}
}

bool Effectsys::Init(HTEXTURE * tex, const char * foldername, char name[][M_PATHMAX])
{
	char buffer[M_STRMAX];
	for(int i=0;i<EFFECTSYSTYPEMAX;i++)
	{
		strcpy(buffer, foldername);
		strcat(buffer, strlen(name[i]) ? name[i] : name[0]);

		if(Export::effLoad(buffer, &efftype[i], tex) < 0)
		{
			HGELOG("%Failed in loading Effect System File %s.", HGELOG_ERRSTR, buffer);
			hgeEffectBasicInfo ebi;
			ZeroMemory(&ebi, sizeof(hgeEffectBasicInfo));
			efftype[i].SetBasicInfo(&ebi);
		}
	}
	return true;
}

void Effectsys::valueSet(WORD ID, BYTE renderflag, float x, float y, int lifetime)
{
	valueSet(ID, renderflag, lifetime, x, y, 0, 0xff, 9000, 0, 0);
}

void Effectsys::valueSet(WORD ID, BYTE renderflag, BObject & owner)
{
	valueSet(ID, renderflag, owner.x, owner.y);
}

void Effectsys::valueSet(WORD ID, BYTE renderflag, int lifetime, float x, float y, BYTE tarID, int _chasetimer, BYTE _tarAim)
{
	valueSet(ID, renderflag, lifetime, x, y, 0, tarID, 9000, 0, 0);
	chasetimer = _chasetimer;
	tarAim = _tarAim;
}

void Effectsys::valueSet(WORD _ID, BYTE _renderflag, int _lifetime, float _x, float _y, float _z, BYTE _tarID, int _angle, float _speed, float _zSpeed)
{
	ID			= _ID;
	tarID		= _tarID;
	lifetime	= _lifetime;
	x			= _x;
	y			= _y;
	z			= _z;
	angle		= _angle;
	speed		= _speed;
	zSpeed		= _zSpeed;
	headangle	= 0;
	hscale		= 1.0f;
	vscale		= 1.0f;
	timer		= 0;
	SetColorMask(0xffffffff);
	SetRenderFlag(_renderflag);

	chasetimer = 0;

	exist = true;

	if(ID >= EFFECTSYSTYPEMAX)
		ID = 0;

	Clear();
//	eff = new hgeEffectSystem(efftype[ID]);
	eff.InitEffectSystem(efftype[ID]);

	MoveTo(x, y, z, true);
	Fire();
}

void Effectsys::SetRenderFlag(BYTE _renderflag)
{
	renderflag = _renderflag;
}

void Effectsys::Stop(bool bKill /* = false */)
{
	eff.Stop(bKill);
}

void Effectsys::Fire()
{
	eff.Fire();
}

void Effectsys::SetColorMask(DWORD color)
{
	alpha = GETA(color);
	diffuse = color & 0xffffff;
}

void Effectsys::Render()
{
	eff.Render(Export::GetFarPoint(renderflag), (alpha<<24)|diffuse);
}

void Effectsys::MoveTo(float _x, float _y, float _z, bool bForce)
{
	x = _x;
	y = _y;
	z = _z;
	eff.MoveTo(x, y, z, bForce);
}

void Effectsys::action()
{
	timer++;

	if (lifetime > 0)
	{
		if (timer == lifetime)
		{
			Stop();
		}
		else if (timer == lifetime + EFFSYS_AUTOFADEOUT_TIME)
		{
			Stop(true);
			exist = false;
		}
	}

	if (chasetimer)
	{
		chasetimer--;
		chaseAim(Target::tar[tarAim].x, Target::tar[tarAim].y, chasetimer);
	}

	if (speed)
	{
		updateMove();
	}
	z += zSpeed;

	MoveTo(x, y, z);
	if (tarID != 0xff)
	{
		Target::SetValue(tarID, x, y);
	}
	eff.Update();
}