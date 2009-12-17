#include "Bullet.h"
#include "Player.h"
#include "SE.h"
#include "Item.h"
#include "BossInfo.h"
#include "Scripter.h"
#include "Main.h"
#include "BResource.h"
#include "Target.h"
#include "Export.h"
#include "EventZone.h"
#include "EffectSp.h"
#include "SpriteItemManager.h"
#include "ProcessDefine.h"

RenderDepth Bullet::renderDepth[M_PL_MATCHMAXPLAYER][BULLETTYPEMAX];

int Bullet::_actionList[M_PL_MATCHMAXPLAYER][BULLETACTIONMAX];
hgeSprite * Bullet::sprite[BULLETTYPECOLORMAX];

VectorList<Bullet> Bullet::bu[M_PL_MATCHMAXPLAYER];
HTEXTURE Bullet::tex;

WORD Bullet::index;

Bullet::Bullet()
{
	able	= false;
}

Bullet::~Bullet()
{
}

void Bullet::Init(HTEXTURE _tex)
{
	Release();

	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		ZeroMemory(renderDepth[i], sizeof(RenderDepth) * BULLETTYPEMAX);
		bu[i].init(BULLETMAX);
	}
	tex = _tex;
	for (int i=0; i<BULLETTYPEMAX; i++)
	{
		bulletData * tbd = &BResource::res.bulletdata[i];
		int tnum = tbd->nRoll;
		if (tnum < 2)
		{
			tnum = BResource::res.bulletdata[i].nColor;
		}
		int j=0;
		int index;
		for (j=0; j<tnum; j++)
		{
			index = i*BULLETCOLORMAX+j;
			sprite[index] = SpriteItemManager::CreateSprite(tbd->siid+j);
			sprite[index]->SetBlendMode(tbd->blendtype);
			if (BResource::res.bulletdata[i].collisiontype != BULLET_COLLISION_ELLIPSE && tbd->collisionSub)
			{
				sprite[index]->SetHotSpot(SpriteItemManager::GetTexW(tbd->siid+j)/2.0f, SpriteItemManager::GetTexH(tbd->siid+j)/2.0f+tbd->collisionSub);
			}
		}
		for (; j<BULLETCOLORMAX; j++)
		{
			index = i*BULLETCOLORMAX+j;
			sprite[index] = new hgeSprite(tex, 0, 0, 0, 0);
		}
	}

	index = 0;
}

void Bullet::BuildCircle(BYTE playerindex, int num, int baseangle, float baser, float x, float y, float speed, BYTE type, BYTE color, int fadeinTime, float avoid)
{
	if (num <= 0)
	{
		return;
	}
	int anglestep = 36000 / num;
	for (int i=0; i<num; i++)
	{
		int tnowangle = baseangle + i * anglestep;
		float tx = x + cost(tnowangle) * baser;
		float ty = y + sint(tnowangle) * baser;
		Build(playerindex, tx, ty, true, tnowangle, speed, type, color, fadeinTime, avoid, 0xff);
	}
}

void Bullet::BuildLine(BYTE playerindex, int num, int baseangle, float space, int baseindex, float x, float y, int angle, float anglefactor, float speed, float speedfactor, BYTE type, BYTE color, int fadeinTime, float avoid)
{
	if (num <= 0)
	{
		return;
	}
	for (int i=0; i<num; i++)
	{
		int tindex = i - baseindex;
		float tx = x + tindex * cost(baseangle) * space;
		float ty = y + tindex * sint(baseangle) * space;
		Build(playerindex, tx, ty, true, angle + anglefactor * tindex, speed + speedfactor * abs(tindex), type, color, fadeinTime, avoid, 0xff);
	}
}

int Bullet::Build(BYTE playerindex, float x, float y, bool absolute, int angle, float speed, BYTE type, BYTE color, int fadeinTime, float avoid, BYTE tarID)
{
	if (bu[playerindex].getSize() == BULLETMAX)
	{
		return -1;
	}
	Bullet * _tbu = NULL;
	_tbu = bu[playerindex].push_back();
	int _index = bu[playerindex].getEndIndex();
	if (!_tbu->valueSet(playerindex, _index, x, y, absolute, angle, speed, type, color, fadeinTime, avoid, tarID))
	{
		bu[playerindex].pop(_index);
		return -1;
	}
	memcpy(_tbu->actionList, _actionList[playerindex], BULLETACTIONMAX*sizeof(int));
	return _index;
}

