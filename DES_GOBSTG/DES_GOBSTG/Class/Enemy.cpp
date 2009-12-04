#include "Enemy.h"
#include "Player.h"
#include "SE.h"
#include "Item.h"
#include "Scripter.h"
#include "Chat.h"
#include "BossInfo.h"
#include "Process.h"
#include "BResource.h"
#include "FrontDisplay.h"
#include "EffectIDDefine.h"
#include "EventZone.h"
#include "SpriteItemManager.h"

#define _DAMAGEZONEMAX	0x10

VectorList<Enemy> Enemy::en[M_PL_MATCHMAXPLAYER];

HTEXTURE * Enemy::tex = NULL;
BYTE Enemy::actionflag[ENEMY_BOSSMAX];
BYTE Enemy::spelluptimer[ENEMY_BOSSMAX];
BYTE Enemy::storetimer[ENEMY_BOSSMAX];

Enemy::Enemy()
{
	exist	= false;
	able	= false;
	ID		= 0;
	sprite = NULL;
}

Enemy::~Enemy()
{
	SpriteItemManager::FreeSprite(&sprite);
}

void Enemy::Init(HTEXTURE * _tex)
{
	Release();
	tex = _tex;
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		en[i].init(ENEMYMAX);
	}
}

void Enemy::Release()
{
}

int Enemy::Build(WORD eID, BYTE playerindex, float x, float y, int angle, float speed, BYTE type, float life, int infitimer)
{
	Enemy _en;
	DWORD _index = en[playerindex].index;
	int enindex = -1;
	Enemy * _pen = NULL;
	if (en[playerindex].size < ENEMYMAX)
	{
		_pen = en[playerindex].push_back(_en);
		enindex = en[playerindex].getEndIndex();
	}
	else
	{
		DWORD i = en[playerindex].index;
		DWORD size = en[playerindex].size;
		for (; i<size; en[playerindex].toNext(), i++)
		{
			if (!en[playerindex].isValid())
			{
				_pen = en[playerindex].push(_en);
				enindex = en[playerindex].index;
				break;
			}
		}
	}
	en[playerindex].index = _index;
	if (_pen)
	{
		_pen->valueSet(playerindex, eID, x, y, angle, speed, type, life, infitimer);
	}
	return enindex;
}

void Enemy::Clear()
{
	exist = false;
	able = false;
	timer = 0;
}

void Enemy::ClearAll()
{
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		for (int i=0; i<en[j].capacity; i++)
		{
			en[j][i].Clear();
		}
		en[j].clear_item();
	}
}

void Enemy::Action(bool notinstop)
{
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		DWORD i = 0;
		DWORD size = en[j].size;
		for (en[j].toBegin(); i<size; en[j].toNext(), i++)
		{
			if (en[j].isValid())
			{
				if ((*en[j]).exist)
				{
					if (notinstop)
					{
						(*en[j]).action();
					}
					else
					{
						(*en[j]).actionInStop();
					}
				}
				else
				{
					en[j].pop();
				}
			}
		}
	}
}

void Enemy::SendGhost(BYTE playerindex, float x, float y, BYTE setID, BYTE * sendtime, float * acceladd)
{
	int siidindex = EFFSPSEND_COLOR_RED;
	if (playerindex)
	{
		siidindex = EFFSPSEND_COLOR_BLUE;
	}
	float _hscale = hge->Random_Float(1.2f, 1.4f);
	int esindex = EffectSp::Build(setID, playerindex, EffectSp::senditemsiid[siidindex][0], x, y, 0, _hscale);
	if (esindex >= 0)
	{
		EffectSp * _peffsp = &(EffectSp::effsp[esindex]);
		_peffsp->colorSet(0x80ffffff, BLEND_ALPHAADD);
		float aimx;
		float aimy;
		aimx = hge->Random_Float(M_GAMESQUARE_LEFT_(playerindex) + 8, M_GAMESQUARE_RIGHT_(playerindex) - 8);
		aimy = hge->Random_Float(M_GAMESQUARE_TOP, M_GAMESQUARE_TOP + 128);
		_peffsp->chaseSet(EFFSP_CHASE_FREE, aimx, aimy, hge->Random_Int(45, 60));
		_peffsp->animationSet(EFFSPSEND_ANIMATIONMAX);
		if (sendtime)
		{
			_peffsp->AppendData(*sendtime, *acceladd);
		}
		else
		{
			_peffsp->AppendData(0, 0);
		}
	}
}

