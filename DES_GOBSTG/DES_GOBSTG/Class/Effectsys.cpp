#include "Effectsys.h"
#include "Main.h"
#include "Export.h"
#include "Player.h"
#include "Target.h"
#include "ProcessDefine.h"

VectorList<Effectsys> Effectsys::effsys[M_PL_MATCHMAXPLAYER];
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
		effsys[j].clear_item();
	}
}

void Effectsys::Action(DWORD stopflag)
{
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		bool binstop = FRAME_STOPFLAGCHECK_PLAYERINDEX_(stopflag, j, FRAME_STOPFLAG_EFFECTSYS);
		if (!binstop)
		{
			DWORD i = 0;
			DWORD size = effsys[j].getSize();
			for (effsys[j].toBegin(); i<size; effsys[j].toNext(), i++)
			{
				if ((*effsys[j]).exist)
				{
					(*effsys[j]).action();
				}
			}
		}
	}
}


void Effectsys::RenderAll(BYTE playerindex)
{
	DWORD i = 0;
	DWORD size = effsys[playerindex].getSize();
	for (effsys[playerindex].toBegin(); i<size; effsys[playerindex].toNext(), i++)
	{
		if ((*effsys[playerindex]).exist)
		{
			(*effsys[playerindex]).Render();
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
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		effsys[i].init(EFFECTSYSMAX);
	}
	return true;
}

int Effectsys::Build(WORD ID, BYTE playerindex, float x, float y, float z, int lifetime/* =-1 */, BYTE tarID/* =0xff */, int angle/* =9000 */, float speed/* =0.0f */, float zSpeed/* =0.0f */)
{
	Effectsys _effsys;
	Effectsys * _peffsys = NULL;
	if (effsys[playerindex].getSize() < EFFECTSYSMAX)
	{
		_peffsys = effsys[playerindex].push_back(_effsys);
	}
	else
	{
		DWORD i = 0;
		DWORD size = effsys[playerindex].getSize();
		for (effsys[playerindex].toEnd(); i<size; effsys[playerindex].toNext(), i++)
		{
			if (!effsys[playerindex].isValid())
			{
				_peffsys = effsys[playerindex].push(_effsys);
			}
		}
	}
	if (_peffsys)
	{
		_peffsys->valueSet(ID, playerindex, x, y, z, lifetime, tarID, angle, speed, zSpeed);
		return effsys[playerindex].getIndex();
	}
	else
	{
		return -1;
	}
}


void Effectsys::valueSet(WORD ID, BYTE playerindex, BObject & owner)
{
	valueSet(ID, playerindex, owner.x, owner.y);
}

void Effectsys::chaseSet(int _chasetimer, BYTE _tarAim)
{
	chasetimer = _chasetimer;
	tarAim = _tarAim;
}

void Effectsys::valueSet(WORD _ID, BYTE _playerindex, float _x, float _y, float _z, int _lifetime, BYTE _tarID, int _angle, float _speed, float _zSpeed)
{
	ID			= _ID;
	playerindex	= _playerindex;
	tarID		= _tarID;
	x			= _x;
	y			= _y;
	z			= _z;
	lifetime	= _lifetime;
	angle		= _angle;
	speed		= _speed;
	zSpeed		= _zSpeed;
	headangle	= 0;
	hscale		= 1.0f;
	vscale		= 1.0f;
	timer		= 0;
	SetColorMask(0xffffffff);
	chaseSet(0, 0xff);
	Clear();

	exist = true;

	if(ID >= EFFECTSYSTYPEMAX)
		ID = 0;

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