void Bullet::Release()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		bu[i].clear();
	}
	for(int i=0;i<BULLETTYPECOLORMAX;i++)
	{
		if(sprite[i])
			delete sprite[i];
		sprite[i] = NULL;
	}
}

void Bullet::ClearItem()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		bu[i].clear_item();
		ZeroMemory(_actionList[i], sizeof(int) * BULLETACTIONMAX);
	}
	index = 0;
}

void Bullet::Action(DWORD stopflag)
{
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		if (bu[j].getSize())
		{
			ZeroMemory(Bullet::renderDepth[j], sizeof(RenderDepth) * BULLETTYPEMAX);
			DWORD i = 0;
			DWORD size = bu[j].getSize();
			bool binstop = FRAME_STOPFLAGCHECK_PLAYERINDEX_(stopflag, j, FRAME_STOPFLAG_BULLET);
			for (bu[j].toBegin(); i<size; bu[j].toNext(), i++)
			{
				if (!bu[j].isValid())
				{
					continue;
				}
				if ((*bu[j]).exist)
				{
					if (!binstop)
					{
						(*bu[j]).action();
					}
					else
					{
						(*bu[j]).actionInStop();
					}
				}
				else
				{
					bu[j].pop();
				}
			}
		}
	}
}

void Bullet::RenderAll(BYTE playerindex)
{
	if (bu[playerindex].getSize())
	{
		for (int i=0; i<BULLETTYPEMAX; i++)
		{
			if (Bullet::renderDepth[playerindex][i].haveType)
			{
				for (bu[playerindex].toIndex(Bullet::renderDepth[playerindex][i].startIndex); bu[playerindex].getIndex() != Bullet::renderDepth[playerindex][i].endIndex; bu[playerindex].toNext())
				{
					if (bu[playerindex].isValid() && (*bu[playerindex]).getRenderDepth() == i)
					{
						(*bu[playerindex]).Render();
					}
				}
			}
		}
	}
}

void Bullet::Render()
{
	int i = type*BULLETCOLORMAX + color;
	if (sprite[i])
	{
		sprite[i]->SetColor(alpha<<24 | diffuse);
		sprite[i]->RenderEx(x, y, ARC(angle+headangle+BULLET_ANGLEOFFSET), hscale);
	}
}

BYTE Bullet::getRenderDepth()
{
	return BResource::res.bulletdata[type].renderdepth;
}

void Bullet::matchFadeInColorType()
{
	if( BResource::res.bulletdata[type].fadecolor < BULLETCOLORMAX)
	{
		color = BResource::res.bulletdata[type].fadecolor;
		type = BULLET_FADEINTYPE;
	}
	else if (BResource::res.bulletdata[type].fadecolor == BULLET_FADECOLOR_16)
	{
		type = BULLET_FADEINTYPE;
		if (color == 0)
		{
		}
		else if (color < 9)
		{
			color = (color+1)/2;
		}
		else
		{
			color = (color-9)/3+5;
		}
	}
	else if (BResource::res.bulletdata[type].fadecolor == BULLET_FADECOLOR_8)
	{
		type = BULLET_FADEINTYPE;
	}
}
void Bullet::matchFadeOutColorType()
{
	if (BResource::res.bulletdata[type].fadecolor < BULLETCOLORMAX)
	{
		color = BResource::res.bulletdata[type].fadecolor;
		type = BULLET_FADEOUTTYPE;
	}
	else if (BResource::res.bulletdata[type].fadecolor == BULLET_FADECOLOR_16)
	{
		type = BULLET_FADEOUTTYPE;
		if (color == 0)
		{
		}
		else if (color < 9)
		{
			color = (color+1)/2;
		}
		else
		{
			color = (color-9)/3+5;
		}
	}
	else if (BResource::res.bulletdata[type].fadecolor == BULLET_FADECOLOR_8)
	{
		type = BULLET_FADEOUTTYPE;
	}
}