void Enemy::RenderAll(BYTE renderflag)
{
	BYTE _playerindex = Export::GetPlayerIndexByRenderFlag(renderflag);
	DWORD i = 0;
	DWORD size = en[_playerindex].size;
	for (en[_playerindex].toBegin(); i<size; en[_playerindex].toNext(), i++)
	{
		if (en[_playerindex].isValid())
		{
			if ((*en[_playerindex]).exist)
			{
				(*en[_playerindex]).Render();
				(*en[_playerindex]).RenderEffect();
			}
		}
	}
}
void Enemy::Render()
{
	if (sprite)
	{
		sprite->SetColor(alpha<<24|diffuse);
		sprite->RenderEx(x, y, ARC(headangle), hscale, vscale);
	}
}

void Enemy::RenderEffect()
{
	if(fadeout && timer)
	{
		effCollapse.Render();
	}
	effShot.Render();
}

void Enemy::setTar(BYTE _tarID)
{
	tarID = _tarID;
}

void Enemy::setTake(DWORD _take)
{
	take = _take;
}

void Enemy::valueSet(BYTE _playerindex, WORD _eID, float _x, float _y, int _angle, float _speed, BYTE _type, float _life, int _infitimer)
{
	playerindex	=	_playerindex;
	ID		=	_eID;
	x		=	_x;
	lastx	=	x;
	y		=	_y;
	speed	=	_speed;
	type	=	_type;
	life	=	_life;
	ac		=	ENAC_NONE;
	angle	=	_angle;
	take	=	0;
	infitimer = _infitimer;

	timer	=	0;
	damagetimer = 0;
	maxlife	=	life;
	damagerate	=	1;
	exist	=	true;
	fadeout	=	false;
	able	=	true;
	damage	=	false;
	hscale	=	1.0f;
	vscale	=	1.0f;
	alpha	=	0xff;
	diffuse	=	0xffffff;
	faceindex = res.enemydata[type].faceIndex;

	if (!res.enemydata[type].rightPreFrame && !res.enemydata[type].leftPreFrame)
	{
		bturnhead = true;
		headangle = angle;
	}
	else
	{
		bturnhead = false;
		headangle	=	0;
	}

	accel		=	0;
	acceladd	=	0;

	sendtime	=	0;
	sendsetID	=	0;

	actionflag[ID]		=	0;
	spelluptimer[ID]	=	0;
	storetimer[ID]		=	0;

	ID		=	0;
	tarID	=	0xff;

	aim.x	=	0;
	aim.y	=	0;

	for (int i=0; i<ENEMY_PARAMAX; i++)
	{
		para[i] = 0;
	}

	if (sprite)
	{
		SpriteItemManager::ChangeSprite(res.enemydata[type].siid, sprite);
	}
	else
	{
		sprite = SpriteItemManager::CreateSprite(res.enemydata[type].siid);
	}

	initFrameIndex();
	setFrame(ENEMY_FRAME_STAND);
	activetimer = 0;
	activemaxtime = 0;

	// TODO:
	effShot.valueSet(EFF_EN_SHOT, M_RENDER_LEFT, *this);
	effShot.Stop();
}

