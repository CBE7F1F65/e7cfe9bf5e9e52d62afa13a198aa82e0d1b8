#include "Selector.h"
#include "SE.h"
#include "Main.h"
#include "Process.h"
#include "SpriteItemManager.h"

Selector::Selector()
{
	sprite = NULL;
	flag	= SEL_NONE;
	sub = false;
}

Selector::~Selector()
{
	fsinfo.SignOff();
}

void Selector::Complete()
{
	fsinfo.SignOff();
}

void Selector::valueSet(BYTE _ID, int siID, float cenx, float ceny, char * info, float _hscale, float _vscale, BYTE _flag /* = SEL_NULL */)
{
	ID		=	_ID;
	x		=	cenx;
	y		=	ceny;
	hscale	=	_hscale;
	vscale	=	_vscale;

	timer	=	0;
	flag	=	SEL_NONE;
	sub		=	false;

	if (info && strlen(info))
	{
		fsinfo.SignUp(info);
	}

	if(sprite)
	{
		SpriteItemManager::FreeSprite(sprite);
		sprite = NULL;
	}
	if (siID >= 0)
	{
		sprite = SpriteItemManager::CreateSprite(siID);
	}

	alpha = 0xff;

	for(int i=0;i<SEL_STATEMAX;i++)
	{
		adj[i].xadj = x;
		adj[i].yadj = y;
	}
}

int Selector::getAdjIndex(BYTE setflag)
{
	int i = SELINFO_NONE;
	switch (setflag)
	{
	case SEL_OVER:
		i = SELINFO_OVER;
		break;
	case SEL_ENTER:
		i = SELINFO_ENTER;
		break;
	case SEL_LEAVE:
		i = SELINFO_LEAVE;
		break;
	}
	return i;
}

void Selector::setAdj(int i, float xadj, float yadj)
{
	adj[i].xadj = xadj;
	adj[i].yadj = yadj;
}

void Selector::actionSet(BYTE setflag, float xadj, float yadj)
{
	setAdj(getAdjIndex(setflag), xadj, yadj);
}

void Selector::actionSet(BYTE setflag, seladj * adj)
{
	if (!adj)
	{
		return;
	}
	int i=getAdjIndex(setflag);
	setAdj(i, adj[i].xadj, adj[i].yadj);
}

void Selector::Render()
{
	if (sprite)
	{
		sprite->RenderEx(x, y, 0, hscale, vscale);
	}
	fsinfo.Render(x, y, 0xFFFFFFFF, 0xFFFFFFFF);
}

void Selector::ChangeState(BYTE state, BYTE op)
{
	BYTE _tflag = flag;
	switch (op)
	{
	case SELOP_EQUAL:
		flag = state;
		break;
	case SELOP_SET:
		flag |= state;
		break;
	case SELOP_UNSET:
		flag &= ~state;
		break;
	}
	if (flag != _tflag)
	{
		timer = 0;
	}
}

bool Selector::checkSub()
{
	if((flag & SEL_GRAY) && !(flag & SEL_NONACTIVE))
	{
		sub = true;
		return true;
	}
	return false;
}

bool Selector::checkFVState()
{
	if (!(flag>>1) && !checkSub())
	{
		return true;
	}
	return false;
}

void Selector::PreAction(int nselect, int select, int * fvID, Selector ** fvselector)
{
	if (checkSub())
	{
		flag &= ~SEL_GRAY;
	}

	if(!((flag & SEL_INFOMASK)>>1) && ID < nselect)
	{
		if(ID == select)
		{
			ChangeState(SEL_OVER, SELOP_SET);
		}
		else
		{
			ChangeState(SEL_OVER, SELOP_UNSET);
		}
	}

	if(!(flag>>1) && !sub && *fvID < 0)
	{
		*fvID = ID;
	}

	if (ID == *fvID && !(*fvselector) && checkFVState())
	{
		*fvselector = this;
	}
}

