#include "PlayerBullet.h"
#include "Player.h"
#include "Enemy.h"
#include "SE.h"
#include "Main.h"
#include "SpriteItemManager.h"
#include "FrontDisplayName.h"
#include "BResource.h"
#include "Export.h"
#include "EventZone.h"

VectorList<PlayerBullet> PlayerBullet::pb[M_PL_MATCHMAXPLAYER];

int PlayerBullet::locked = PBLOCK_LOST;

hgeSprite * PlayerBullet::sprite[PLAYERSHOOTTYPEMAX][PLAYERBULLETTYPE];
HTEXTURE * PlayerBullet::tex;

DWORD PlayerBullet::bcol0;
DWORD PlayerBullet::bcol1;
DWORD PlayerBullet::bcol2;
DWORD PlayerBullet::bcol3;
WORD PlayerBullet::beams;

#define _PBLOCK_ACCSPEED		1.0f
#define _PBLOCK_MINSPEED		2.0f
#define _PBLOCK_TURNMAX			600
#define _PBLOCK_LOCKTIMERMAX	0x80

#define _PBBEAM_LASTINDEX		1

#define _PBCHASE_TURNSPEEDDOWN	0.8f
#define _PBDELAY_SPEEDDOWN		0.9f
#define _DELAY_TURNMAX		1200

#define _PB_DELETEBOLDER		M_GAMESQUARE_HEIGHT
#define _PB_DELETE_LEFT_(X)		M_DELETECLIENT_LEFT_(X) - _PB_DELETEBOLDER
#define _PB_DELETE_RIGHT_(X)	M_DELETECLIENT_RIGHT_(X) + _PB_DELETEBOLDER
#define _PB_DELETE_TOP			M_DELETECLIENT_TOP - _PB_DELETEBOLDER
#define _PB_DELETE_BOTTOM		M_DELETECLIENT_BOTTOM + _PB_DELETEBOLDER

#define _PB_HEADARCPLUS			10

#define PLAYERBULLETMAX		0x40

#define _PBTEX_PLAYERBEGIN		10

PlayerBullet::PlayerBullet()
{
	able	= false;
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Init(HTEXTURE * _tex)
{
	tex = _tex;
	Release();

	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		pb[i].init(PLAYERBULLETMAX);
	}

	for (int i=0; i<PLAYERSHOOTTYPEMAX; i++)
	{
		for (int j=0; j<4; j++)
		{
			sprite[i][j] = SpriteItemManager::CreateSprite(res.playershootdata[i].siid+(((res.playershootdata[i].flag)&PBFLAG_ANIMATION)?j:0));
		}
	}
}

void PlayerBullet::Release()
{
	for (int i=0; i<PLAYERSHOOTTYPEMAX; i++)
	{
		for (int j=0; j<PLAYERBULLETTYPE; j++)
		{
			SpriteItemManager::FreeSprite(&sprite[i][j]);
		}

	}
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		pb[i].clear();
	}
}

void PlayerBullet::ClearItem()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		pb[i].clear_item();
	}
}

void PlayerBullet::Action()
{
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		if (pb[j].size)
		{
			DWORD i = 0;
			DWORD size = pb[j].size;
			for (pb[j].toBegin(); i<size; pb[j].toNext(), i++)
			{
				if (!pb[j].isValid())
				{
					continue;
				}
				if ((*pb[j]).exist)
				{
					(*pb[j]).action();
				}
				else
				{
					pb[j].pop();
				}
			}
		}
	}
}

void PlayerBullet::RenderAll(BYTE renderflag)
{
	BYTE playerindex = Export::GetPlayerIndexByRenderFlag(renderflag);
	if (pb[playerindex].size)
	{
		DWORD i = 0;
		DWORD size = pb[playerindex].size;
		for (pb[playerindex].toBegin(); i<size; pb[playerindex].toNext(), i++)
		{
			if (pb[playerindex].isValid())
			{
				(*pb[playerindex]).Render();
			}

		}
	}
}