void Enemy::matchAction()
{
	switch(ac)
	{
	case ENAC_NONE:
		break;
	case ENAC_DIRECTSET_XYAS:
		//x，y，angle，speed
		//直接设置（需要连续设置）
		x = para[0];
		y = para[1];
		angle = para[2];
		speed = para[3]/1000.0f;
		break;
	case ENAC_CHASEPLAYER_TFR:
		//作用时间，摩擦力，退出角度
		//靠近主角
		if(timer < para[0])
		{
			angle = aMainAngle(Player::p[playerindex]);
			speed *= para[1]/1000.0f;
		}
		else
		{
			angle = (int)para[2];
		}
		break;
	case ENAC_ATTENUATION_TFER:
		//作用时间，摩擦力，停止时间，退出角度
		//向原方向前进、停止、撤离
		if(timer < para[0])
		{
			speed *= para[1]/1000.0f;
		}
		else if(timer < para[2])
			speed = 0;
		else
		{
			angle = (int)para[3];
			speed += 0.03f;
		}
		break;
	case ENAC_CIRCLE_TXYE:
		//[+-]起始时间，环绕中心x，环绕中心y，终止时间
		//绕圆周行走
		if(para[0] > 0)
		{
			if(timer > (DWORD)para[0] && timer < (DWORD)para[3])
			{
				float tr = DIST(x, y, para[1], para[2]);
				angle += ANGLE(speed / tr);
			}
		}
		else
		{
			if(timer > (DWORD)(-para[0]) && timer < (DWORD)para[3])
			{
				float tr = DIST(x, y, para[1], para[2]);
				angle -= ANGLE(speed / tr);
			}
		}
		break;
	case ENAC_BROKENLINE_CATE:
		//作用时间[计数器]，变角范围，更替周期，终止时间
		//折线行走
		if((int)para[0] && timer < para[3])
		{
			speed = speed * ((int)para[0] - 1) / (int)para[0];
			para[0] -= 0.8f;
			para[0] = (int)para[0];
		}
		else if(timer < para[3])
		{
			para[0] = para[2];
			speed = para[2] / 30;
			if(para[1] > 0)
			{
				angle = para[1];
				para[1] = 18000 - para[1];
			}
			else
			{
				angle = 18000 + para[1];
				para[1] = -18000 - para[1];
			}
		}
		else
		{
			speed += 0.03f;
			angle = -9000;
		}
		break;
	case ENAC_STOPANDSTRIKE_TEA:
		//作用时间，停止时间，放弃时间
		//减速至0，后冲向Player
		if(timer < para[0])
		{
			speed -= speed / (para[0] - timer);
		}
		else if(timer < para[1])
		{
			speed = 0;
		}
		else if(timer < para[2])
		{
			speed += 0.06f;
			angle = aMainAngle(Player::p[playerindex]);
		}
		break;

	case ENAC_REPOSITION_T:
		//作用时间[计数器]
		//BOSS出场复位
		if((int)para[0])
		{
			chaseAim(M_GAMESQUARE_BOSSX_(playerindex), M_GAMESQUARE_BOSSY, para[0]);
			para[0] -= 0.8f;
			para[0] = (int)para[0];
		}
		else
		{
			ac = 0;
			speed = 0;
		}
		break;
	case ENAC_OVERPLAYER_CXYT:
		//作用时间[计数器]，目标x，目标y，更替周期
		//在主角上方随机
		if((int)para[0])
		{
			chaseAim(para[1], para[2], para[0]);
			para[0] -= 0.8f;
			para[0] = (int)para[0];
		}
		else if(timer % (int)para[3] == 0)
		{
			para[0] = 2 * para[3] > 120 ? 120 : 2 * para[3];
			if(Player::p[playerindex].x > x)
				para[1] = Player::p[playerindex].x + randt() % 60;
			else
				para[1] = Player::p[playerindex].x - randt() % 60;
			float edgescale = 0.15f;
			float leftedge = M_GAMESQUARE_LEFT_(playerindex)+M_GAMESQUARE_WIDTH * edgescale;
			float rightedge = M_GAMESQUARE_RIGHT_(playerindex)-M_GAMESQUARE_WIDTH * edgescale;
			if(para[1] < M_GAMESQUARE_LEFT_(playerindex)+M_GAMESQUARE_WIDTH*0.15f)
			{
				if(x <= leftedge + 8)
					para[1] = leftedge + 8 + randt() % 50;
				else
					para[1] = leftedge;
			}
			else if(para[1] > rightedge)
			{
				if(x >= rightedge - 8)
					para[1] = rightedge - 8 - randt() % 50;
				else
					para[1] = rightedge;
			}
			para[2] = randt() % 80 + M_GAMESQUARE_BOSSY - 40;
		}
		break;
	case ENAC_CHASETO_CXY:
		//作用时间[计数器]，目标x，目标y
		//滑步走向点
		if((int)para[0])
		{
			chaseAim(para[1], para[2], para[0]);
			para[0] -= 0.8f;
			para[0] = (int)para[0];
		}
		else
			speed = 0;
		break;
	}
}

