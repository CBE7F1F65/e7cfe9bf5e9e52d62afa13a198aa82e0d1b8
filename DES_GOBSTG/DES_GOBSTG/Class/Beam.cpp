#include "Beam.h"
#include "Bullet.h"
#include "Player.h"
#include "SE.h"
#include "Chat.h"
#include "BossInfo.h"
#include "Item.h"
//#include "Main.h"
#include "Target.h"
#include "Export.h"

#define	BEAMMAX				0x50

VectorList<Beam> Beam::be[M_PL_MATCHMAXPLAYER];

Beam::Beam()
{
	able	= false;
}

Beam::~Beam()
{
}

void Beam::Init()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		be[i].init(BEAMMAX);
	}
}

void Beam::ClearItem()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		be[i].clear_item();
	}
}

void Beam::Action()
{
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		if (be[j].size)
		{
			DWORD i = 0;
			DWORD size = be[j].size;
			for (be[j].toBegin(); i<size; be[j].toNext(), i++)
			{
				if (!be[j].isValid())
				{
					continue;
				}
				if ((*be[j]).exist)
				{
					(*be[j]).action(j);
				}
				else
				{
					be[j].pop();
				}
			}
		}
	}
}

void Beam::RenderAll(BYTE renderflag)
{
	BYTE playerindex = Export::GetPlayerIndexByRenderFlag(renderflag);
	if (be[playerindex].size)
	{
		DWORD i = 0;
		DWORD size = be[playerindex].size;
		for (be[playerindex].toBegin(); i<size; be[playerindex].toNext(), i++)
		{
			if (be[playerindex].isValid())
			{
				(*be[playerindex]).Render();
			}
		}
	}
}

int Beam::Build(BYTE playerindex, float x, float y, int angle, float speed, BYTE type, BYTE color, WORD length, BYTE flag, int fadeouttime, BYTE tarID)
{
	if (be[playerindex].size == BEAMMAX)
	{
		return NULL;
	}
	Beam * _tbe;
	_tbe = be[playerindex].push_back();
	int beindex = be[playerindex].getEndIndex();
	_tbe->valueSet(beindex, x, y, angle, speed, type, color, length, flag, fadeouttime, tarID);
	return beindex;
}

void Beam::Render()
{
	int i = type*BULLETCOLORMAX+color;
	if (Bullet::sprite[i])
	{
		int tblend = Bullet::sprite[i]->GetBlendMode();
		Bullet::sprite[i]->SetBlendMode(BLEND_ALPHAADD);
		Bullet::sprite[i]->SetColor(alpha<<24|diffuse);
		Bullet::sprite[i]->RenderEx(x, y, ARC(angle+headangle+BULLET_ANGLEOFFSET), vscale, hscale);
		Bullet::sprite[i]->SetBlendMode(tblend);
	}
}

void Beam::valueSet(WORD _ID, float _x, float _y, int _angle, float _speed, BYTE _type, BYTE _color, WORD _length, BYTE _flag, int _fadeouttime, BYTE _tarID)
{
	ID			=	_ID;
	x			=	_x;
	y			=	_y;
	angle		=	_angle;
	speed		=	_speed;
	type		=	_type;
	color		=	_color;
	length		=	_length;
	flag		=	_flag;
	fadeouttime	=	_fadeouttime;

	tarID		=	_tarID;
	holdtar		=	0xff;
	pintar		=	0xff;
	holdoffset	=	0;

	timer			=	0;
	grazetimer		=	0;
	exist			=	true;
	fadeout			=	false;
	able			=	true;
	headangle		=	0;
	alpha			=	0xff;

	lastangle = angle;

	xplus = cost(angle);
	yplus = sint(angle);
	if(flag & BEAMFLAG_HORIZON)
	{
		hscale = length / 16.0f;
		vscale = 0.1f;
		x += length * cost(angle) / 2;
		y += length * sint(angle) / 2;
		speed /= 100.0f;
	}
	else
	{
		hscale = 0;
		vscale = 1;
		xplus *= speed;
		yplus *= speed;
	}
}

void Beam::SetVector(const BObject &ori, const BObject &aim)
{
	SetVector(ori.x, ori.y, aim.x, aim.y);
}

void Beam::SetVector(float orix, float oriy, float aimx, float aimy)
{
	length = DIST(orix, oriy, aimx, aimy) + holdoffset;
	x = (orix + aimx) / 2;
	y = (oriy + aimy) / 2;
	hscale = length / 16.0f;
	angle = aMainAngle(aimx, aimy);
}