bool Selector::PostAction(int * select, int sellock, int nPageNum, float fadebegin, float offset, int shiftangle)
{
	bool ret = false;
	int tindex = SELINFO_NONE;
	switch (flag & SEL_INFOMASK)
	{
	case SEL_OVER:
		tindex = SELINFO_OVER;
		break;
	case SEL_ENTER:
		tindex = SELINFO_ENTER;
		break;
	case SEL_LEAVE:
		tindex = SELINFO_LEAVE;
		break;
	}
	if (timer < maxtime)
	{
		x += (adj[tindex].xadj - x) / (maxtime-timer);
		y += (adj[tindex].yadj - y) / (maxtime-timer);
		switch (tindex)
		{
		case SELINFO_NONE:
			alpha = 0x30 * (maxtime-timer) / maxtime + 0xcf;
			break;
		case SELINFO_OVER:
			alpha = 0x10 * timer / maxtime + 0xef;
			break;
		case SELINFO_ENTER:
			alpha = 0xff;
			break;
		case SELINFO_LEAVE:
			alpha = 0x80 * (maxtime - timer) / maxtime;
			break;
		}
		timer++;
	}
	else
	{
		x = adj[tindex].xadj;
		y = adj[tindex].yadj;
		switch (tindex)
		{
		case SELINFO_NONE:
			alpha = ROLL(time, 0x3f) + 0x80;
			break;
		case SELINFO_OVER:
			alpha = ROLL(time, 0x3f) / 0x10 + 0xf0;
			break;
		case SELINFO_ENTER:
			alpha = 0xff;
			break;
		case SELINFO_LEAVE:
			alpha = 0;
			break;
		}
	}

	if(flag & SEL_ENTER)
	{
		*select = sellock;
		if(flag & ~SEL_ENTER)
		{
			timer = maxtime;
			ChangeState(SEL_ENTER, SELOP_EQUAL);
		}
		if(timer == maxtime)
		{
			Complete();
			ret = true;
		}
	}
	if(flag & SEL_LEAVE)
	{
		if(flag & ~SEL_LEAVE)
		{
			timer = 0;
			ChangeState(SEL_LEAVE, SELOP_EQUAL);
			alpha = 0x80;
		}
	}
	
	if(flag & SEL_NONACTIVE)
	{
		if(flag & SEL_GRAY)
			alpha = 0x40;
		else
			alpha = 0xff;
	}

	//
	BYTE fademode = 0;
	if (nPageNum && !(flag & SEL_STAY))
	{
		float fadeend = fadebegin + (nPageNum+2) * offset;
		float fadeoffbegin = fadebegin + offset / 2;
		float fadeoffend = fadeend - offset / 2;
		while (shiftangle > 18000)
		{
			shiftangle -= 18000;
		}
		while (shiftangle <= 0)
		{
			shiftangle += 18000;
		}
		if (shiftangle > 4500 && shiftangle <= 13500)
		{
			if (y < fadebegin || y > fadeend)
			{
				alpha = 0;
			}
			else if (y <= fadeoffbegin)
			{
				fademode = SELFADE_UP;
			}
			else if (y >= fadeoffend)
			{
				fademode = SELFADE_DOWN;
			}
		}
		else
		{
			if (x < fadebegin || x > fadeend)
			{
				alpha = 0;
			}
			else if (x <= fadeoffbegin)
			{
				fademode = SELFADE_LEFT;
			}
			else if (x >= fadeoffend)
			{
				fademode = SELFADE_RIGHT;
			}
		}
	}

	sprite->SetColor((alpha << 24) | (0xffffff));

	if (fademode)
	{
		switch (fademode)
		{
		case SELFADE_UP:
			sprite->SetColor(0, 0);
			sprite->SetColor(0, 1);
			break;
		case SELFADE_DOWN:
			sprite->SetColor(0, 2);
			sprite->SetColor(0, 3);
			break;
		case SELFADE_LEFT:
			sprite->SetColor(0, 0);
			sprite->SetColor(0, 3);
			break;
		case SELFADE_RIGHT:
			sprite->SetColor(0, 1);
			sprite->SetColor(0, 2);
			break;
		}
	}

	if(sub)
	{
		flag |= SEL_GRAY;
		sub = false;
	}

	return ret;
}

void Selector::SetMaxtime(int _maxtime)
{
	maxtime = _maxtime;
}