void Enemy::setAction(WORD _ac, float para0, float para1, float para2, float para3)
{
	para[0] = para0;
	para[1] = para1;
	para[2] = para2;
	para[3] = para3;
	ac = _ac;
}

void Enemy::updateFrame(BYTE frameenum, int usetimer /* = -1*/)
{
	if (usetimer == -1)
	{
		usetimer = timer;
	}
	if (frameenum != nowstate && (frameenum == ENEMY_FRAME_STAND || frameenum+1 != nowstate))
	{
		setFrame(frameenum);
		return;
	}
	if ((usetimer % ENEMY_ANIMATIONSPEED))
	{
		return;
	}
	enemyData * pdata = &(res.enemydata[type]);
	frameoffset++;
	BYTE tbyte;
	switch (nowstate)
	{
	case ENEMY_FRAME_STAND:
		if (frameoffset >= pdata->standFrame)
		{
			setFrame(ENEMY_FRAME_STAND);
		}
		else
		{
			setIndexFrame(getFrameIndex(ENEMY_FRAME_STAND) + frameoffset);
		}
		if (pdata->standshake)
		{
			float thsx;
			float thsy;
			sprite->GetHotSpot(&thsx, &thsy);
			sprite->SetHotSpot(thsx, sint(timer*512)*4.8f+thsy-2.4f);
		}
		break;
	case ENEMY_FRAME_RIGHTPRE:
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
			setFrame(ENEMY_FRAME_RIGHT);
		}
		else
		{
			setIndexFrame(getFrameIndex(ENEMY_FRAME_RIGHTPRE) + frameoffset);
		}
		break;
	case ENEMY_FRAME_RIGHT:
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
			setFrame(ENEMY_FRAME_RIGHT);
		}
		else
		{
			setIndexFrame(getFrameIndex(ENEMY_FRAME_RIGHT) + frameoffset);
		}
		break;
	case ENEMY_FRAME_LEFTPRE:
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
			setFrame(ENEMY_FRAME_LEFT);
		}
		else
		{
			setIndexFrame(getFrameIndex(ENEMY_FRAME_LEFTPRE) + frameoffset);
		}
		break;
	case ENEMY_FRAME_LEFT:
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
			setFrame(ENEMY_FRAME_LEFT);
		}
		else
		{
			setIndexFrame(getFrameIndex(ENEMY_FRAME_LEFT) + frameoffset);
		}
		break;
	case ENEMY_FRAME_ATTACKPRE:
		tbyte = pdata->attackPreFrame;
		if (frameoffset >= tbyte)
		{
			setFrame(ENEMY_FRAME_ATTACK);
		}
		else
		{
			setIndexFrame(getFrameIndex(ENEMY_FRAME_ATTACKPRE) + frameoffset);
		}
		break;
	case ENEMY_FRAME_ATTACK:
		tbyte = pdata->attackFrame;
		if (frameoffset >= tbyte)
		{
			setFrame(ENEMY_FRAME_ATTACK);
		}
		else
		{
			setIndexFrame(getFrameIndex(ENEMY_FRAME_ATTACK) + frameoffset);
		}
		break;
	case ENEMY_FRAME_STOREPRE:
		tbyte = pdata->storePreFrame;
		if (frameoffset >= tbyte)
		{
			setFrame(ENEMY_FRAME_STORE);
		}
		else
		{
			setIndexFrame(getFrameIndex(ENEMY_FRAME_STOREPRE) + frameoffset);
		}
		break;
	case ENEMY_FRAME_STORE:
		tbyte = pdata->storeFrame;
		if (frameoffset >= tbyte)
		{
			setFrame(ENEMY_FRAME_STORE);
		}
		else
		{
			setIndexFrame(getFrameIndex(ENEMY_FRAME_STORE) + frameoffset);
		}
		break;
	}
}

void Enemy::updateFrameAsMove()
{
	if (bturnhead)
	{
		updateFrame(ENEMY_FRAME_STAND);
	}
	else
	{
		if(lastx - x > ENEMY_BOSSMOVELIMIT)
		{
			updateFrame(ENEMY_FRAME_LEFTPRE);
		}
		else if(x - lastx > ENEMY_BOSSMOVELIMIT)
		{
			updateFrame(ENEMY_FRAME_RIGHTPRE);
		}
		else
		{
			updateFrame(ENEMY_FRAME_STAND);
		}
	}
}

