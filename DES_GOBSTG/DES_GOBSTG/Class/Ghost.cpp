#include "Ghost.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "SE.h"
#include "Bullet.h"
#include "Scripter.h"
#include "Chat.h"
#include "BossInfo.h"
#include "Main.h"
#include "EffectIDDefine.h"

Ghost Ghost::gh[GHOSTMAX];

WORD Ghost::index;

#define PB_SHOOTGHOST_ENEMYCOST 0.25f

Ghost::Ghost()
{
	able			= false;
	effghost.exist	= false;
	gID				= 0;
}

Ghost::~Ghost()
{
}

bool Ghost::Build(WORD _gID, BYTE _tarID, BYTE _belong, float x, float y, int angle, float speed, BYTE type, float life, int ac)
{
	bool rv = false;
	for(int i=0;i<GHOSTMAX;i++)
	{
		index++;
		if(index == GHOSTMAX)
		{
			index = 0;
		}
		if(!gh[index].exist)
		{
			rv = true;
			break;
		}
	}
	if(!rv)
		return false;
	gh[index].gID = _gID;
	gh[index].valueSet(index, x, y, angle, speed, type, life, ac);
	gh[index].belong = _belong;
	gh[index].tarID = _tarID;

	return true;
}

void Ghost::valueSet(WORD _ID, float _x, float _y, int _angle, float _speed, BYTE _type, float _life, int _ac)
{
	ID		=	_ID;
	x		=	_x;
	y		=	_y;
	speed	=	_speed;
	type	=	_type;
	life	=	_life;
	ac		=	_ac;
	angle	=	_angle;

	tarID	=	0xff;

	timer	=	0;
	cenx	=	x;
	ceny	=	y;
	maxlife	=	life;
	exist	=	true;
	fadeout	=	false;
	able	=	true;
	damage	=	false;
	half	=	false;
	gave	=	false;
	lastborderstate = false;
	hscale	=	1.0f;
	vscale	=	1.0f;
	headangle =	0;
	alpha	=	0xff;
	belong	=	0xff;

	aim.x	=	0;
	aim.y	=	0;

	// TODO:
	effghost.valueSet(EFF_GH_TYPEBEGIN + type, M_RENDER_LEFT, *this);

	effghost.Fire();
}

void Ghost::CostLife(float power)
{
	life -= power;
	if (life < 0)
	{
		life = maxlife / 4;
	}
	damage = true;
	if (belong < ENEMYMAX)
	{
		Enemy::en[belong].CostLife(power * PB_SHOOTGHOST_ENEMYCOST);
	}
}

void Ghost::valueSet(WORD ID, BYTE _belong, int angle, float speed, BYTE type, float life, int ac)
{
	valueSet(ID, Enemy::en[_belong].x, Enemy::en[_belong].y,angle, speed, type, life, ac);
	belong = _belong;
}

void Ghost::Render()
{
	effghost.Render();
}

void Ghost::actionInStop()
{
	BYTE playerindex = getPlayerIndex();
	if (!fadeout && !half && Player::p[playerindex].bBorder)
	{
		DoShot(playerindex);
	}
}

BYTE Ghost::getPlayerIndex()
{
	if (ID >= GHID_LEFTIDBEGIN && ID < GHID_LEFTIDUNTIL)
	{
		return 0;
	}
	else if (ID >= GHID_RIGHTIDBEGIN && ID < GHID_RIGHTIDUNTIL)
	{
		return 1;
	}
	return 0;
}

void Ghost::DoShot(BYTE playerindex)
{
	float costpower = PlayerBullet::CheckShoot(playerindex, x, y, 32);
	if (costpower)
	{
		CostLife(costpower);
	}
	if (Enemy::dmgz[playerindex].size)
	{
		DWORD i = 0;
		DWORD size = Enemy::dmgz[playerindex].size;
		for (Enemy::dmgz[playerindex].toBegin(); i<size; Enemy::dmgz[playerindex].toNext(), i++)
		{
			if (Enemy::dmgz[playerindex].isValid())
			{
				DamageZone * tdmg = &(*(Enemy::dmgz[playerindex]));
				if (checkCollisionCircle(tdmg->x, tdmg->y, tdmg->r))
				{
					CostLife(tdmg->power);
					Player::p[playerindex].DoPlayerBulletHit();
				}
			}
		}
	}
}

void Ghost::ClearAll()
{
	for (int i=0; i<GHOSTMAX; i++)
	{
		gh[i].Clear();
	}
	index = 0;
}

