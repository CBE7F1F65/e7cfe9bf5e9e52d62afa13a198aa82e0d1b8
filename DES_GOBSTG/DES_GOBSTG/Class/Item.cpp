#include "Item.h"
#include "Player.h"
#include "Bullet.h"
#include "SE.h"
#include "SpriteItemManager.h"
#include "FrontDisplayName.h"
#include "FrontDisplay.h"

hgeSprite * Item::spItem[ITEMSPRITEMAX];

VectorList<infoFont> Item::infofont;
VectorList<Item> Item::mi;

#define _ITEM_GETR				32
#define _ITEM_DRAINY			PL_ITEMDRAINY
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
	mi.clear_item();
	infofont.clear_item();
}

void Item::Action(bool notinpause)
{
	if (mi.size)
	{
		DWORD i = 0;
		DWORD size = mi.size;
		for (mi.toBegin(); i<size; mi.toNext(), i++)
		{
			if (!mi.isValid())
			{
				continue;
			}
			if ((*mi).exist)
			{
				(*mi).action();
			}
			else
			{
				mi.pop();
			}
		}
	}
	if (infofont.size)
	{
		DWORD i = 0;
		DWORD size = infofont.size;
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
}

void Item::RenderAll()
{
	if (mi.size)
	{
		DWORD i = 0;
		DWORD size = mi.size;
		for (mi.toBegin(); i<size; mi.toNext(), i++)
		{
			if (mi.isValid())
			{
				(*mi).Render();
			}
		}
	}
	if (infofont.size)
	{
		DWORD i = 0;
		DWORD size = infofont.size;
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
}

void Item::Init()
{
	Release();
	mi.init(ITEMMAX);
	infofont.init(ITEMINFOFONTMAX);
	int tidx = SpriteItemManager::GetIndexByName(SI_ITEM_POWER);
	for(int i=0;i<ITEMTYPEMAX;i++)
	{
		spItem[i] = SpriteItemManager::CreateSprite(tidx+i);
	}
	tidx = SpriteItemManager::GetIndexByName(SI_ITEM_POWER_OUT);
	for(int i=0;i<ITEMTYPEMAX;i++)
	{
		spItem[i+ITEMTYPEMAX] = SpriteItemManager::CreateSprite(tidx+i);
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

void Item::Build(WORD type, float _x, float _y, bool _bDrained /* = false */, int _angle, float _speed)
{
	mi.push_back()->valueSet(type, _x, _y, _bDrained, _angle, _speed);
}

void Item::ChangeItemID(WORD oriID, WORD toID)
{
	DWORD nowindex = mi.index;
	DWORD i = 0;
	DWORD size = mi.size;
	for (mi.toBegin(); i<size; mi.toNext(), i++)
	{
		if (!mi.isValid())
		{
			continue;
		}
		if ((*mi).exist)
		{
			if ((*mi).ID == oriID)
			{
				(*mi).valueSet(toID, (*mi).x, (*mi).y);
			}
		}
	}
	mi.index = nowindex;
}

void Item::Release()
{
	for(int i=0;i<ITEMSPRITEMAX;i++)
	{
		if(spItem[i])
			SpriteItemManager::FreeSprite(&spItem[i]);
	}
	mi.clear();
	infofont.clear();
}

void Item::Render()
{
	if(y < 0)
	{
		spItem[ID + ITEMTYPEMAX]->SetColor((BYTE)((int)y + 0xff)<<24 | 0xffffff);
		spItem[ID + ITEMTYPEMAX]->Render(x, 24);
	}
	spItem[ID]->RenderEx(x, y, ARC(headangle));
}

void Item::drainAll()
{
	if (mi.size)
	{
		DWORD _index = mi.index;

		DWORD i = 0;
		DWORD size = mi.size;
		for (mi.toBegin(); i<size; mi.toNext(), i++)
		{
			if (!mi.isValid())
			{
				continue;
			}
			Item * _i = &(*mi);
			if (_i->exist)
			{
				_i->bDrained = true;
			}
		}
		mi.index = _index;
	}
}

void Item::undrainAll()
{
	if (mi.size)
	{
		DWORD _index = mi.index;

		DWORD i = 0;
		DWORD size = mi.size;
		for (mi.toBegin(); i<size; mi.toNext(), i++)
		{
			if (!mi.isValid())
			{
				continue;
			}
			Item * _i = &(*mi);
			if (_i->exist && _i->bDrained)
			{
				_i->bDrained = false;
				_i->bFast = true;
				_i->speed = _ITEM_RETHROWSPEED;
				_i->angle = 9000;
			}
		}
		mi.index = _index;
	}
}

void Item::action()
{
	if(!bDrained && !(Player::p[0].flag & PLAYER_COLLAPSE || Player::p[0].flag & PLAYER_SHOT))
	{
		float rdrain = (Player::p[0].bSlow) ? 64 : 48;
		if (checkCollisionSquare(Player::p[0], rdrain))
		{
			bDrained = true;
			bFast = false;
		}
		if(Player::p[0].y < _ITEM_DRAINY || Player::p[0].fPoprate >= 1.0f)
		{
			bDrained = true;
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
			float dist = DIST(x, y, Player::p[0].x, Player::p[0].y);
			x += speed * (Player::p[0].x - x) / dist;
			y += speed * (Player::p[0].y - y) / dist;
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
		headangle += SIGN((int)mi.index) * 600 * speed;
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

	if (checkCollisionSquare(Player::p[0], _ITEM_GETR)
		&& !(Player::p[0].flag & PLAYER_COLLAPSE)
		&& !((ID == ITEM_SMALLFAITH || ID == ITEM_FAITH) && timer <= _ITEM_DRAINDELAY))
	{
		DWORD score;

		if(ID != ITEM_BOMB && ID != ITEM_EXTEND)
			SE::push(SE_ITEM_GET, x);
		else
			SE::push(SE_ITEM_EXTEND, x);

		score = Player::p[0].getItemBonus(ID);

		exist = false;
		Player::p[0].nScore += score;

		struct infoFont info;
		itoa(score, info.cScore, 10);

		info.timer = 0;
		info.x = x;
		info.y = y;
		if(ID == ITEM_POINT && (Player::p[0].fPoprate) >= 1.0f)
			info.yellow = true;
		else
			info.yellow = false;
		infofont.push_back(info);
	}
	if(y > M_DELETECLIENT_BOTTOM)
		exist = false;
}