bool Bullet::valueSet(BYTE _playerindex, WORD _ID, float _x, float _y, bool absolute, int _angle, float _speed, BYTE _type, BYTE _color, int _fadeinTime, float avoid, BYTE _tarID)
{
	playerindex	= _playerindex;
	ID			=	_ID;
	x			=	_x;
	y			=	_y;
	type		=	_type;
	if(avoid)
	{
		if(isInRect(avoid, Player::p[playerindex].x, Player::p[playerindex].y))
			return false;
	}
	if(absolute)
		angle	=	_angle;
	else
		angle	=	rMainAngle(Player::p[playerindex].x, Player::p[playerindex].y, _angle);
	speed		=	_speed;
	oldtype		=	type;
	color		=	_color;
	oldcolor	=	color;
	fadeinTime	=	_fadeinTime;

	for (int i=0; i<BULLET_EVENTMAX; i++)
	{
		eventID[i] = 0xff;
	}

	tarID	=	_tarID;

	sendtime = 0;
	sendsetID = 0;

	matchFadeInColorType();

	timer			=	0;
	typechangetimer	=	0;
	exist			=	true;
	grazed			=	false;
	fadeout			=	false;
	able			=	true;
	remain			=	false;
	actionList[0]	=	SECTIONEND;
	hscale			=	1.0f;
	headangle		=	0;
	alpha			=	0xff;
	cancelable		=	true;

	xplus = speed * cost(angle);
	yplus = speed * sint(angle);
	lastx = x;
	lasty = y;
	lastangle = angle;
	lastspeed = speed;

	return true;
}

void Bullet::DoIze()
{
	if (cancelable || BossInfo::bossinfo.flag>=BOSSINFO_COLLAPSE)
	{
		for (list<EventZone>::iterator it=EventZone::ezone[playerindex].begin(); it!=EventZone::ezone[playerindex].end(); it++)
		{
			if (it->timer < 0)
			{
				continue;
			}
			if ((it->type) & EVENTZONE_TYPEMASK_BULLET)
			{
				if (checkCollisionBigCircle(it->x, it->y, it->r))
				{
					if (it->type & EVENTZONE_TYPE_BULLETFADEOUT)
					{
						sendsetID = 0;
						fadeout = true;
						timer = 0;
					}
					if (it->type & EVENTZONE_TYPE_SENDBULLET)
					{
						if (!(it->type & EVENTZONE_TYPE_NOSEND))
						{
							if (sendsetID)
							{
								SE::push(SE_BULLET_ERASE, x);
								fadeout = true;
								timer = 0;
							}
						}
					}
					if (it->type & EVENTZONE_TYPE_BULLETEVENT)
					{
						if (!passedEvent(it->eventID))
						{
							Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_BULLETENTERZONE, it->eventID);
							passEvent(it->eventID);
						}

					}
				}
			}
		}
	}
}

void Bullet::DoGraze()
{
	if(!grazed && BResource::res.bulletdata[type].collisiontype != BULLET_COLLISION_NONE)
	{
		if((Player::p[playerindex].x - x) * (Player::p[playerindex].x - x) + (Player::p[playerindex].y - y) * (Player::p[playerindex].y - y) < PLAYER_GRAZE_R * PLAYER_GRAZE_R)
		{
			Player::p[playerindex].DoGraze(x, y);
			grazed = true;
		}
	}
}

void Bullet::DoCollision()
{
	if(isInRect(Player::p[playerindex].r, Player::p[playerindex].x, Player::p[playerindex].y))
	{
		if (cancelable)
		{
			sendsetID = 0;
			fadeout = true;
			timer = 0;
		}
		Player::p[playerindex].DoShot();
	}
}

void Bullet::DoUpdateRenderDepth()
{
	if (exist)
	{
		BYTE rdtype = getRenderDepth();
		if (!renderDepth[playerindex][rdtype].haveType)
		{
			renderDepth[playerindex][rdtype].haveType = true;
			renderDepth[playerindex][rdtype].startIndex = index;
		}
		renderDepth[playerindex][rdtype].endIndex = index + 1;
		if (renderDepth[playerindex][rdtype].endIndex >= BULLETMAX)
		{
			renderDepth[playerindex][rdtype].endIndex = 0;
		}
	}
}

bool Bullet::HaveGray()
{
	if (!(BResource::res.bulletdata[type].nColor % 8))
	{
		return true;
	}
	return false;
}

void Bullet::actionInStop()
{
	index = ID;
	if (!fadeout)
	{
		DoIze();
		if (timer > fadeinTime)
		{
			DoGraze();
		}
	}
	able = exist && !fadeout;
	DoUpdateRenderDepth();
}

