#include "Player.h"
#include "PlayerBullet.h"
#include "SE.h"
#include "Enemy.h"
#include "Chat.h"
#include "Process.h"
#include "BResource.h"
#include "SpriteItemManager.h"

#define _PLAYER_ANIMATIONSPEED	8

void Player::Init()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		p[i].ClearNC();
		p[i].exist = false;
		p[i].ID = i;
		p[i].nowID = i;
		p[i].ID_sub_1 = 0xffff;
		p[i].ID_sub_2 = 0xffff;
	}
	SetAble(false);
}

void Player::RenderAll(BYTE renderflag)
{
	int _playerindex = Export::GetPlayerIndexByRenderFlag(renderflag);
	if (p[_playerindex].exist)
	{
		p[_playerindex].Render();
		p[_playerindex].RenderEffect();
	}
}

void Player::SetInitLife(BYTE _initlife)
{
	initlife = _initlife;
}

void Player::SetAble(bool setable)
{
	able = setable;
}

bool Player::CheckAble()
{
	return able;
}

bool Player::HavePlayer(WORD _ID)
{
	if (_ID == ID || _ID == ID_sub_1 || _ID == ID_sub_2)
	{
		return true;
	}
	return false;
}

void Player::initFrameIndex()
{
	WORD _ID;
	for (int i=0; i<M_PL_ONESETPLAYER; i++)
	{
		if (i == 1)
		{
			_ID = ID_sub_1;
		}
		else if (i == 2)
		{
			_ID = ID_sub_2;
		}
		else
		{
			_ID = ID;
		}
		if (_ID > PLAYERTYPEMAX)
		{
			continue;
		}
		playerData * pdata = &(res.playerdata[_ID]);
		int tfi = 0;
		frameindex[i][PLAYER_FRAME_STAND] = tfi;

		bool bhr = pdata->rightPreFrame;
		bool bhl = pdata->leftPreFrame;

		tfi += pdata->standFrame;
		frameindex[i][PLAYER_FRAME_LEFTPRE] = tfi;
		if (bhr)
		{
			tfi += pdata->rightPreFrame;
		}
		else
		{
			tfi += pdata->leftPreFrame;
		}
		frameindex[i][PLAYER_FRAME_LEFT] = tfi;

		if (bhr)
		{
			tfi += pdata->rightFrame;
		}
		else
		{
			tfi += pdata->leftFrame;
		}
		if (!bhr || !bhl)
		{
			tfi -= pdata->leftPreFrame + pdata->rightPreFrame + pdata->leftFrame + pdata->rightFrame;
		}
		frameindex[i][PLAYER_FRAME_RIGHTPRE] = tfi;
		if (bhr)
		{
			tfi += pdata->rightPreFrame;
		}
		else
		{
			tfi += pdata->leftPreFrame;
		}
		frameindex[i][PLAYER_FRAME_RIGHT] = tfi;
		if (bhr)
		{
			tfi += pdata->rightFrame;
		}
		else
		{
			tfi += pdata->leftFrame;
		}
	}
}

BYTE Player::getFrameIndex(BYTE frameenum)
{
	flipx = false;
	playerData * pdata = &(res.playerdata[nowID]);
	if ((frameenum == PLAYER_FRAME_RIGHTPRE || frameenum == PLAYER_FRAME_RIGHT) && (!pdata->rightPreFrame) ||
		(frameenum == PLAYER_FRAME_LEFTPRE || frameenum == PLAYER_FRAME_LEFT) && (!pdata->leftPreFrame))
	{
		flipx = true;
	}
	int tindex = 0;
	if (nowID == ID_sub_1)
	{
		tindex = 1;
	}
	else if (nowID == ID_sub_2)
	{
		tindex = 2;
	}
	return frameindex[tindex][frameenum];
}

void Player::setFrame(BYTE frameenum)
{
	frameoffset = 0;
	setIndexFrame(getFrameIndex(frameenum));
	nowstate = frameenum;
}

void Player::setIndexFrame(BYTE index)
{
	playerData * pdata = &(res.playerdata[nowID]);
	SpriteItemManager::ChangeSprite(res.playerdata[nowID].siid+index, sprite);
	sprite->SetFlip(flipx, false);
}


