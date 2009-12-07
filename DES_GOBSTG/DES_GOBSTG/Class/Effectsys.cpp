#include "Effectsys.h"
#include "Main.h"
#include "Export.h"
#include "Player.h"
#include "Target.h"
#include "ProcessDefine.h"

Effectsys Effectsys::effsys[M_PL_MATCHMAXPLAYER][EFFECTSYSMAX];
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
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		for (int i=0; i<EFFECTSYSMAX; i++)
		{
			effsys[j][i].Clear();
		}
	}
}

void Effectsys::Action(DWORD stopflag)
{
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		bool binstop = FRAME_STOPFLAGCHECK_PLAYERINDEX_(stopflag, j, FRAME_STOPFLAG_EFFECTSYS);
		if (!binstop)
		{
			for (int i=0; i<EFFECTSYSMAX; i++)
			{
				if (effsys[j][i].exist)
				{
					effsys[j][i].action();
				}
			}
		}
	}
}

void Effectsys::RenderAll(BYTE playerindex)
{
	for (int i=0; i<EFFECTSYSMAX; i++)
	{
		if (effsys[playerindex][i].exist)
		{
			effsys[playerindex][i].Render();
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

void Effectsys::valueSet(WORD ID, BYTE playerindex, float x, float y, int lifetime)
{
	valueSet(ID, playerindex, lifetime, x, y, 0, 0xff, 9000, 0, 0);
}

void Effectsys::valueSet(WORD ID, BYTE playerindex, BObject & owner)
{
	valueSet(ID, playerindex, owner.x, owner.y);
}

void Effectsys::valueSet(WORD ID, BYTE playerindex, int lifetime, float x, float y, BYTE tarID, int _chasetimer, BYTE _tarAim)
{
	valueSet(ID, playerindex, lifetime, x, y, 0, tarID, 9000, 0, 0);
	chasetimer = _chasetimer;
	tarAim = _tarAim;
}

void Effectsys::valueSet(WORD _ID, BYTE _playerindex, int _lifetime, float _x, float _y, float _z, BYTE _tarID, int _angle, float _speed, float _zSpeed)
{
	ID			= _ID;
	playerindex	= _playerindex;
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
	BYTE renderflag = Export::GetRenderFlagByPlayerIndex(playerindex);
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