bool Bullet::passedEvent(BYTE _eventID)
{
	for (int i=0; i<BULLET_EVENTMAX; i++)
	{
		if (eventID[i] == _eventID)
		{
			return true;
		}
		else if (eventID[i] == 0xff)
		{
			return false;
		}
	}
	return false;
}

void Bullet::passEvent(BYTE _eventID)
{
	for (int i=0; i<BULLET_EVENTMAX; i++)
	{
		if (eventID[i] == 0xff)
		{
			eventID[i] = _eventID;
			return;
		}
	}
	eventID[0] = _eventID;
}

void Bullet::SendBullet(BYTE playerindex, float x, float y, BYTE setID, BYTE * sendtime, float * speed)
{
	int siidindex = EFFSPSEND_COLOR_RED;
	if (playerindex)
	{
		siidindex = EFFSPSEND_COLOR_BLUE;
	}
	float _hscale = randtf(0.6f, 0.8f);
	int esindex = EffectSp::Build(setID, playerindex, EffectSp::senditemsiid[siidindex][0], x, y, 0, _hscale);
	if (esindex >= 0)
	{
		EffectSp * _peffsp = &(EffectSp::effsp[playerindex][esindex]);
		_peffsp->colorSet(0x80ffffff, BLEND_ALPHAADD);
		float aimx;
		float aimy;
		aimx = randtf(M_GAMESQUARE_LEFT_(playerindex) + 8, M_GAMESQUARE_RIGHT_(playerindex) - 8);
		aimy = randtf(M_GAMESQUARE_TOP, M_GAMESQUARE_TOP + 128);
		_peffsp->chaseSet(EFFSP_CHASE_FREE, aimx, aimy, randt(45, 60));
		_peffsp->animationSet(EFFSPSEND_ANIMATIONMAX);
		if (sendtime && speed)
		{
			_peffsp->AppendData(*sendtime, *speed);
		}
		else
		{
			_peffsp->AppendData(-1, -1);
		}
	}
}

void Bullet::AddSendInfo(BYTE _sendsetID, BYTE _sendtime)
{
	sendtime = _sendtime;
	sendsetID = _sendsetID;
}

void Bullet::action()
{
	index = ID;
	if(angle != lastangle || lastspeed == 0)
	{
		xplus = speed * cost(angle);
		yplus = speed * sint(angle);
	}
	else if(speed != lastspeed)
	{
		xplus *= speed / lastspeed;
		yplus *= speed / lastspeed;
	}
	lastangle = angle;
	lastspeed = speed;
	
	timer++;

	lastx = x;
	lasty = y;


	if(!fadeout)
	{
		if(timer == 1 && fadeinTime > 1)
		{
			if(oldtype != type)
			{
				hscale *= (fadeinTime + 15.0f) * 0.0625f;
			}
			else
			{
				hscale /= fadeinTime;
			}
		}
		else if(timer < (DWORD)fadeinTime)
		{
			if(oldtype != type)
			{
				hscale -= 0.0625f;
				alpha = 0x80;
			}
			else
			{
				hscale += 1.0f / fadeinTime;
			}
		}
		else if(timer == fadeinTime)
		{
			if(oldtype != type)
			{
				hscale -= 0.0625f;
			}
			else
			{
				hscale += 1.0f / fadeinTime;
			}
			type = oldtype;
			color = oldcolor;
			alpha = 0xff;
			SE::push(BResource::res.bulletdata[type].seID, x);
		}
		else
		{
			x += xplus;
			y += yplus;

			if (able)
			{
				ChangeAction();

				if (BResource::res.bulletdata[type].nRoll && !(timer % BULLET_ANIMATIONSPEED))
				{
					color++;
					if (color >= BResource::res.bulletdata[type].nRoll)
					{
						color = 0;
					}
				}

				if(typechangetimer)
				{
					if(typechangetimer == 1)
					{
						hscale *= (BULLET_TYPECHANGETIME + 15.0f) * 0.0625f;
						matchFadeInColorType();
					}
					if(typechangetimer < BULLET_TYPECHANGETIME)
					{
						typechangetimer++;
						hscale -= 0.0625f;
						alpha = 0x80;
					}
					else
					{
						hscale -= 0.0625f;
						type = oldtype;
						color = oldcolor;
						typechangetimer = 0;
						alpha = 0xff;
					}
				}

				DoCollision();
				DoGraze();
			}
		}

		DoIze();
		headangle += SIGN(color) * BResource::res.bulletdata[type].nTurnAngle;
		if(tarID != 0xff)
		{
			Target::SetValue(tarID, x, y);
		}

		if(!remain)
		{
			if(x > M_DELETECLIENT_RIGHT_(playerindex) || x < M_DELETECLIENT_LEFT_(playerindex) || y > M_DELETECLIENT_BOTTOM || y < M_DELETECLIENT_TOP)
				exist = false;
		}
	}
	else
	{
		if(timer == 16)
		{
			if (sendsetID)
			{
				if (sendtime > 2)
				{
					sendtime = 2;
					if (hge->Random_Int(0, 4) == 0)
					{
						sendsetID += 2;
					}
				}
				SendBullet(1-playerindex, x, y, sendsetID, &sendtime, &speed);
			}
		}
		else if(timer == 32)
		{
			exist = false;
		}
		else if(timer == 96)
			exist = false;
		else if(timer < 32)
		{
			diffuse = 0xffffff;
			matchFadeOutColorType();
			hscale = timer / 60.0f + 0.6f;
			alpha = (BYTE)(32-timer) * 4 - 1;
		}
		else if(timer > 32 && timer < 96)
		{
			if(timer > 64)
				alpha = (BYTE)(96-timer) * 8 - 1;
			y -= 0.2f;
		}
	}
	able = exist && !fadeout;

	DoUpdateRenderDepth();
}

