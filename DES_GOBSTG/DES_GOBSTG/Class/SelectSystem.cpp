#include "SelectSystem.h"
#include "Main.h"
#include "Process.h"
#include "SpriteItemManager.h"
#include "PushKey.h"
#include "SE.h"

SelectSystem selsys[SELSYSTEMMAX];

SelectSystem::SelectSystem()
{
	select = 0;
	Clear();
}

SelectSystem::~SelectSystem()
{
	Clear();
}

void SelectSystem::Init()
{
	ClearAll();
}

void SelectSystem::ClearAll()
{
	for (int i=0; i<SELSYSTEMMAX; i++)
	{
		selsys[i].Clear();
	}
}

void SelectSystem::Clear()
{
	for(list<Selector>::iterator it=sel.begin();it!=sel.end();it++)
	{
		if(it->sprite)
			delete it->sprite;
		it->sprite = NULL;
		it->fsinfo.SignOff();
	}
	sel.clear();
	nselect = 0;
	nPageNum = 0;
	complete = false;
	confirminit = false;
	plus = true;
}

Selector * SelectSystem::BuildSelector(BYTE ID, int siID, float cenx, float ceny, char * info, float hscale, float vscale, BYTE flag /* = SEL_NULL */)
{
	Selector _selector;
	sel.push_back(_selector);
	Selector * _pselector = &(*(sel.rbegin()));
	_pselector->valueSet(ID, siID, cenx, ceny, info, hscale, vscale, flag);
	_pselector->actionSet(SEL_NONE, adj);
	_pselector->actionSet(SEL_OVER, adj);
	_pselector->actionSet(SEL_ENTER, adj);
	_pselector->actionSet(SEL_LEAVE, adj);
	return _pselector;
}

void SelectSystem::Setup(int _nselect, int _select, BYTE _keyminus, BYTE _keyplus, BYTE _keyok, BYTE _keycancel, BYTE _pushid, int maxtime/* =-1 */)
{
	nselect = _nselect;
	select = _select;
	keyplus = _keyplus;
	keyminus = _keyminus;
	keyok = _keyok;
	keycancel = _keycancel;
	pushid = _pushid;
	for (list<Selector>::iterator it=sel.begin(); it!=sel.end(); it++)
	{
		it->SetMaxtime(maxtime);
	}
	PushKey::SetPushEvent(pushid, keyplus, keyminus);
}

bool SelectSystem::SetPageNumber(BYTE _nPageNum, float _fadebegin, float _offset, int initshift/* =0 */, int _shiftangle/* =9000 */)
{
	if (nselect < _nPageNum)
	{
		return false;
	}
	nPageNum = _nPageNum;
	fadebegin = _fadebegin;
	offset = _offset;
	firstID = 0;
	lastID = nPageNum - 1;
	shiftangle = _shiftangle;
	shift(initshift);
	return true;
}

void SelectSystem::SetAction(BYTE typeflag, float xadj, float yadj)
{
	adj[typeflag].xadj = xadj;
	adj[typeflag].yadj = yadj;

	for (list<Selector>::iterator it=sel.begin(); it!=sel.end(); it++)
	{
		it->actionSet(typeflag, adj);
	}
}

void SelectSystem::shift(int nshift)
{
	if (!nshift)
	{
		return;
	}
	float moveoffset = offset * nshift;
	float xmoveoffset = moveoffset * cost(shiftangle);
	float ymoveoffset = moveoffset * sint(shiftangle);
	for (list<Selector>::iterator it=sel.begin(); it!=sel.end(); it++)
	{
		if ((it->flag & SEL_STAY) || (it->flag & SEL_NOSHIFT))
		{
			continue;
		}
		for (int i=0; i<SEL_STATEMAX; i++)
		{
			it->adj[i].xadj -= xmoveoffset;
			it->adj[i].yadj -= ymoveoffset;
		}
		it->timer = 0;
	}
	firstID += nshift;
	while (firstID >= nselect)
	{
		firstID -= nselect;
	}
	lastID = firstID + (nPageNum-1);
	if (lastID >= nselect)
	{
		lastID = nselect - 1;
		firstID = lastID - (nPageNum-1);
	}
}

