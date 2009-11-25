#include "EffectSp.h"
#include "Player.h"
#include "Enemy.h"
#include "SpriteItemManager.h"
#include "FrontDisplayName.h"
#include "Bullet.h"
#include "Scripter.h"

#define EFFSPMAX	(BULLETMAX * M_PL_MATCHMAXPLAYER)

VectorList<EffectSp> EffectSp::effsp;

EffectSp::EffectSp()
{
	sprite = NULL;
}

EffectSp::~EffectSp()
{
	if(sprite)
		delete sprite;
	sprite = NULL;
}

void EffectSp::Init()
{
	effsp.init(EFFSPMAX);
}

void EffectSp::ClearItem()
{
	effsp.clear_item();
}

void EffectSp::Render()
{
	sprite->SetColor((alpha<<24)|diffuse);
	sprite->RenderEx(x, y, ARC(angle+headangle), hscale, vscale);
}

void EffectSp::Action()
{
	if (effsp.size)
	{
		DWORD i = 0;
		DWORD size = effsp.size;
		for (effsp.toBegin(); i<size; effsp.toNext(), i++)
		{
			if (effsp.isValid())
			{
				if ((*effsp).exist)
				{
					(*effsp).action();
				}
				else
				{
					effsp.pop();
				}
			}
		}
	}
}

void EffectSp::RenderAll()
{
	if (effsp.size)
	{
		DWORD i = 0;
		DWORD size = effsp.size;
		for (effsp.toBegin(); i<size; effsp.toNext(), i++)
		{
			if (effsp.isValid())
			{
				if ((*effsp).exist)
				{
					(*effsp).Render();
				}
			}
		}
	}
}


void EffectSp::EffectSpOff(int _setID, int _ID)
{
	if (_setID < EFFSPSET_FREEBEGIN || _setID >= EFFSPSET_FREEUNTIL)
	{
		return;
	}
	DWORD nowindex = effsp.index;
	if (effsp.size)
	{
		DWORD i = 0;
		DWORD size = effsp.size;
		for (effsp.toBegin(); i<size; effsp.toNext(), i++)
		{
			if (effsp.isValid())
			{
				if ((*effsp).exist)
				{
					if ((*effsp).setID == _setID)
					{
						if (_ID < 0 || (*effsp).ID == _ID)
						{
							effsp.pop();
						}
					}
				}
			}
		}
	}
	effsp.index = nowindex;
}

void EffectSp::actionSet(int _angle, float _speed, int _headangleadd/* =0 */)
{
	angle = _angle;
	speed = _speed;
	headangleadd = _headangleadd;
}

void EffectSp::chaseSet(BYTE _chaseflag, float _aimx, float _aimy, int _chasetimer/* =-1 */, BYTE _chaseaim/* =0xff */)
{
	if (chaseflag != _chaseflag || _chasetimer != -1)
	{
		chasetimer = _chasetimer;
	}
	if (chaseflag != chaseflag || _chaseaim != 0xff)
	{
		chaseaim = _chaseaim;
	}
	chaseflag = _chaseflag;
	aimx = _aimx;
	aimy = _aimy;
}

void EffectSp::Build(int setID, WORD ID, int siid, float x, float y, int headangle/* =0 */, float hscale/* =1.0f */, float vscale/* =0.0f */)
{
	EffectSp _effsp;
	effsp.push_back(_effsp)->valueSet(setID, ID, siid, x, y, headangle, hscale, vscale);
}

void EffectSp::valueSet(int _setID, WORD _ID, int siid, float _x, float _y, int _headangle/*=0*/, float _hscale/*=1.0f*/, float _vscale/*=0.0f*/)
{
	ID			= _ID;
	setID		= _setID;
	x			= _x;
	y			= _y;
	headangle	= _headangle;
	hscale = _hscale;
	vscale = _vscale;

	chaseflag = EFFSP_CHASE_NULL;
	chasetimer = 0;
	angle = 0;
	speed = 0;
	timer = 0;
	exist = true;
	headangleadd = 0;

	if(sprite)
	{
		SpriteItemManager::FreeSprite(&sprite);
	}
	sprite = NULL;

	colorSet(0xffffffff);

	sprite = SpriteItemManager::CreateSprite(siid);
}

void EffectSp::colorSet(DWORD color, int blend)
{
	alpha = GETA(color);
	diffuse = color & 0xffffff;
	if (sprite)
	{
		sprite->SetBlendMode(blend);
	}
}

float EffectSp::GetWidth()
{
	return sprite->width;
}

float EffectSp::GetHeight()
{
	return sprite->height;
}

void EffectSp::action()
{
	timer++;

	switch (chaseflag)
	{
	case EFFSP_CHASE_PLAYER_0:
		aimx = Player::p[0].x;
		aimy = Player::p[0].y;
		break;
	case EFFSP_CHASE_PLAYER_1:
		aimx = Player::p[1].x;
		aimy = Player::p[1].y;
		break;
	case EFFSP_CHASE_TARGET:
		aimx = Target::tar[chaseaim].x;
		aimy = Target::tar[chaseaim].y;
		break;
	}

	if (chaseflag != EFFSP_CHASE_NULL)
	{
		if (chasetimer > 0)
		{
			chasetimer = chaseAim(aimx, aimy, chasetimer);
		}
		else
		{
			x = aimx;
			y = aimy;
			if (setID >= EFFSPSET_FREEBEGIN && setID < EFFSPSET_FREEUNTIL)
			{
				scr.Execute(SCR_EVENT, SCR_EVENT_EFFSPCHASE, setID);
			}
		}
	}
	headangle += headangleadd;

	updateMove();
}