bool Bullet::isInRect(float r, float aimx, float aimy)
{
	bulletData * tbd = &(BResource::res.bulletdata[type]);
	switch (tbd->collisiontype)
	{
	case BULLET_COLLISION_NONE:
		return false;
		break;
	case BULLET_COLLISION_CIRCLE: 
		return checkCollisionCircle(aimx, aimy, tbd->collisionMain + r);
		break;
	case BULLET_COLLISION_ELLIPSE: 
		float rotCos;
		float rotSin;
		if (!speed)
		{
			rotCos = xplus / speed;
			rotSin = yplus / speed;
		}
		else
		{
			rotCos = cost(angle);
			rotSin = sint(angle);
		}
		return checkCollisionEllipse(aimx, aimy, tbd->collisionSub, tbd->collisionMain, rotCos, rotSin, r);
		break;
	case BULLET_COLLISION_SQURE: 
		return checkCollisionSquare(aimx, aimy, tbd->collisionMain);
		break;
	}
	return false;
}

void Bullet::ChangeAction()
{
	bool doit = false;
	for(int i=0;i<BULLETACTIONMAX;++i)
	{
		if (actionList[i] < BULA_SPECIALSTART)
		{
			switch (actionList[i])
			{
			case AND:
				if(!doit)
					for(++i;i<BULLETACTIONMAX;++i)
						if(actionList[i] == THEN)
							break;
				doit = false;
				break;
			case OR:
				if(doit)
				{
					for(++i;i<BULLETACTIONMAX;++i)
						if(actionList[i] == THEN)
							break;
				}
				else
					doit = false;
				break;
			case NOT:
				doit = !doit;
				break;
//			case ANDSET:
//				doit = true;
//				break;
			}
		}
		else if (actionList[i] < BULA_EXECUTESTART)
		{
			switch (actionList[i] & BULAC_FILTER)
			{
			case BULAC_OTHER:
				switch (actionList[i])
				{
				case SECTIONEND:
					i = BULLETACTIONMAX-1;
					break;

				case EVERY:
					doit = true;
					break;
				case EVERYMOD:
					if(timer % (DWORD)actionList[i+1] == 0)
						doit = true;
					++i;
					break;
				}
				break;
			case BULAC_TIMER:
				switch (actionList[i])
				{
				case TIMERGREAT:
					if(timer >= (DWORD)actionList[i+1])
						doit = true;
					++i;
					break;
				case TIMEREQUAL:
					if(timer == (DWORD)actionList[i+1])
						doit = true;
					++i;
					break;
				case TIMERLESS:
					if(timer <= (DWORD)actionList[i+1])
						doit = true;
					++i;
					break;
				case TIMERRANGE:
					if(timer >= (DWORD)actionList[i+1] && timer <= (DWORD)actionList[i+2])
						doit = true;
					i+=2;
					break;
				}
				break;
			case BULAC_TYPE:
				switch (actionList[i])
				{
				case TYPEEQUAL:
					if(type == actionList[i+1])
						doit = true;
					++i;
					break;
				}
				break;
			case BULAC_COLOR:
				switch (actionList[i])
				{
				case COLOREQUAL:
					if(color == actionList[i+1])
						doit = true;
					++i;
					break;
				}
				break;
			case BULAC_ANGLE:
				switch (actionList[i])
				{
				case ANGLEGREAT:
					if(angle >= actionList[i+1])
						doit = true;
					++i;
					break;
				case ANGLEEQUAL:
					if(angle == actionList[i+1])
						doit = true;
					++i;
					break;
				case ANGLELESS:
					if(angle <= actionList[i+1])
						doit = true;
					++i;
					break;
				case ANGLERANGE:
					if(angle >= actionList[i+1] && angle <= actionList[i+2])
						doit = true;
					i+=2;
					break;
				}
				break;
			case BULAC_POS:
				switch (actionList[i])
				{
				case XGREAT:
					if(x >= actionList[i+1])
						doit = true;
					++i;
					break;
				case XLESS:
					if(x <= actionList[i+1])
						doit = true;
					++i;
					break;
				case XRANGE:
					if(x >= actionList[i+1] && x <= actionList[i+2])
						doit = true;
					i+=2;
					break;
				case YGREAT:
					if(y >= actionList[i+1])
						doit = true;
					++i;
					break;
				case YLESS:
					if(y <= actionList[i+1])
						doit = true;
					++i;
					break;
				case YRANGE:
					if(y >= actionList[i+1] && y <= actionList[i+2])
						doit = true;
					i+=2;
					break;
				}
				break;
			case BULAC_VAL:
				switch (actionList[i])
				{
				case VALGREAT:
					if(CAST(Scripter::scr.d[actionList[i+1]]) >= actionList[i+2])
						doit = true;
					i+=2;
					break;
				case VALEQUAL:
					if(CAST(Scripter::scr.d[actionList[i+1]]) == actionList[i+2])
						doit = true;
					i+=2;
					break;
				case VALLESS:
					if(CAST(Scripter::scr.d[actionList[i+1]]) <= actionList[i+2])
						doit = true;
					i+=2;
					break;
				case VALRANGE:
					if(CAST(Scripter::scr.d[actionList[i+1]]) >= actionList[i+2] && CAST(Scripter::scr.d[actionList[i+1]]) <= actionList[i+3])
						doit = true;
					i+=3;
					break;
				}
				break;
			case BULAC_SPEED:
				switch (actionList[i])
				{
				case SPEEDGREAT:
					if(speed*BULLETACT_FLOATSCALE >= actionList[i+1])
						doit = true;
					++i;
					break;
				case SPEEDEQUAL:
					if(speed*BULLETACT_FLOATSCALE == actionList[i+1])
						doit = true;
					++i;
					break;
				case SPEEDLESS:
					if(speed*BULLETACT_FLOATSCALE <= actionList[i+1])
						doit = true;
					++i;
					break;
				case SPEEDRANGE:
					if(speed*BULLETACT_FLOATSCALE >= actionList[i+1] && speed*BULLETACT_FLOATSCALE <= actionList[i+2])
						doit = true;
					i+=2;
					break;
				}
				break;
			case BULAC_INDEX:
				switch (actionList[i])
				{
				case INDEXMODGREAT:
					if (index % actionList[i+1] >= actionList[i+2])
					{
						doit = true;
					}
					i+=2;
					break;
				case INDEXMODEQUAL:
					if (index % actionList[i+1] == actionList[i+2])
					{
						doit = true;
					}
					i+=2;
					break;
				case INDEXMODLESS:
					if (index % actionList[i+1] <= actionList[i+2])
					{
						doit = true;
					}
					i+=2;
					break;
				case INDEXMODRANGE:
					if (index % actionList[i+1] >= actionList[i+2] && index % actionList[i+1] <= actionList[i+3])
					{
						doit = true;
					}
					i+=3;
					break;
				}
				break;
			}
		}
		else
		{
			switch (actionList[i] & BULAE_FILTER)
			{
			case BULAE_TYPE:
				switch (actionList[i])
				{
				case TYPESET:
					if(doit)
					{
						oldtype = actionList[i+1];
						typechangetimer = 1;
						SE::push(SE_BULLET_CHANGE_2, x);
					}
					++i;
					doit = false;
					break;
				}
				break;
			case BULAE_COLOR:
				switch (actionList[i])
				{
				case COLORSET:
					if(doit)
					{
						color = actionList[i+1];
						oldcolor = color;
						SE::push(SE_BULLET_CHANGE_2, x);
					}
					++i;
					doit = false;
					break;
				}
				break;
			case BULAE_ANGLE:
				switch (actionList[i])
				{
				case ANGLESET:
					if(doit)
					{
						angle = actionList[i+1];
						SE::push(SE_BULLET_CHANGE_1, x);
					}
					++i;
					doit = false;
					break;
				case ANGLESETADD:
					if(doit)
					{
						angle += actionList[i+1];
						if(actionList[i+1] > BULLETACT_ANGLECHANGESE || actionList[i+1] < -BULLETACT_ANGLECHANGESE)
							SE::push(SE_BULLET_CHANGE_1, x);
					}
					++i;
					doit = false;
					break;
				case ANGLESETRMA:
					if(doit)
					{
						angle = rMainAngle(actionList[i+1]*1.0f, actionList[i+2]*1.0f, actionList[i+3]*1.0f);
						SE::push(SE_BULLET_CHANGE_1, x);
					}
					i+=3;
					doit = false;
					break;
				case ANGLESETRMAP:
					if(doit)
					{
						angle = rMainAngle(Player::p[playerindex].x, Player::p[playerindex].y, actionList[i+1]*1.0f);
						SE::push(SE_BULLET_CHANGE_1, x);
					}
					++i;
					doit = false;
					break;
				case ANGLESETRMAT:
					if(doit)
					{
						angle = rMainAngle(Target::tar[actionList[i+1]].x, Target::tar[actionList[i+1]].y, actionList[i+2]*1.0f);
						SE::push(SE_BULLET_CHANGE_1, x);
					}
					i+=2;
					doit = false;
					break;
				case ANGLESETAMA:
					if(doit)
					{
						angle = aMainAngle(actionList[i+1]*1.0f, actionList[i+2]*1.0f, actionList[i+3]);
						SE::push(SE_BULLET_CHANGE_1, x);
					}
					i+=3;
					doit = false;
					break;
				case ANGLESETAMAP:
					if(doit)
					{
						angle = aMainAngle(Player::p[playerindex].x, Player::p[playerindex].y, actionList[i+1]);
						SE::push(SE_BULLET_CHANGE_1, x);
					}
					++i;
					doit = false;
					break;
				case ANGLESETAMAT:
					if(doit)
					{
						angle = aMainAngle(Target::tar[actionList[i+1]].x, Target::tar[actionList[i+1]].y, actionList[i+2]);
						SE::push(SE_BULLET_CHANGE_1, x);
					}
					i+=2;
					doit = false;
					break;
				case ANGLEADJUST:
					if(doit)
						angle = aMainAngle(lastx, lasty) + 18000;
					doit = false;
					break;
				}
				break;
			case BULAE_HEADANGLE:
				switch (actionList[i])
				{
				case HEADANGLESET:
					if(doit)
						headangle = actionList[i+1];
					++i;
					doit = false;
					break;
				case HEADANGLESETADD:
					if(doit)
						headangle += actionList[i+1];
					++i;
					doit = false;
					break;
				}
				break;
			case BULAE_POS:
				switch (actionList[i])
				{
				case XSET:
					if(doit)
					{
						x = (float)actionList[i+1];
						SE::push(SE_BULLET_CHANGE_2, x);
					}
					++i;
					doit = false;
					break;
				case YSET:
					if(doit)
					{
						y = (float)actionList[i+1];
						SE::push(SE_BULLET_CHANGE_2, x);
					}
					++i;
					doit = false;
					break;
				case XSETADD:
					if(doit)
						x += actionList[i+1]/BULLETACT_FLOATSCALE;
					++i;
					doit = false;
					break;
				case YSETADD:
					if(doit)
						y += actionList[i+1]/BULLETACT_FLOATSCALE;
					++i;
					doit = false;
					break;
				case XSETACCADD:
					if(doit && timer > (DWORD)actionList[i+1])
						x += (int)(timer - actionList[i+1]) * actionList[i+2]/BULLETACT_FLOATSCALE;
					i+=2;
					doit = false;
					break;
				case YSETACCADD:
					if(doit && timer > (DWORD)actionList[i+1])
						y += (int)(timer - actionList[i+1]) * actionList[i+2]/BULLETACT_FLOATSCALE;
					i+=2;
					doit = false;
					break;
				}
				break;
			case BULAE_SPEED:
				switch (actionList[i])
				{
				case SPEEDSET:
					if(doit)
					{
						if (speed == 0)
						{
							SE::push(SE_BULLET_CHANGE_1, x);
						}
						speed = actionList[i+1]/BULLETACT_FLOATSCALE;
					}
					++i;
					doit = false;
					break;
				case SPEEDSETADD:
					if(doit)
					{
						if(speed == 0)
							SE::push(SE_BULLET_CHANGE_2, x);
						speed += actionList[i+1]/BULLETACT_FLOATSCALE;
					}
					++i;
					doit = false;
					break;
				}
				break;
			case BULAE_VAL:
				switch (actionList[i])
				{
				case VALSET:
					if(doit)
					{
						Scripter::scr.SetIntValue(actionList[i+1], actionList[i+2]);
						Scripter::scr.d[actionList[i+1]].bfloat = false;
					}
					i+=2;
					doit = false;
					break;
				case VALSETADD:
					if(doit)
					{
						Scripter::scr.SetIntValue(actionList[i+1], Scripter::scr.GetIntValue(actionList[i+1])+actionList[i+2]);
						Scripter::scr.d[actionList[i+1]].bfloat = false;
					}
					i+=2;
					doit = false;
					break;
				}
				break;
			case BULAE_OTHER:
				switch (actionList[i])
				{
				case CALLEVENT:
					if (doit)
					{
						Scripter::scr.Execute(SCR_EVENT, actionList[i+1], actionList[i+2]);
					}
					i+=2;
					doit = false;
					break;
				case CHASE:
					if (doit)
					{
						actionList[i+2]--;
						chaseAim(Target::tar[actionList[i+1]].x, Target::tar[actionList[i+1]].y, actionList[i+2]);
					}
					i+=2;
					doit = false;
					break;

				case REMAIN:
					if(doit)
						remain = true;
					break;
				case FADEOUT:
					if(doit)
					{
						sendsetID = 0;
						fadeout = true;
						timer = 0;
					}
					break;
				case BOUNCE:
					if (doit)
					{
						if (actionList[i+2])
						{
							if (x < M_GAMESQUARE_LEFT_(playerindex) + actionList[i+1] || x > M_GAMESQUARE_RIGHT_(playerindex) - actionList[i+1])
							{
								actionList[i+2]--;
								SE::push(SE_BULLET_CHANGE_2, x);
								angle = 18000 - angle;
							}
							if (y < M_GAMESQUARE_TOP + actionList[i+1] || y > M_GAMESQUARE_BOTTOM - actionList[i+1])
							{
								actionList[i+2]--;
								SE::push(SE_BULLET_CHANGE_2, x);
								angle = -angle;
							}
						}
					}
					i+=2;
					doit = false;
					break;
				case BOUNCELR:
					if (doit)
					{
						if (actionList[i+2])
						{
							if (x < M_GAMESQUARE_LEFT_(playerindex) + actionList[i+1] || x > M_GAMESQUARE_RIGHT_(playerindex) - actionList[i+1])
							{
								actionList[i+2]--;
								SE::push(SE_BULLET_CHANGE_2, x);
								angle = 18000 - angle;
							}
						}
					}
					i+=2;
					doit = false;
					break;
				case BOUNCETB:
					if (doit)
					{
						if (actionList[i+2])
						{
							if (y < M_GAMESQUARE_TOP + actionList[i+1] || y > M_GAMESQUARE_BOTTOM - actionList[i+1])
							{
								actionList[i+2]--;
								SE::push(SE_BULLET_CHANGE_2, x);
								angle = -angle;
							}
						}
					}
					i+=2;
					doit = false;
					break;
				}
				break;
			}
		}
	}		
}