void SelectSystem::matchSelect()
{
	for(list<Selector>::iterator it=sel.begin();it!=sel.end();it++)
	{
		if(it->ID == select && (it->flag & SEL_NONACTIVE))
		{
			list<Selector>::iterator jt = it;
			do
			{
				if(plus)
				{
					jt++;
					if(jt == sel.end())
						jt++;
				}
				else
				{
					jt--;
					if(jt == sel.end())
						jt--;
				}
				if(!((jt->flag & SEL_NONACTIVE) || (jt->flag & SEL_GRAY)))
				{
					select = jt->ID;
					break;
				}
			}while(jt!=it);
			break;
		}
	}
}

Selector * SelectSystem::GetPointer(int index)
{
	if (index < 0 || index >= sel.size())
	{
		return NULL;
	}
	int tindex = 0;
	for (list<Selector>::iterator it=sel.begin(); it!=sel.end(); it++)
	{
		if (index == tindex)
		{
			return &(*it);
		}
		tindex++;
	}
	return NULL;
}

void SelectSystem::action()
{
	int fvID = -1;
	Selector * fvselector = NULL;
	for(list<Selector>::iterator it=sel.begin();it!=sel.end();it++)
	{
		it->PreAction(nselect, select, &fvID, &fvselector);
	}

	if(fvselector != NULL)
	{
		PushKey::UpdatePushEvent(pushid);
		if(hge->Input_GetDIKey(keyplus, DIKEY_DOWN))
		{
			plus = true;
			SE::push(SE_SYSTEM_SELECT);
			select++;
			if(select == nselect)
				select = 0;
		}
		else if(hge->Input_GetDIKey(keyminus, DIKEY_DOWN))
		{
			plus = false;
			SE::push(SE_SYSTEM_SELECT);
			select--;
			if(select == -1)
				select = nselect - 1;
		}
		matchSelect();
		if (nPageNum)
		{
			if (select < firstID)
			{
				shift(select - firstID);
			}
			else if (select > lastID)
			{
				shift(select - lastID);
			}
		}
		if(hge->Input_GetDIKey(keyok, DIKEY_DOWN))
		{
			bool benter = false;
			for(list<Selector>::iterator it = sel.begin(); it != sel.end(); it++)
			{
				if(it->ID == select)
				{
					if(!((it->flag) & SEL_NONACTIVE))
					{
						sellock = select;
						benter = true;
						break;
					}
				}
			}
			if(benter)
			{
				SE::push(SE_SYSTEM_OK);
				for(list<Selector>::iterator it = sel.begin(); it != sel.end(); it++)
				{
					if(it->ID == select)
						it->ChangeState(SEL_ENTER, SELOP_SET);
					else
						it->ChangeState(SEL_LEAVE, SELOP_SET);
				}
			}
			else
			{
				SE::push(SE_SYSTEM_CANCEL);
			}
		}
	}

	for (list<Selector>::iterator it=sel.begin(); it!=sel.end(); it++)
	{
		it->PostAction(&select, sellock, nPageNum, fadebegin, offset, shiftangle);
	}
}

void SelectSystem::Render()
{
	for(list<Selector>::iterator it=sel.begin(); it!=sel.end(); it++)
	{
		it->Render();
	}
}

bool SelectSystem::Confirm(BYTE _keyminus, BYTE _keyplus, BYTE _keyok, BYTE _keycancel, BYTE _pushid, float cenx/* =M_ACTIVECLIENT_CENTER_X */, float ceny/* =M_ACTIVECLIENT_CENTER_Y */, bool settrue/* =false */)
{
	if(!confirminit)
	{
		Clear();
		SetAction(SEL_OVER, 0, -4);
		SetAction(SEL_ENTER, 0, 0);
		SetAction(SEL_LEAVE, 16, 4);

		BuildSelector(0, SpriteItemManager::yesIndex, cenx, ceny)->actionSet(SEL_NONE, -30, 45);
		BuildSelector(0, SpriteItemManager::noIndex, cenx, ceny)->actionSet(SEL_NONE, 30, 45);
		BuildSelector(0, SpriteItemManager::confirmIndex, cenx, ceny, NULL, 1, 0, SEL_NONACTIVE)->actionSet(SEL_NONE, 0, 0);

		Setup(2, settrue?0:1, _keyplus, _keyminus, _keyok, _keycancel, _pushid);
		confirminit = true;
	}

	if(hge->Input_GetDIKey(_keycancel, DIKEY_UP))
	{
		SE::push(SE_SYSTEM_CANCEL);
		confirminit = false;
	}
	if(complete)
	{
		confirminit = false;
		if(select == 0)
			return true;
	}
	return false;
}