void Player::updateFrame(BYTE frameenum, int usetimer /* = -1*/)
{
	if (usetimer == -1)
	{
		usetimer = timer;
	}
	if (frameenum != nowstate && (frameenum == PLAYER_FRAME_STAND || frameenum+1 != nowstate))
	{
		setFrame(frameenum);
		return;
	}
	if ((usetimer % _PLAYER_ANIMATIONSPEED))
	{
		return;
	}
	playerData * pdata = &(res.playerdata[nowID]);
	frameoffset++;
	BYTE tbyte;
	switch (nowstate)
	{
	case PLAYER_FRAME_STAND:
		if (frameoffset >= pdata->standFrame)
		{
			setFrame(PLAYER_FRAME_STAND);
		}
		else
		{
			setIndexFrame(getFrameIndex(PLAYER_FRAME_STAND) + frameoffset);
		}
		break;
	case PLAYER_FRAME_LEFTPRE:
		if (!pdata->leftPreFrame)
		{
			tbyte = pdata->rightPreFrame;
		}
		else
		{
			tbyte = pdata->leftPreFrame;
		}
		if (frameoffset >= tbyte)
		{
			setFrame(PLAYER_FRAME_LEFT);
		}
		else
		{
			setIndexFrame(getFrameIndex(PLAYER_FRAME_LEFTPRE) + frameoffset);
		}
		break;
	case PLAYER_FRAME_LEFT:
		if (!pdata->leftFrame)
		{
			tbyte = pdata->rightFrame;
		}
		else
		{
			tbyte = pdata->leftFrame;
		}
		if (frameoffset >= tbyte)
		{
			setFrame(PLAYER_FRAME_LEFT);
		}
		else
		{
			setIndexFrame(getFrameIndex(PLAYER_FRAME_LEFT) + frameoffset);
		}
		break;
	case PLAYER_FRAME_RIGHTPRE:
		if (!pdata->rightPreFrame)
		{
			tbyte = pdata->leftPreFrame;
		}
		else
		{
			tbyte = pdata->rightPreFrame;
		}
		if (frameoffset >= tbyte)
		{
			setFrame(PLAYER_FRAME_RIGHT);
		}
		else
		{
			setIndexFrame(getFrameIndex(PLAYER_FRAME_RIGHTPRE) + frameoffset);
		}
		break;
	case PLAYER_FRAME_RIGHT:
		if (!pdata->rightFrame)
		{
			tbyte = pdata->leftFrame;
		}
		else
		{
			tbyte = pdata->rightFrame;
		}
		if (frameoffset >= tbyte)
		{
			setFrame(PLAYER_FRAME_RIGHT);
		}
		else
		{
			setIndexFrame(getFrameIndex(PLAYER_FRAME_RIGHT) + frameoffset);
		}
		break;
	}
}

void Player::UpdatePlayerData()
{
	playerData * pdata = &(res.playerdata[nowID]);
	r = pdata->collision_r;
	speed = pdata->fastspeed;
	slowspeed = pdata->slowspeed;
	shotdelay = pdata->shotdelay;
	chargespeed = pdata->chargespeed;
	rechargedelay = pdata->rechargedelay;
	fExSendParaB = pdata->exsendparab;
	fExSendParaA = pdata->exsendparaa;
}


void Player::AddLostStack()
{
	float lost = (hge->Timer_GetDelta() - 1/60.0f) * 100 * 60.0f;
	if(lost < 0)
		lost = 0;
	if(lost > 100)
		lost = 100;
	lostStack += lost;
}

void Player::SetInfi(BYTE reasonflag, int _infitimer/* =PLAYER_INFIMAX */)
{
	infireasonflag |= reasonflag;
	if (_infitimer == PLAYER_INFIMAX)
	{
		infitimer = PLAYER_INFIMAX;
	}
	else if (_infitimer == PLAYER_INFIUNSET)
	{
		infitimer = 0;
	}

	if (infitimer == PLAYER_INFIMAX || infitimer >= _infitimer)
	{
		return;
	}
	infitimer = _infitimer;
}


void Player::SetChara(WORD id, WORD id_sub_1/* =0xffff */, WORD id_sub_2/* =0xffff */)
{
	ID = id;
	nowID = ID;
	ID_sub_1 = id_sub_1;
	ID_sub_2 = id_sub_2;
}