int PlayerBullet::Build(BYTE playerindex, int shootdataID)
{
	if (pb[playerindex].size == PLAYERBULLETMAX)
	{
		return;
	}
	PlayerBullet _pb;
	playershootData * item = &(res.playershootdata[shootdataID]);
	pb[playerindex].push_back(_pb)->valueSet(playerindex, shootdataID, item->arrange, item->xbias, item->ybias, 
		item->scale, item->angle, item->speed, item->accelspeed, 
		item->power, item->hitonfactor, item->flag, item->seID);
	return pb[playerindex].getEndIndex();
}

void PlayerBullet::valueSet(BYTE _playerindex, WORD _ID, BYTE _arrange, float _xbias, float _ybias, float _scale, int _angle, float _speed, float _accelspeed, float _power, int _hitonfactor, WORD _flag, BYTE seID)
{
	playerindex = _playerindex;
	ID		=	_ID;
	angle	=	_angle;
	speed	=	_speed;
	accelspeed = _accelspeed;
	oldspeed =	speed;
	power	=	_power;
	hitonfactor = _hitonfactor;
	arrange	=	_arrange;
	flag	=	_flag;
	xbias	=	_xbias;
	ybias	=	_ybias;
	scale	=	_scale;

	timer	=	0;
	exist	=	true;
	able	=	true;
	fadeout	=	false;
	hscale	=	1.0f;
	vscale	=	1.0f;
	headangle =	0;
	animation	=	0;

	diffuse	=	0xffffff;
	alpha	=	0xC0;

	if (flag & PBFLAG_RANDOMANGLE)
	{
		angle = randt() % (angle * 2 + 1) - angle;
	}
	if (arrange)
	{
		angle += Player::p[playerindex].pg[arrange-1].shootangle;
	}
	if (flag & PBFLAG_ANTISHOOTER)
	{
		if (!arrange)
		{
			angle += Player::p[playerindex].aMainAngle(Player::p[playerindex].lastmx[0], Player::p[playerindex].lastmy[0]);
		}
	}
	else
	{
		angle += 27000;
	}

	xplus	=	speed * cost(angle);
	yplus	=	speed * sint(angle);

	if (flag & PBFLAG_BEAM)
	{
		hscale = M_GAMESQUARE_HEIGHT / SpriteItemManager::GetTexW(res.playershootdata[ID].siid);
		vscale = scale / SpriteItemManager::GetTexH(res.playershootdata[ID].siid);
		angle = -9000;
		alpha = 0x60;
	}
	else
	{
		hscale *= scale;
		vscale *= scale;
	}
	locktimer = 0;

	if(arrange)
	{
		x = Player::p[playerindex].pg[arrange-1].x;
		y = Player::p[playerindex].pg[arrange-1].y;
	}
	else
	{
		x = Player::p[playerindex].x;
		y = Player::p[playerindex].y;
	}

	x += xbias;
	y += ybias;

	SE::push(seID, x);
}

void PlayerBullet::Render()
{
	if (sprite[ID][animation])
	{
		sprite[ID][animation]->SetColor((alpha<<24)|diffuse);
		sprite[ID][animation]->RenderEx(x, y, ARC(angle+headangle), hscale, vscale);
	}
}

bool PlayerBullet::GetLockAim(BObject ** obj)
{
	if(locked == PBLOCK_LOST)
	{
		return false;
	}
	// TODO:
	*obj = &(Enemy::en[0][locked]);
	return true;
}