void Enemy::updateAction()
{
	enemyData * pdata = &(res.enemydata[type]);
	if(!actionflag[ID])
	{
		updateFrameAsMove();
	}
	if(actionflag[ID] & ENEMYACTION_ATTACK)
	{
		if (!pdata->attackFrame)
		{
			updateFrameAsMove();
		}
		else
		{
			updateFrame(ENEMY_FRAME_ATTACKPRE);
		}
		actionflag[ID] &= ~ENEMYACTION_ATTACK;
	}
	if(actionflag[ID] & ENEMYACTION_STORE)
	{
		if (!pdata->storeFrame)
		{
			updateFrameAsMove();
		}
		else
		{
			updateFrame(ENEMY_FRAME_STOREPRE);
		}
		storetimer[ID]++;

		if(storetimer[ID] == 1)
		{
		}
		else if(storetimer[ID] == 120)
		{
			storetimer[ID] = 0;
			actionflag[ID] &= ~ENEMYACTION_STORE;
		}
	}
}

void Enemy::initFrameIndex()
{
	enemyData * pdata = &(res.enemydata[type]);
	int tfi = 0;
	frameindex[ENEMY_FRAME_STAND] = tfi;

	bool bhr = pdata->rightPreFrame;
	bool bhl = pdata->leftPreFrame;

	tfi += pdata->standFrame;
	frameindex[ENEMY_FRAME_RIGHTPRE] = tfi;
	if (bhr)
	{
		tfi += pdata->rightPreFrame;
	}
	else
	{
		tfi += pdata->leftPreFrame;
	}
	frameindex[ENEMY_FRAME_RIGHT] = tfi;
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
	frameindex[ENEMY_FRAME_LEFTPRE] = tfi;
	if (bhr)
	{
		tfi += pdata->rightPreFrame;
	}
	else
	{
		tfi += pdata->leftPreFrame;
	}
	frameindex[ENEMY_FRAME_LEFT] = tfi;

	if (bhr)
	{
		tfi += pdata->rightFrame;
	}
	else
	{
		tfi += pdata->leftFrame;
	}
	frameindex[ENEMY_FRAME_ATTACKPRE] = tfi;
	tfi += pdata->attackPreFrame;
	frameindex[ENEMY_FRAME_ATTACK] = tfi;
	tfi += pdata->attackFrame;
	frameindex[ENEMY_FRAME_STOREPRE] = tfi;
	tfi += pdata->storePreFrame;
	frameindex[ENEMY_FRAME_STORE] = tfi;
	tfi += pdata->storeFrame;
}

BYTE Enemy::getFrameIndex(BYTE frameenum)
{
	flipx = false;
	enemyData * pdata = &(res.enemydata[type]);
	if ((frameenum == ENEMY_FRAME_RIGHTPRE || frameenum == ENEMY_FRAME_RIGHT) && (!pdata->rightPreFrame) ||
		(frameenum == ENEMY_FRAME_LEFTPRE || frameenum == ENEMY_FRAME_LEFT) && (!pdata->leftPreFrame))
	{
		flipx = true;
	}
	return frameindex[frameenum];
}

void Enemy::setFrame(BYTE frameenum)
{
	frameoffset = 0;
	setIndexFrame(getFrameIndex(frameenum));
	nowstate = frameenum;
}

void Enemy::setIndexFrame(BYTE index)
{
	enemyData * pdata = &(res.enemydata[type]);
	SpriteItemManager::ChangeSprite(pdata->siid+index, sprite);
	sprite->SetFlip(flipx, false);
}

void Enemy::GetCollisionRect(float * w, float * h)
{
	*w = res.enemydata[type].collision_w;
	*h = res.enemydata[type].collision_h;
}

void Enemy::CostLife(float power)
{
	if (infitimer)
	{
		return;
	}
	life -= power * damagerate;
	damage = true;
}