void Ghost::Clear()
{
	exist = false;
	able = false;
	timer = 0;
}

void Ghost::Action(bool notinstop)
{
	for (int i=0; i<GHOSTMAX; i++)
	{
		if (gh[i].exist)
		{
			if (notinstop)
			{
				gh[i].action();
			}
			else
			{
				gh[i].actionInStop();
			}
		}
	}
}

void Ghost::RenderAll(BYTE renderflag)
{
	if (renderflag == M_RENDER_LEFT)
	{
		for (int i=GHID_LEFTIDBEGIN; i<GHID_LEFTIDUNTIL; i++)
		{
			if (gh[i].exist)
			{
				gh[i].Render();
			}
		}
	}
	else if (renderflag == M_RENDER_RIGHT)
	{
		for (int i=GHID_RIGHTIDBEGIN; i<GHID_RIGHTIDUNTIL; i++)
		{
			if (gh[i].exist)
			{
				gh[i].Render();
			}
		}
	}
}

void Ghost::action()
{
	timer++;

	BYTE playerindex = getPlayerIndex();
	if(life < maxlife / 2 && life > 0)
	{
		if (!half)
		{
			SE::push(SE_GHOST_HALF, x);
			half = true;
		}
	}

	if(!fadeout && !gave && half && (Player::p[playerindex].bBorder))
	{
		Item::Build(playerindex, ITEM_FAITH, x, y, true);

		gave = true;
	}

	if (Player::p[playerindex].bBorder ^ lastborderstate)
	{
		// TODO:
		effghost.valueSet(EFF_GH_TYPEBEGIN + type + (Player::p[playerindex].bBorder?1:0), M_RENDER_LEFT, *this);
		effghost.Fire();
		lastborderstate ^= true;
	}

	if(!fadeout)
	{
		if(timer == 1)
		{
			SE::push(SE_GHOST_MERGE, x);
		}

		if(Chat::chatitem.IsChatting() || BossInfo::flag >= BOSSINFO_COLLAPSE)
		{
			life = 0;
			fadeout = true;
			timer = 0;
		}

		if(gID && !Scripter::stopEdefScript)
		{
			WORD tindex = index;
			index = ID;
			scr.Execute(SCR_EDEF, gID, timer);
			index = tindex;
		}

		if(Player::p[playerindex].bBorder)
		{
			if (checkCollisionSquare(Player::p[playerindex], GHOST_COLLISIONR))
			{
				Player::p[playerindex].DoShot();
			}
			DoShot(playerindex);
		}

		if(belong != 0xff)
		{
			if(Enemy::en[belong].exist)
			{
				cenx = Enemy::en[belong].x;
				ceny = Enemy::en[belong].y;
			}
			else
			{
				if(Enemy::en[belong].life >= 0)
				{
					life = 0;
				}
				timer = 0;
				fadeout = true;
			}
		}

		if(life < 0)
		{
			WORD tindex = index;
			index = ID;
			scr.Execute(SCR_EDEF, gID, SCRIPT_CON_POST);
			index = tindex;

			if (life < 0)
			{
				Player::p[playerindex].GetScoreLife(maxlife, false);

				fadeout = true;
				timer = 0;
			}
		}
		else if(ac && belong != 0xff)
		{
			angle += ANGLE(speed / ac);

			float tr2 = DIST2(x, y, cenx, ceny);
			float trac2 = ac * ac;
			float tac = fabsf(ac);
			float trac = tac;
			if(tr2 < trac2)
			{
				trac = sqrtf(tr2) + fabsf(speed);
				if(trac > tac)
					trac = tac;
			}
			else if(tr2 > trac2)
			{
				trac = sqrtf(tr2) - fabsf(speed);
				if(trac < tac)
					trac = tac;
			}
			if(ac < 0)
				trac = -trac;

			x = cenx + trac * cost(angle);
			y = ceny + trac * sint(angle);
		}
		else
		{
			updateMove();
		}

		if(tarID != 0xff)
		{
			Target::SetValue(tarID, x, y);
		}

		effghost.MoveTo(x, y);
		effghost.action();

		if(belong == 0xff)
		{
			if(timer > (DWORD)ac)
			{
				life = 0;
				fadeout = true;
				timer = 0;
			}
		}
	}
	else
	{
		effghost.action();
		if(timer == 32)
		{
			effghost.Stop();
			exist = false;
		}
	}

	damage = false;
	able = exist && !fadeout;
}