void PlayerBullet::Lock()
{
	locktimer++;
	BObject * _tpbobj;

	if (!GetLockAim(&_tpbobj))
	{
		if(speed < oldspeed)
			speed += _PBLOCK_ACCSPEED;
		if(speed > oldspeed)
			speed = oldspeed;
		return;
	}

	int aimangle = aMainAngle(*_tpbobj);
	bool clockwise = false;

	if(locktimer >= _PBLOCK_LOCKTIMERMAX)
	{
		locktimer = _PBLOCK_LOCKTIMERMAX;
		angle = aimangle;
	}

	while(angle > 18000)
		angle -= 36000;
	while(angle < -18000)
		angle += 36000;
	while(aimangle > 18000)
		aimangle -= 36000;
	while(aimangle < -18000)
		aimangle += 36000;

	int incangle = aimangle - angle;
	if(incangle > 18000)
		incangle = incangle - 36000;
	else if(incangle < -18000)
		incangle = 36000 + incangle;

	if(incangle > 0 && incangle < 18000)
		clockwise = true;

	incangle = abs(incangle);

	if(timer == 1 && incangle > 9000 && _tpbobj->y > y)
	{
		if(_tpbobj->x > x)
			angle = aimangle - 9000;
		else
			angle = aimangle + 9000;
	}

	if (speed < 0)
	{
		speed *= _PBDELAY_SPEEDDOWN;
	}
	else
	{
		if(incangle < _PBLOCK_TURNMAX)
		{
			angle = aimangle;
			if(speed < oldspeed)
			{
				speed += _PBLOCK_ACCSPEED;
			}
			if(speed > oldspeed)
				speed = oldspeed;
		}
		else
		{
			if(speed > _PBLOCK_MINSPEED)
				speed -= _PBLOCK_ACCSPEED;
			if(speed < _PBLOCK_MINSPEED)
				speed = _PBLOCK_MINSPEED;
			if(clockwise)
				angle += _PBLOCK_TURNMAX;
			else
				angle -= _PBLOCK_TURNMAX;
		}
	}
}

void PlayerBullet::hitOn()
{
	fadeout = true;
	able = false;
	Player::p[playerindex].DoPlayerBulletHit(hitonfactor);
	timer = 0;
}

bool PlayerBullet::isInRange(float aimx, float aimy, float w, float h)
{
	bool hiton = true;
	if (flag & PBFLAG_BEAM)
	{
		hiton = false;
		w += scale / 2;
		aimy += M_GAMESQUARE_HEIGHT / 2;
		h = M_GAMESQUARE_HEIGHT / 2;
	}
	if (checkCollisionSquare(aimx, aimy, w, h))
	{
		if (hiton)
		{
			xplus = aimx - x;
			hitOn();
		}
		else if ((flag & PBFLAG_BEAM) && !(timer % 24))
		{
			Player::p[playerindex].DoPlayerBulletHit(hitonfactor);
		}
		return true;
	}
	return false;
	
}

void PlayerBullet::DelayShoot()
{
	if(locked == PBLOCK_LOST)
	{
		if(timer < PB_FADEOUTTIME)
			timer = PB_FADEOUTTIME;
		if(speed != oldspeed)
		{
			speed = oldspeed;
		}
	}
	else
	{
		BObject * _tpbobj;
		_tpbobj = &Enemy::en[playerindex][locked];
		if(timer == 1)
		{
			speed = -speed;
		}
		if(timer < PB_FADEOUTTIME)
		{
			angle = aMainAngle(*_tpbobj);
			if (flag & PBFLAG_TURNWHILEDELAY)
			{
				if(arrange & 1)
					headangle += _DELAY_TURNMAX;
				else
					headangle -= _DELAY_TURNMAX;
			}
			speed *= _PBCHASE_TURNSPEEDDOWN;
		}
		else if(timer == PB_FADEOUTTIME)
		{
			angle = aMainAngle(*_tpbobj);
			headangle = 0;
			speed = oldspeed;
		}
	}
}

void PlayerBullet::TurnBullet(float mul)
{
	headangle += (xplus<0?1:-1)*_PBLOCK_TURNMAX * mul;
}

