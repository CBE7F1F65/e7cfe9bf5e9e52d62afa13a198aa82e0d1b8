#include "EventZone.h"
#include "ProcessDefine.h"
#include "SpriteItemManager.h"

list<EventZone> EventZone::ezone[M_PL_MATCHMAXPLAYER];

EventZone::EventZone()
{
	sprite = NULL;
}

EventZone::~EventZone()
{
	if (sprite)
	{
		SpriteItemManager::FreeSprite(&sprite);
	}
}

void EventZone::Clear()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		ezone[i].clear();
	}
}

void EventZone::Render()
{
	if (sprite && timer > 0)
	{
		sprite->RenderEx(x, y, ARC(timer*turnangle), r*2/width);
	}
}

void EventZone::RenderAll(BYTE playerindex)
{
	for (list<EventZone>::iterator it=ezone[playerindex].begin(); it!=ezone[playerindex].end(); it++)
	{
		it->Render();
	}
}

void EventZone::Build(DWORD _type, BYTE _playerindex, float _x, float _y, int _maxtime, float _r/* =EVENTZONE_OVERZONE */, float _power/* =0 */, DWORD _eventID/* =EVENTZONE_EVENT_NULL */, float _rspeed/* =0 */, int inittimer/* =0 */, int _siid/* =-1 */, int _turnangle/* =0 */)
{
	EventZone _ezone;
	ezone[_playerindex].push_back(_ezone);
	EventZone * _pezone = &(*(ezone[_playerindex].rbegin()));
	_pezone->playerindex = _playerindex;
	_pezone->type = _type;
	_pezone->x = _x;
	_pezone->y = _y;
	_pezone->timer = inittimer;
	_pezone->maxtime = _maxtime;
	_pezone->r = _r;
	_pezone->power = _power;
	_pezone->eventID = _eventID;
	_pezone->rspeed = _rspeed;
	if (_siid >= 0)
	{
		_pezone->sprite = SpriteItemManager::CreateSprite(_siid);
		_pezone->width = SpriteItemManager::GetTexW(_siid);
	}
	_pezone->turnangle = _turnangle;
}

void EventZone::Action(DWORD stopflag)
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		bool binstop = FRAME_STOPFLAGCHECK_PLAYERINDEX_(stopflag, i, FRAME_STOPFLAG_EVENTZONE);
		if (!binstop)
		{
			for (list<EventZone>::iterator it=ezone[i].begin(); it!=ezone[i].end();)
			{
				if (it->action())
				{
					it = ezone[i].erase(it);
				}
				else
				{
					++it;
				}
			}
		}
	}
}

bool EventZone::action()
{
	timer++;
	r += rspeed;
	if (sprite && timer*5 > maxtime*4)
	{
		BYTE alpha = INTER(0, 0xff, (maxtime-timer)*5.0f/(maxtime));
		sprite->SetColor((alpha<<24)+0xffffff);
	}
	if (timer >= maxtime)
	{
		return true;
	}
	return false;
}