void Beam::SetHold(BYTE _holdtar, float _holdoffset)
{
	holdtar = _holdtar;
	holdoffset = _holdoffset;
}

void Beam::SetHold(BYTE _holdtar, BYTE _pintar, float holdoffset)
{
	SetHold(_holdtar, holdoffset);
	pintar = _pintar;
}

void Beam::action(BYTE playerindex)
{
	if(angle != lastangle)
	{
		xplus = speed * cost(angle);
		yplus = speed * sint(angle);
		lastangle = angle;
		lastspeed = speed;
	}
	timer++;

	if(!fadeout)
	{
		if(BossInfo::flag >> 2)
		{
			fadeout = true;
			timer = 0;
		}
		if(timer == 1)
			SE::push(SE_BEAM_1, x);
		if(!(flag & BEAMFLAG_HORIZON))
		{
			if(hscale * 16.0f < length)
			{
				x += xplus / 2;
				y += yplus / 2;
				hscale += speed / 16.0f;
			}
			else if(!(flag & BEAMFLAG_STOP))
			{
				x += xplus;
				y += yplus;
			}
		}
		else
		{
			if(vscale < 1)
				vscale += speed;
		}
		if ((flag & BEAMFLAG_HORIZON) || (flag & BEAMFLAG_STOP))
		{
			if(timer > (DWORD)fadeouttime)
			{
				fadeout = true;
				timer = 0;
			}
		}
		if (holdtar != 0xff)
		{
			if (pintar != 0xff)
			{
				SetVector(Target::tar[holdtar].x, Target::tar[holdtar].y, Target::tar[pintar].x, Target::tar[pintar].y);
			}
			else
			{
				float factor = (hscale * 16.0f - holdoffset) / speed;
				SetVector(Target::tar[holdtar].x, Target::tar[holdtar].y, Target::tar[holdtar].x + factor * xplus, Target::tar[holdtar].y + factor * yplus);
			}
		}

		if(tarID != 0xff)
		{
			Target::SetValue(tarID, x, y);
		}

		if(Chat::chatitem.IsChatting())
		{
			fadeout = true;
			timer = 0;
		}

		if(isInRect(Player::p[playerindex].r, Player::p[playerindex].x, Player::p[playerindex].y))
		{
			Player::p[playerindex].DoShot();
		}

		if (!(flag & BEAMFLAG_NOGRAZE))
		{
			if(grazetimer)
			{
				grazetimer++;
				if(grazetimer == 6)
					grazetimer = 0;
			}
			else
			{
				grazetimer++;
				if(isInRect(PLAYER_GRAZE_R, Player::p[playerindex].x, Player::p[playerindex].y))
				{
					float itemx;
					float itemy;
					float tk = 0;
					if (xplus || yplus)
					{
						tk = - ((x - Player::p[playerindex].x) * xplus + (y - Player::p[playerindex].y) * yplus) / (xplus * xplus + yplus * yplus);
						itemx = x + xplus * tk;
						itemy = y + yplus * tk;
					}
					else
					{
						itemx = Player::p[playerindex].x;
						itemy = Player::p[playerindex].y;
					}
					Player::p[playerindex].DoGraze(itemx, itemy);
				}
			}

		}
		if(	x - hscale * 16 > M_DELETECLIENT_RIGHT_(playerindex) ||
			x + hscale * 16 < M_DELETECLIENT_LEFT_(playerindex) ||
			y - hscale * 16 > M_DELETECLIENT_BOTTOM ||
			y + hscale * 16 < M_DELETECLIENT_TOP)
			exist = false;
	}
	else
	{
		if(timer == 1)
		{
			SE::push(SE_BEAM_FADEOUT, x);
		}
		if(timer == 32)
			exist = false;
		else
		{
			vscale -= 0.03125;
			alpha = (BYTE)(32-timer) * 8 - 1;
		}
	}
	able = exist && !fadeout;
}

bool Beam::isInRect(float r, float aimx, float aimy)
{
	if(vscale < BEAM_INVALIDSCALE)
		return false;
	float nowlength = hscale * 5;
	float cx = x;
	float cy = y;

//	nowlength *= 0.3125f;

	float rotCos;
	float rotSin;
	if (!(flag & BEAMFLAG_HORIZON) && speed != 0)
	{
		rotCos = xplus / speed;
		rotSin = yplus / speed;
	}
	else
	{
		rotCos = cost(angle);
		rotSin = sint(angle);
	}
	return checkCollisionEllipse(aimx, aimy, 5.0f*vscale, nowlength, rotCos, rotSin, r);

}