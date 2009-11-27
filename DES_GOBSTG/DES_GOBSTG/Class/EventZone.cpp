#include "EventZone.h"

list<EventZone> EventZone::ezone[M_PL_MATCHMAXPLAYER];

EventZone::EventZone()
{

}

EventZone::~EventZone()
{

}

void EventZone::Clear()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		ezone[i].clear();
	}
}

void EventZone::Build(DWORD _type, BYTE _playerindex, float _x, float _y, int _maxtime, float _r/* =EVENTZONE_OVERZONE */, float _power/* =0 */, DWORD _eventID/* =EVENTZONE_EVENT_NULL */, float _rspeed/* =0 */)
{
	EventZone _ezone;
	ezone[_playerindex].push_back(_ezone);
	EventZone * _pezone = &(*(ezone[_playerindex].rbegin()));
	_pezone->type = _type;
	_pezone->x = _x;
	_pezone->y = _y;
	_pezone->timer = 0;
	_pezone->maxtime = _maxtime;
	_pezone->r = _r;
	_pezone->power = _power;
	_pezone->eventID = _eventID;
	_pezone->rspeed = _rspeed;
}

void EventZone::Action()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		for (list<EventZone>::iterator it=ezone[i].begin(); it!=ezone[i].end(); it++)
		{
			if (it->action())
			{
				it = ezone[i].erase(it);
			}
		}
	}
}

bool EventZone::action()
{
	timer++;
	r += rspeed;
	if (timer >= maxtime)
	{
		return true;
	}
	return false;
}
