#include "Item.h"
#include "Player.h"
#include "Bullet.h"
#include "SE.h"
#include "SpriteItemManager.h"
#include "FrontDisplayName.h"
#include "FrontDisplay.h"
#include "Export.h"

hgeSprite * Item::sprite[ITEMSPRITEMAX];

//VectorList<infoFont> Item::infofont;
VectorList<Item> Item::mi[M_PL_MATCHMAXPLAYER];

#define ITEMMAX				0x10

#define _ITEM_GETR				32
#define _ITEM_DRAINDELAY		24
#define _ITEM_DRAINFASTSPEED	8.8f
#define _ITEM_DRAINSLOWSPEED	5.0f
#define _ITEM_FAITHUPSPEED		-1.0f
#define _ITEM_DROPSPEEDMAX		2.8f
#define _ITEM_DROPSPEEDACC		0.1f
#define _ITEM_RETHROWSPEED		-3.0f

Item::Item()
{
}

Item::~Item()
{
}

void Item::ClearItem()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		mi[i].clear_item();
	}
//	infofont.clear_item();
}

void Item::Action(bool notinpause)
{
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		if (mi[j].getSize())
		{
			DWORD i = 0;
			DWORD size = mi[j].getSize();
			for (mi[j].toBegin(); i<size; mi[j].toNext(), i++)
			{
				if (!mi[j].isValid())
				{
					continue;
				}
				if ((*mi[j]).exist)
				{
					(*mi[j]).action(j);
				}
				else
				{
					mi[j].pop();
				}
			}
		}
	}
	/*
	if (infofont.getSize())
	{
		DWORD i = 0;
		DWORD size = infofont.getSize();
		for (infofont.toBegin(); i<size; infofont.toNext(), i++)
		{
			if (infofont.isValid())
			{
				infoFont * _i = &(*(infofont));
				if(notinpause)
				{
					_i->timer++;
					if(_i->timer >= 32)
					{
						infofont.pop();
					}
					if (_i->timer == 24 || _i->timer == 28)
					{
						for(int i=0; i<(int)strlen(_i->cScore); i++)
						{
							_i->cScore[i] += 10;
						}
					}
				}
			}
		}
	}
	*/
}

void Item::RenderAll(BYTE renderflag)
{
	BYTE playerindex = Export::GetPlayerIndexByRenderFlag(renderflag);
	if (mi[playerindex].getSize())
	{
		DWORD i = 0;
		DWORD size = mi[playerindex].getSize();
		for (mi[playerindex].toBegin(); i<size; mi[playerindex].toNext(), i++)
		{
			if (mi[playerindex].isValid())
			{
				(*mi[playerindex]).Render();
			}
		}
	}
	/*
	if (infofont.getSize())
	{
		DWORD i = 0;
		DWORD size = infofont.getSize();
		for (infofont.toBegin(); i<size; infofont.toNext(), i++)
		{
			if (!infofont.isValid())
			{
				continue;
			}
			infoFont * _i = &(*(infofont));
			FrontDisplay::fdisp.ItemInfoDisplay(_i);
		}
	}
	*/
}

void Item::Init()
{
	Release();
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		mi[i].init(ITEMMAX);
	}
//	infofont.init(ITEMINFOFONTMAX);
	int tidx = SpriteItemManager::GetIndexByName(SI_ITEM_GUARD);
	for(int i=0;i<ITEMTYPEMAX;i++)
	{
		sprite[i] = SpriteItemManager::CreateSprite(tidx+i);
	}
}

void Item::valueSet(WORD type, float _x, float _y, bool _bDrained, int _angle, float _speed)
{
	ID			=	type;
	x			=	_x;
	y			=	_y;
	bDrained	=	_bDrained;

	bFast	=	true;

	timer	=	0;
	speed	=	_speed;
	angle	=	_angle;
	headangle =	0;
	hscale	=	1.0f;
	vscale	=	1.0f;
	alpha	=	0xff;
	exist	=	true;
}

int Item::Build(BYTE playerindex, WORD type, float _x, float _y, bool _bDrained /* = false */, int _angle, float _speed)
{
	if (mi[playerindex].getSize() == ITEMMAX)
	{
		return -1;
	}
	mi[playerindex].push_back()->valueSet(type, _x, _y, _bDrained, _angle, _speed);
	return mi[playerindex].getEndIndex();
}

void Item::Release()
{
	for (int i=0; i<ITEMSPRITEMAX; i++)
	{
		if(sprite[i])
			SpriteItemManager::FreeSprite(&sprite[i]);
	}
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		mi[i].clear();
	}
//	infofont.clear();
}

void Item::Render()
{
	if (sprite[ID])
	{
		sprite[ID]->RenderEx(x, y, ARC(headangle));
	}
}

void Item::action(BYTE playerindex)
{
	if(!bDrained && !(Player::p[playerindex].flag & PLAYER_COLLAPSE || Player::p[playerindex].flag & PLAYER_SHOT))
	{
		float rdrain = (Player::p[playerindex].bSlow) ? 64 : 48;
		if (checkCollisionSquare(Player::p[playerindex].x, Player::p[playerindex].y, rdrain))
		{
			bDrained = true;
			bFast = false;
		}
	}
	if(bDrained)
	{
		if(timer > _ITEM_DRAINDELAY)
		{
			if(bFast)
				speed = _ITEM_DRAINFASTSPEED;
			else
				speed = _ITEM_DRAINSLOWSPEED;
			float dist = DIST(x, y, Player::p[playerindex].x, Player::p[playerindex].y);
			x += speed * (Player::p[playerindex].x - x) / dist;
			y += speed * (Player::p[playerindex].y - y) / dist;
		}
		else
		{
			speed = _ITEM_FAITHUPSPEED;
			y += speed;
		}
	}
	else if(speed > 0)
	{
		angle = 9000;
	}

	if (speed > 0)
	{
		headangle = 0;
	}
	else
	{
		headangle += SIGN((int)mi[playerindex].getIndex()) * 600 * speed;
	}

	timer++;
	if(speed < _ITEM_DROPSPEEDMAX)
		speed += _ITEM_DROPSPEEDACC;
	if(!bDrained)
	{
		if(angle != 9000)
		{
			updateMove();
		}
		else
			y += speed;
	}

	if (checkCollisionSquare(Player::p[playerindex].x, Player::p[playerindex].y, _ITEM_GETR)
		&& !(Player::p[playerindex].flag & PLAYER_COLLAPSE)
		&& !((ID == ITEM_SMALLFAITH || ID == ITEM_FAITH) && timer <= _ITEM_DRAINDELAY))
	{
		DWORD score;

		if(ID != ITEM_BOMB && ID != ITEM_EXTEND)
			SE::push(SE_ITEM_GET, x);
		else
			SE::push(SE_ITEM_EXTEND, x);

		score = Player::p[playerindex].DoItemGet(ID);

		exist = false;

		/*
		struct ScoreDisplay info;
		itoa(score, info.cScore, 10);

		info.timer = 0;
		info.x = x;
		info.y = y;
		
		if(ID == ITEM_POINT && (Player::p[playerindex].fPoprate) >= 1.0f)
			info.yellow = true;
		else
		
			info.yellow = false;
		infofont.push_back(info);
		*/
	}
	if(y > M_DELETECLIENT_BOTTOM)
		exist = false;
}