void PlayerBullet::action()
{
	timer++;

	if(!fadeout)
	{
		if (flag & PBFLAG_BEAM)
		{
			if (arrange)
			{
				y = Player::p[playerindex].pg[arrange-1].y;
			}
			else
			{
				y = Player::p[playerindex].y;
			}
			y += - M_GAMESQUARE_HEIGHT / 2 + ybias;
			xplus = 0;
			yplus = 0;
			float extramove = 0;
			if (!(arrange && (Player::p[playerindex].pg[arrange-1].flag & PGFLAG_STAY) || (Player::p[playerindex].pg[arrange-1].flag & PGFLAG_ABSSTAY)))
			{
				extramove = (Player::p[playerindex].y-Player::p[playerindex].lasty[_PBBEAM_LASTINDEX]) / 2.5f;
			}
			float _tx, _ty, _tw, _th;
//			sprite[ID]->GetTextureRect(&_tx, &_ty, &_tw, &_th);
//			sprite[ID]->SetTextureRect(_tx - (2.0f + extramove) / accelspeed, _ty, _tw, _th);
			timer = PB_FADEOUTTIME - 8;
			fadeout = true;
		}

		else
		{
			if ((flag & PBFLAG_DELAY) || (flag & PBFLAG_CHASE) || (flag & PBFLAG_TURNWHILEDELAY) || accelspeed)
			{
				if (flag & PBFLAG_DELAY)
				{
					DelayShoot();
				}
				if (flag & PBFLAG_CHASE)
				{
					Lock();
				}
				speed += accelspeed;
				xplus = speed * cost(angle);
				yplus = speed * sint(angle);
			}
			else
			{
				locktimer = 0;
			}

			x += xplus;
			y += yplus;

			if (flag & PBFLAG_TURN)
			{
				TurnBullet(5.0f);
			}
			if (flag & PBFLAG_HEADUPWARD)
			{
				int nowangle = headangle + angle;
				while (nowangle < 0)
				{
					nowangle += 36000;
				}
				while (nowangle >= 36000)
				{
					nowangle -= 36000;
				}
				if (nowangle < 18000)
				{
					headangle += 18000;
				}
			}
		}
		if(x < _PB_DELETE_LEFT_(playerindex) || x > _PB_DELETE_RIGHT_(playerindex) || y < _PB_DELETE_TOP || y > _PB_DELETE_BOTTOM)
			exist = false;
	}
	else
	{
		if(timer == PB_FADEOUTTIME)
		{
			exist = false;
		}
		if (flag & PBFLAG_OUTTURN)
		{
			TurnBullet();
		}
		if (flag & PBFLAG_ANIMATION)
		{
			if (timer % (PB_FADEOUTTIME / 3 + 1) == 1)
			{
				animation++;
				if (animation >= PLAYERBULLETTYPE)
				{
					animation = PLAYERBULLETTYPE-1;
				}
			}
		}
		if (flag & PBFLAG_REBOUND)
		{
			if (xplus < 0)
			{
				x += 1;
			}
			else
			{
				x -= 1;
			}
			y -= 0.5f;
		}
		if (flag & PBFLAG_EXPLODE)
		{
			if (timer == 1)
			{
				SE::push(SE_PLAYER_EXPLODE, x);
			}

			EventZone::Build(EVENTZONE_TYPE_ENEMYGHOSTDAMAGE, playerindex, x, y, 1, SpriteItemManager::GetTexW(res.playershootdata[ID].siid), power);
		}
		if (flag & PBFLAG_SCALEUP)
		{
			hscale = (timer * 0.05f + 1.0f) * scale;
			vscale = hscale;
		}
		if (flag & PBFLAG_BEAM)
		{
			float taimx = Player::p[playerindex].x;
			if (arrange)
			{
				taimx = Player::p[playerindex].pg[arrange-1].x;
			}
			float taimy = Player::p[playerindex].y;
			if (arrange)
			{
				taimy = Player::p[playerindex].pg[arrange-1].y;
			}
			taimx += xbias;
			taimy += -M_GAMESQUARE_HEIGHT / 2 + ybias;
			chaseAim(taimx, taimy, (32-timer));
			angle = -9000;
		}
		alpha = (32 - timer) * 0x06;
	}
	able = exist && !fadeout;
}

float PlayerBullet::CheckShoot(BYTE playerindex, float aimx, float aimy, float aimw, float aimh)
{
	float totalpower = 0.0f;
	if (pb[playerindex].size)
	{
		DWORD i = 0;
		DWORD size = pb[playerindex].size;
		for (pb[playerindex].toBegin(); i<size; pb[playerindex].toNext(), i++)
		{
			if (pb[playerindex].isValid() && (*pb[playerindex]).able)
			{
				if ((*pb[playerindex]).isInRange(aimx, aimy, aimw, aimh))
				{
					totalpower += (*pb[playerindex]).power;
				}
			}
		}
	}
	return totalpower;
}