bool Enemy::isInRange(float _x, float _y, float _r)
{
	float _tw;
	float _th;
	GetCollisionRect(&_tw, &_th);
	_tw /= 2;
	_th /= 2;
	if (checkCollisionBigCircle(_x - _tw, _y + _th, _r) ||
		checkCollisionBigCircle(_x + _tw, _y + _th, _r) ||
		checkCollisionBigCircle(_x - _tw, _y - _th, _r) ||
		checkCollisionBigCircle(_x + _tw, _y - _th, _r))
	{
		return true;
	}
	return false;
}

void Enemy::actionInStop()
{
	if (!fadeout)
	{
		DoShot();
	}
}

void Enemy::DoShot()
{
	float tw;
	float th;
	GetCollisionRect(&tw, &th);
	float costpower = PlayerBullet::CheckShoot(playerindex, x, y ,tw, th);
	if (costpower)
	{
		CostLife(costpower);
	}
	for (list<EventZone>::iterator it=EventZone::ezone[playerindex].begin(); it!=EventZone::ezone[playerindex].end(); it++)
	{
		if (it->type & EVENTZONE_TYPE_ENEMYDAMAGE)
		{
			if (isInRange(it->x, it->y, it->r))
			{
				CostLife(it->power);
				// TODO:
				Player::p[playerindex].DoPlayerBulletHit();
			}
		}
	}


	if(!damage && life < maxlife / 5 && timer%8<4)
	{
		SE::push(SE_ENEMY_DAMAGE_1, x);
	}

	if(damage && !damagetimer)
	{
		damagetimer++;
	}
	else if(damagetimer > 0)
	{
		if(damagetimer < 8)
			damagetimer++;
		else
			damagetimer = 0;
		if(damagetimer > 0 && damagetimer % 8 < 4)
		{
			alpha = 0x7f;
			diffuse = 0xb40000;
			effShot.Fire();

			if(life < maxlife / 5)
			{
				SE::push(SE_ENEMY_DAMAGE_2, x);
			}
			else
			{
				SE::push(SE_ENEMY_DAMAGE_1, x);
			}
		}
		else
		{
			alpha = 0xff;
			diffuse = 0xffffff;
			effShot.Stop();
		}
	}
	if(life < 0)
	{
		en[playerindex].pushIndex();
		scr.Execute(SCR_EDEF, ID, SCRIPT_CON_POST);
		en[playerindex].popIndex();

		if (life < 0)
		{
			SE::push(SE_ENEMY_DEAD, x);

			fadeout = true;
			timer = 0;
		}
	}

}

void Enemy::AddSendInfo(BYTE _sendsetID, BYTE _sendtime, float _accel, float _acceladd)
{
	sendsetID = _sendsetID;
	sendtime = _sendtime;
	accel = _accel;
	acceladd = _acceladd;
}

void Enemy::action()
{
	timer++;

	if (timer < 60)
	{
		if (accel)
		{
			speed += accel;
		}
	}

	if(infitimer)
	{
		infitimer--;
	}

	effShot.MoveTo(x, y);
	effShot.action();

	if(!fadeout)
	{
		if((Chat::chatitem.IsChatting() || (BossInfo::flag >= BOSSINFO_COLLAPSE)))
		{
			life = 0;
			fadeout = true;
			timer = 0;
		}

		if(ID && !Scripter::stopEdefScript)
		{
			en[playerindex].pushIndex();
			scr.Execute(SCR_EDEF, ID, timer);
			en[playerindex].popIndex();
		}
		matchAction();
		updateMove();
		updateAction();

		lastx = x;

		if(tarID != 0xff)
		{
			Target::SetValue(tarID, x, y);
		}

		float tw;
		float th;
		GetCollisionRect(&tw, &th);
		if (!Player::p[playerindex].bInfi)
		{
			if (checkCollisionSquare(Player::p[playerindex], tw, th))
			{
				Player::p[playerindex].DoShot();
			}
		}
		/*
		if(BossInfo::flag)
		{
			int txdiff = fabsf(Player::p[playerindex].x - x);
			if(txdiff < ENEMY_BOSSX_FADERANGE)
				FrontDisplay::fdisp.info.enemyx->SetColor(((0x40 + txdiff*2) << 24) | 0xffffff);
			else
				FrontDisplay::fdisp.info.enemyx->SetColor(0x80ffffff);
		}
		*/

		if (sendsetID && !activetimer && Player::p[playerindex].bDrain)
		{
			scr.Execute(SCR_EVENT, SCR_EVENT_PLAYERDRAINCHECK, playerindex);
		}

		if (activetimer)
		{
			activetimer++;
			if (activetimer >= activemaxtime)
			{
				scr.Execute(SCR_EVENT, SCR_EVENT_ACTIVEGHOSTOVER, playerindex);
				fadeout = true;
				timer = 0;
			}
		}

		if (bturnhead)
		{
			headangle = angle;
		}

		DoShot();
		if(x > M_DELETECLIENT_RIGHT_(playerindex) || x < M_DELETECLIENT_LEFT_(playerindex) || y > M_DELETECLIENT_BOTTOM || y < M_DELETECLIENT_TOP)
			exist = false;
	}
	else
	{
		if(timer == 1)
		{
			giveItem(playerindex);
			effShot.Stop();
			// TODO:
			effCollapse.valueSet(EFF_EN_COLLAPSE, M_RENDER_LEFT, *this);

			BYTE blastmaxtime;
			float blastr;
			float blastpower;
			GetBlastInfo(&blastmaxtime, &blastr, &blastpower);
			EventZone::Build(EVENTZONE_TYPE_SENDBULLET|EVENTZONE_TYPE_ENEMYGHOSTDAMAGE, playerindex, x, y, blastmaxtime, blastr, blastpower, EVENTZONE_EVENT_NULL);
			Player::p[playerindex].DoEnemyCollapse(x, y);

			if (sendsetID)
			{
				sendtime++;
				if (sendtime < 3)
				{
					SendGhost(playerindex, x, y, sendsetID, &sendtime, &acceladd);
				}
			}
		}
		else if(timer == 32)
		{
			effCollapse.Stop();
			exist = false;
		}
		effCollapse.action();

		if(type < ENEMY_BOSSTYPEBEGIN)
		{
			hscale	=	timer * 0.05f + 1.0f;
			vscale	=	(32 - timer) * 0.03225f;
			alpha	=	(BYTE)((32 - timer) * 8);
		}
	}

	damage = false;
	able = exist && !fadeout;
}

void Enemy::GetBlastInfo(BYTE * maxtime/* =NULL */, float * r/* =NULL */, float * power/* =NULL */)
{
	if (maxtime)
	{
		*maxtime = res.enemydata[type].blastmaxtime;
	}
	if (r)
	{
		*r = res.enemydata[type].blastr;
	}
	if (power)
	{
		*power = res.enemydata[type].blastpower;
	}
}

void Enemy::SetActiveInfo(BYTE _activemaxtime, WORD _eID, BYTE _type, int _angle, float _speed, float _damagerate)
{
	if (!exist || fadeout)
	{
		return;
	}
	activemaxtime = _activemaxtime;
	ID = _eID;
	type = _type;
	angle = _angle;
	speed = _speed;
	accel = 0;
	damagerate = _damagerate;
	setAction();
	updateAction();
	activetimer = 1;
}

void Enemy::giveItem(BYTE playerindex)
{
	bool first = true;
	float aimx;
	float aimy;

	float tempx = x;
	float tempy = y;

	y -= randt()%30;
	if(x > PL_MOVABLE_RIGHT_(playerindex))
		x = PL_MOVABLE_RIGHT_(playerindex);
	else if(x < PL_MOVABLE_LEFT_(playerindex))
		x = PL_MOVABLE_LEFT_(playerindex);

	for(int i=0;i<8;i++)
	{
		for(int j=0;j<(int)((take>>(i*4))&0xf);j++)
		{
			if(!first)
			{
				aimx = (float)((x + randt()%80 - 40));
				if(aimx > 417)
					aimx = 417;
				else if(aimx < 23)
					aimx = 23;
				aimy = (float)(randt()%80 - 240 + y);
				Item::Build(playerindex, i, x, y, false, 18000 + rMainAngle(aimx, aimy), -sqrt(2 * 0.1f * DIST(x, y, aimx, aimy)));
			}
			else
			{
				Item::Build(playerindex, i, x, y);
			}
			first = false;
		}
	}
	x = tempx;
	y = tempy;
}
