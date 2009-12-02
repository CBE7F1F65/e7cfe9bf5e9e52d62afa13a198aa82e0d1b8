#include "Player.h"

#include "Process.h"
#include "BGLayer.h"
#include "SE.h"

#include "PlayerBullet.h"
#include "Item.h"
#include "Ghost.h"
#include "Bullet.h"
#include "Chat.h"
#include "BossInfo.h"
#include "EffectIDDefine.h"
#include "SpriteItemManager.h"
#include "FrontDisplayName.h"
#include "FrontDisplay.h"
#include "EventZone.h"
#include "BResource.h"
#include "Scripter.h"

#define _GAMERANK_MIN	8
#define _GAMERANK_MAX	22
#define _GAMERANK_ADDINTERVAL	9000
#define _GAMERANK_STAGEOVERADD	-8

#define _PL_SHOOTCHARGEINFI_1	8
#define _PL_SHOOTCHARGEINFI_2	47
#define _PL_SHOOTCHARGEINFI_3	63
#define _PL_SHOOTCHARGEINFI_4	127

#define _PLAYER_DEFAULETCARDLEVEL_(X)	(X?9:8)
#define _PLAYER_DEFAULETBOSSLEVEL_(X)	(X?9:8)

#define _PLAYER_LIFECOSTMAX	2880
#define _PLAYER_COMBOHITMAX	999

#define _PLAYER_SHOOTPUSHOVER	9
#define _PLAYER_SHOOTNOTPUSHOVER	9

Player Player::p[M_PL_MATCHMAXPLAYER];
float Player::lostStack = 0;
bool Player::able = false;

BYTE Player::rank = _GAMERANK_MIN;
int Player::lilycount = 0;



Player::Player()
{
	effGraze.exist = false;
	effChange.exist = false;
	effInfi.exist = false;
	effCollapse.exist = false;
	effMerge.exist = false;
	effBorder.exist = false;
	effBorderOn.exist = false;
	effBorderOff.exist = false;
	sprite			= NULL;
	nowID			= 0;
	ID_sub_1		= 0;
	ID_sub_2		= 0;
	ClearNC();
}

Player::~Player()
{
	SpriteItemManager::FreeSprite(&sprite);
}

void Player::ClearNC()
{
}

void Player::ClearSet(BYTE round)
{
	x			=	PL_MERGEPOS_X_(playerindex);
	y			=	PL_MERGEPOS_Y;

	for(int i=0;i<PL_SAVELASTMAX;i++)
	{
		lastx[i] = x;
		lasty[i] = y;
		lastmx[i] = x;
		lastmy[i] = y;
	}
	timer		=	0;
	angle		=	0;
	flag		=	PLAYER_MERGE;
	bSlow		=	false;
	bCharge		=	false;
	bDrain		=	false;
	bInfi		=	true;
	hscale		=	1.0f;
	vscale		=	1.0f;
	alpha		=	0xff;

	mergetimer			=	0;
	shottimer			=	0;
	collapsetimer		=	0;
	shoottimer			=	0;
	draintimer			=	0;
	chargetimer			=	0;
	slowtimer			=	0;
	fasttimer			=	0;
	playerchangetimer	=	0;
	costlifetimer		=	0;

	fCharge = 0;
	if (round == 0)
	{
		fChargeMax = PLAYER_CHARGEONE;
	}
	cardlevel = _PLAYER_DEFAULETCARDLEVEL_(round);
	bosslevel = _PLAYER_DEFAULETBOSSLEVEL_(round);
	infitimer = 0;
	rechargedelaytimer = 0;
	infireasonflag = 0;

	shootpushtimer = 0;
	shootnotpushtimer = 0;

	speedfactor		=	1.0f;

	// add
	initlife	=	PLAYER_DEFAULTINITLIFE;

	exist = true;

	nComboHit = 0;
	nComboHitOri = 0;
	nComboGage = 0;

	if (effGraze.exist)
	{
		effGraze.Stop(true);
		effGraze.MoveTo(x, y, 0, true);
	}
	if (effChange.exist)
	{
		effChange.Stop(true);
		effChange.MoveTo(x, y, 0, true);
	}
	if (effInfi.exist)
	{
		effInfi.Stop(true);
		effInfi.MoveTo(x, y, 0, true);
	}
	if (effCollapse.exist)
	{
		effCollapse.Stop(true);
		effCollapse.MoveTo(x, y, 0, true);
	}
	if (effMerge.exist)
	{
		effMerge.Stop(true);
		effMerge.MoveTo(x, y, 0, true);
	}
	if (effBorder.exist)
	{
		effBorder.Stop(true);
		effBorder.MoveTo(x, y, 0, true);
	}
	if (effBorderOn.exist)
	{
		effBorderOn.Stop(true);
		effBorderOn.MoveTo(x, y, 0, true);
	}
	if (effBorderOff.exist)
	{
		effBorderOff.Stop(true);
		effBorderOff.MoveTo(x, y, 0, true);
	}

	changePlayerID(nowID, true);

	esChange.valueSet(EFFSPSET_PLAYERUSE, EFFSP_PLAYERCHANGE, SpriteItemManager::GetIndexByName(SI_PLAYER_SHOTITEM), x, y, 0, 3.0f);
	esChange.colorSet(0x7fffffff, BLEND_ALPHAADD);
	esChange.chaseSet(EFFSP_CHASE_PLAYER_(playerindex), 0, 0);

	esShot.valueSet(EFFSPSET_PLAYERUSE, EFFSP_PLAYERSHOT, SpriteItemManager::GetIndexByName(SI_PLAYER_SHOTITEM), x, y, 0, 1.2f);
	esShot.colorSet(0xccff0000);
	esShot.chaseSet(EFFSP_CHASE_PLAYER_(playerindex), 0, 0);

	esPoint.valueSet(EFFSPSET_PLAYERUSE, EFFSP_PLAYERPOINT, SpriteItemManager::GetIndexByName(SI_PLAYER_POINT), x, y);
	esPoint.chaseSet(EFFSP_CHASE_PLAYER_(playerindex), 0, 0);

	esCollapse.valueSet(EFFSPSET_PLAYERUSE, EFFSP_PLAYERCOLLAPSE, SpriteItemManager::GetIndexByName(SI_PLAYER_SHOTITEM), x, y);
	esCollapse.actionSet(0, 0, 160);
	esCollapse.colorSet(0x80ffffff);
}

//add


void Player::valueSet(BYTE _playerindex, BYTE round)
{
	playerindex = _playerindex;
	nowID		= ID;
	ClearSet(round);
	initFrameIndex();
	UpdatePlayerData();

	nLife		=	initlife;
	nLifeCost	=	0;

	nSpellPoint		=	0;

	if (round == 0)
	{
		lostStack		=	0;
	}

	if(!sprite)
	{
		sprite = SpriteItemManager::CreateSpriteByName(SI_NULL);
//		sprite = new hgeSprite(mp.tex[res.playerdata[ID].tex], 0, 0, 0, 0);
	}
	setFrame(PLAYER_FRAME_STAND);

	// TODO:
	effGraze.valueSet(EFF_PL_GRAZE, M_RENDER_LEFT, *this);
	effGraze.Stop();
	effChange.valueSet(EFF_PL_CHANGE, M_RENDER_LEFT, *this);
	effChange.Stop();
	effInfi.valueSet(EFF_PL_INFI, M_RENDER_LEFT, *this);
	effInfi.Stop();
	effCollapse.valueSet(EFF_PL_COLLAPSE, M_RENDER_LEFT, *this);
	effCollapse.Stop();
	effMerge.valueSet(EFF_PL_MERGE, M_RENDER_LEFT, *this);
	effMerge.Stop();
	effBorder.valueSet(EFF_PL_BORDER, M_RENDER_LEFT, *this);
	effBorder.Stop();
	effBorderOn.valueSet(EFF_PL_BORDERON, M_RENDER_LEFT, *this);
	effBorderOn.Stop();
	effBorderOff.valueSet(EFF_PL_BORDEROFF, M_RENDER_LEFT, *this);
	effBorderOff.Stop();

	SetAble(true);
}

void Player::Action(bool * notinstop)
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		if (p[i].exist && notinstop[i])
		{
			p[i].action();
		}
	}
	if (time % _GAMERANK_ADDINTERVAL == 0)
	{
		rank++;
		if (rank > _GAMERANK_MAX)
		{
			rank = _GAMERANK_MAX;
		}
	}
}

void Player::action()
{
	float nowspeed = 0;
	timer++;

	alpha = 0xff;
	if(timer == 1)
		flag |= PLAYER_MERGE;

	//savelast
	if(lastmx[0] != x || lastmy[0] != y)
	{
		for(int i=PL_SAVELASTMAX-1;i>0;i--)
		{
			lastmx[i] = lastmx[i-1];
			lastmy[i] = lastmy[i-1];
		}
		lastmx[0] = x;
		lastmy[0] = y;
	}
	for(int i=PL_SAVELASTMAX-1;i>0;i--)
	{
		lastx[i] = lastx[i-1];
		lasty[i] = lasty[i-1];
	}
	lastx[0] = x;
	lasty[0] = y;

	//flag
	if(flag & PLAYER_MERGE)
	{
		if(Merge())
		{
			flag &= ~PLAYER_MERGE;
		}
	}
	if(flag & PLAYER_SHOT)
	{
		if(Shot())
		{
			flag &= ~PLAYER_SHOT;
		}
	}
	if (flag & PLAYER_COSTLIFE)
	{
		if (CostLife())
		{
			flag &= ~PLAYER_COSTLIFE;
		}
	}
	if(flag & PLAYER_COLLAPSE)
	{
		if(Collapse())
		{
			flag &= ~PLAYER_COLLAPSE;
		}
	}
	if(flag & PLAYER_SLOWCHANGE)
	{
		if(SlowChange())
		{
			flag &= ~PLAYER_SLOWCHANGE;
		}
	}
	if(flag & PLAYER_FASTCHANGE)
	{
		if(FastChange())
		{
			flag &= ~PLAYER_FASTCHANGE;
		}
	}
	if(flag & PLAYER_PLAYERCHANGE)
	{
		if(PlayerChange())
		{
			flag &= ~PLAYER_PLAYERCHANGE;
		}
	}
	if(flag & PLAYER_SHOOT)
	{
		if(Shoot())
		{
			flag &= ~PLAYER_SHOOT;
		}
	}
	if(flag & PLAYER_BOMB)
	{
		if(Bomb())
		{
			flag &= ~PLAYER_BOMB;
		}
	}
	if(flag & PLAYER_DRAIN)
	{
		if(Drain())
		{
			flag &= ~PLAYER_DRAIN;
		}
	}
	if (flag & PLAYER_CHARGE)
	{
		if (Charge())
		{
			flag &= ~PLAYER_CHARGE;
		}
	}
	if(flag & PLAYER_GRAZE)
	{
		if(Graze())
		{
			flag &= ~PLAYER_GRAZE;
		}
	}

	nLifeCost++;
	if (nLifeCost > _PLAYER_LIFECOSTMAX)
	{
		nLifeCost = _PLAYER_LIFECOSTMAX;
	}
	if (rechargedelaytimer)
	{
		rechargedelaytimer--;
	}
	if (infitimer > 0)
	{
		infitimer--;
		bInfi = true;
	}
	else if (infitimer == PLAYER_INFIMAX)
	{
		bInfi = true;
	}
	else
	{
		bInfi = false;
	}
	if (nComboGage)
	{
		nComboGage--;
		if (nComboGage == PLAYER_COMBORESET)
		{
			AddComboHit(-1, true);
		}
		else if (!nComboGage)
		{
			AddSpellPoint(-1);
		}
	}

	//input
	if(!(flag & PLAYER_SHOT || flag & PLAYER_COLLAPSE))
	{
		if (hge->Input_GetDIKey(KS_SLOW_MP_(playerindex)))
		{
			bSlow = true;
			flag &= ~PLAYER_FASTCHANGE;
			if(hge->Input_GetDIKey(KS_SLOW_MP_(playerindex), DIKEY_DOWN))
			{
				if (!(flag & PLAYER_SLOWCHANGE))
				{
					slowtimer = 0;
					flag |= PLAYER_SLOWCHANGE;
				}
			}
		}
		else
		{
			bSlow = false;
			flag &= ~PLAYER_SLOWCHANGE;
			if(hge->Input_GetDIKey(KS_SLOW_MP_(playerindex), DIKEY_UP))
			{
				if (!(flag & PLAYER_FASTCHANGE))
				{
					fasttimer = 0;
					flag |= PLAYER_FASTCHANGE;
				}
			}
		}
		if(bSlow)
		{
			nowspeed = slowspeed;
		}
		else
		{
			nowspeed = speed;
		}
		nowspeed *= speedfactor;
		speedfactor = 1.0f;

		if(hge->Input_GetDIKey(KS_FIRE_MP_(playerindex)))
		{
			if (!Chat::chatitem.IsChatting())
			{
				flag |= PLAYER_SHOOT;
			}
			shootnotpushtimer = 0;
		}
		else
		{
			if (shootnotpushtimer < 0xff)
			{
				shootnotpushtimer++;
			}
		}
		if (shootpushtimer < _PLAYER_SHOOTPUSHOVER)
		{
			if (hge->Input_GetDIKey(KS_FIRE_MP_(playerindex)))
			{
				shootpushtimer++;
			}
			else
			{
				shootpushtimer = 0;
			}
		}
		else
		{
			if (!hge->Input_GetDIKey(KS_FIRE_MP_(playerindex)))
			{
				bCharge = false;
				flag &= ~PLAYER_CHARGE;
				shootpushtimer = 0;
			}
			else
			{
				if (!rechargedelaytimer)
				{
					flag &= ~PLAYER_SHOOT;
					bCharge = true;
					if (shootpushtimer == _PLAYER_SHOOTPUSHOVER)
					{
						if (!(flag & PLAYER_CHARGE))
						{
							chargetimer = 0;
							flag |= PLAYER_CHARGE;
							shootpushtimer = 0xff;
						}
					}
				}
			}
		}
		if (hge->Input_GetDIKey(KS_DRAIN_MP_(playerindex)))
		{
			bDrain = true;
			if (hge->Input_GetDIKey(KS_DRAIN_MP_(playerindex), DIKEY_DOWN))
			{
				if (!(flag & PLAYER_DRAIN))
				{
					draintimer = 0;
					flag |= PLAYER_DRAIN;
				}
			}
		}
		else
		{
			bDrain = false;
			flag &= ~PLAYER_DRAIN;
		}

		/*
		if(!(flag & PLAYER_DRAIN || flag & PLAYER_CHARGE))
		{
			if(hge->Input_GetDIKey(KS_DRAIN_MP_(playerindex), DIKEY_DOWN))
			{
				if (!(flag & PLAYER_PLAYERCHANGE))
				{
					playerchangetimer = 0;
					flag |= PLAYER_PLAYERCHANGE;
				}
			}
		}
		*/
		if((hge->Input_GetDIKey(KS_UP_MP_(playerindex)) ^ hge->Input_GetDIKey(KS_DOWN_MP_(playerindex))) &&
			hge->Input_GetDIKey(KS_LEFT_MP_(playerindex)) ^ hge->Input_GetDIKey(KS_RIGHT_MP_(playerindex)))
			nowspeed *= M_SQUARE_2;
		if(hge->Input_GetDIKey(KS_UP_MP_(playerindex)))
			y -= nowspeed;
		if(hge->Input_GetDIKey(KS_DOWN_MP_(playerindex)))
			y += nowspeed;
		if(hge->Input_GetDIKey(KS_LEFT_MP_(playerindex)))
		{
			updateFrame(PLAYER_FRAME_LEFTPRE);
			x -= nowspeed;
		}
		if(hge->Input_GetDIKey(KS_RIGHT_MP_(playerindex)))
		{
			if (!hge->Input_GetDIKey(KS_LEFT_MP_(playerindex)))
			{
				updateFrame(PLAYER_FRAME_RIGHTPRE);
			}
			else
			{
				updateFrame(PLAYER_FRAME_STAND);
			}
			x += nowspeed;
		}
		if (!hge->Input_GetDIKey(KS_LEFT_MP_(playerindex)) && !hge->Input_GetDIKey(KS_RIGHT_MP_(playerindex)))
		{
			updateFrame(PLAYER_FRAME_STAND);
		}
	}
	if(hge->Input_GetDIKey(KS_QUICK_MP_(playerindex)) && !(flag & PLAYER_MERGE))
	{
		callBomb();
	}

	if (!(flag & PLAYER_MERGE) || mergetimer >= 32)
	{
		if(x > PL_MOVABLE_RIGHT_(playerindex))
			x = PL_MOVABLE_RIGHT_(playerindex);
		else if(x < PL_MOVABLE_LEFT_(playerindex))
			x = PL_MOVABLE_LEFT_(playerindex);
		if(y > PL_MOVABLE_BOTTOM)
			y = PL_MOVABLE_BOTTOM;
		else if(y < PL_MOVABLE_TOP)
			y = PL_MOVABLE_TOP;
	}

	if (bInfi && timer % 8 < 4)
	{
		diffuse = 0xff99ff;
	}
	else
		diffuse = 0xffffff;

	esChange.action();
	esShot.action();
	esPoint.action();
	
	effGraze.MoveTo(x, y);
	effGraze.action();
	effCollapse.action();
	effBorderOn.action();
	effBorderOff.action();

	if(!(flag & PLAYER_GRAZE))
		effGraze.Stop();

	for(int i=0;i<PLAYERGHOSTMAX;i++)
		pg[i].action();
}

bool Player::Merge()
{
	mergetimer++;
	if(mergetimer == 1)
	{
		SetInfi(PLAYERINFI_MERGE, 240);
		if(hge->Input_GetDIKey(KS_SLOW_MP_(playerindex)))
		{
			flag |= PLAYER_SLOWCHANGE;
			slowtimer = 0;
			flag &= ~PLAYER_FASTCHANGE;
		}
		else
		{
			flag |= PLAYER_FASTCHANGE;
			fasttimer = 0;
			flag &= ~PLAYER_SLOWCHANGE;
		}
	}
	if(mergetimer < 48)
	{
		flag &= ~PLAYER_SHOOT;
		x = PL_MERGEPOS_X_(playerindex);
		y = PL_MERGEPOS_Y - (mergetimer-16) * 4.5f;
		alpha = (mergetimer-16) * 8;
	}
	/*
	else if(mergetimer == 48 && mp.spellmode)
	{
		mergetimer = 208;
	}
	*/
	else if(mergetimer > 208 && mergetimer < 240)
	{
		alpha = 0xff;
	}
	else if(mergetimer == 240)
	{
		mergetimer = 0;
		return true;
	}
	return false;
}

bool Player::Shot()
{
	shottimer++;
	// TODO:
	if(bInfi)
	{
		shottimer = 0;
		return true;
	}
	
	if(shottimer == 1)
	{
//		Item::undrainAll();
		SE::push(SE_PLAYER_SHOT, x);
	}
	else if(shottimer == shotdelay)
	{
		shottimer = 0;
		flag |= PLAYER_COSTLIFE;
		return true;
	}

	esShot.hscale = (shotdelay - shottimer) * 4.0f / shotdelay;
	return false;
}

bool Player::CostLife()
{
	costlifetimer++;
	if (costlifetimer == 1)
	{
		if (nLife == 1)
		{
			flag |= PLAYER_COLLAPSE;
			costlifetimer = 0;
			return true;
		}
		int nLifeCostNum = nLifeCost / 720 + 2;
		if (nLife > nLifeCostNum+1)
		{
			nLife -= nLifeCostNum;
		}
		else
		{
			FrontDisplay::fdisp.gameinfodisplay.lastlifecountdown[playerindex] = FDISP_COUNTDOWNTIME;
			SE::push(SE_PLAYER_ALERT, x);
			nLife = 1;
		}
		SetInfi(PLAYERINFI_COSTLIFE, 120);
		EventZone::Build(EVENTZONE_TYPE_BULLETFADEOUT|EVENTZONE_TYPE_ENEMYGHOSTDAMAGE, playerindex, x, y, 120, 0, 10, EVENTZONE_EVENT_NULL, 15.6);
		if (nLife == 1)
		{
			AddCharge(0, PLAYER_CHARGEMAX);
		}
		else
		{
			AddCharge(0, 130-nLife * 10);
		}
		nBounceAngle = RANDA;
	}
	else if (costlifetimer == 60)
	{
		costlifetimer = 0;
		return true;
	}
	else
	{
		hge->Input_SetDIKey(KS_UP_MP_(playerindex), false);
		hge->Input_SetDIKey(KS_DOWN_MP_(playerindex), false);
		hge->Input_SetDIKey(KS_LEFT_MP_(playerindex), false);
		hge->Input_SetDIKey(KS_RIGHT_MP_(playerindex), false);
		hge->Input_SetDIKey(KS_FIRE_MP_(playerindex), false);
		hge->Input_SetDIKey(KS_QUICK_MP_(playerindex), false);
		hge->Input_SetDIKey(KS_SLOW_MP_(playerindex), false);
		hge->Input_SetDIKey(KS_DRAIN_MP_(playerindex), false);
		x += cost(nBounceAngle) * ((60-costlifetimer) / 20.0f);
		y += sint(nBounceAngle) * ((60-costlifetimer) / 20.0f);
	}
	return false;
}

bool Player::Collapse()
{
	collapsetimer++;
	if(collapsetimer == 1)
	{
		for (int i=0; i<2; i++)
		{
			EventZone::Build(EVENTZONE_TYPE_BULLETFADEOUT|EVENTZONE_TYPE_ENEMYGHOSTDAMAGE, i, p[i].x, p[i].y, 64, EVENTZONE_OVERZONE, 1000, EVENTZONE_EVENT_NULL, 16);
		}
//		Bullet::IzeBuild(playerindex, BULLETIZE_FADEOUT, x, y, 64);

		if(bossinfo.isSpell())
			BossInfo::failed = true;
		esCollapse.x = x;
		esCollapse.y = y;
		SE::push(SE_PLAYER_DEAD, x);

		/*
		float aimx;
		float aimy;
		for(int i=0;i<5;i++)
		{
			aimx = (float)(randt()%360 + 40);
			aimy = (float)(randt()%80 - 40 - (480 - y) / 2);
			Item::Build(playerindex, nLife ? ITEM_POWER : ITEM_FULL, x, y + 36, false, 18000 + rMainAngle(aimx, aimy), -sqrt(2 * 0.1f * DIST(x, y, aimx, aimy)));
		}
		aimx = (float)(randt()%360 + 40);
		aimy = (float)(randt()%80 - 40 - (480 - y) / 2);
		Item::Build(playerindex, nLife ? ITEM_BIGPOWER : ITEM_FULL, x, y + 32, false, 18000 + rMainAngle(aimx, aimy), -sqrt(2 * 0.1f * DIST(x, y, aimx, aimy)));
		*/

		effCollapse.MoveTo(x, y , 0, true);
		effCollapse.Fire();
	}
	else if(collapsetimer == 64)
	{
		x = PL_MERGEPOS_X_(playerindex);
		y = PL_MERGEPOS_Y;
		for(int i=0;i<PL_SAVELASTMAX;i++)
		{
			lastx[i] = x;
			lasty[i] = y;
			lastmx[i] = x;
			lastmy[i] = y;
		}

		timer = 0;
		collapsetimer = 0;
		vscale = 1.0f;
		flag |= PLAYER_MERGE;

		SetInfi(PLAYERINFI_COLLAPSE);
		if(nLife)
		{
			nLife--;
//			nPower = PL_DEFAULTNPOWER;
		}
		else
		{
			exist = false;
			return true;
		}

		if(hge->Input_GetDIKey(KS_SLOW_MP_(playerindex)))
		{
			flag |= PLAYER_SLOWCHANGE;
			slowtimer = 0;
			flag &= ~PLAYER_FASTCHANGE;
		}
		else
		{
			flag |= PLAYER_FASTCHANGE;
			fasttimer = 0;
			flag &= ~PLAYER_SLOWCHANGE;
		}

		effCollapse.Stop();

		return true;
	}
	
	esCollapse.hscale = collapsetimer / 1.5f;
	esCollapse.alpha = (BYTE)((WORD)(0xff * collapsetimer) / 0x3f);
	esCollapse.colorSet(0xff0000);

	alpha = (0xff - collapsetimer * 4);
	vscale = (float)(collapsetimer)/40.0f + 1.0f;
	return false;
}

bool Player::Shoot()
{
	if(flag & PLAYER_SHOT || Chat::chatitem.IsChatting())
	{
		shoottimer = 0;
		return true;
	}

	playershootData * item;
	for (int i=0; i<PLAYERSHOOTTYPEMAX; i++)
	{
		item = &(res.playershootdata[i]);
		if (item->timeMod)
		{
			if (item->userID == nowID && item->timeMod && (item->timeMod == 1 || !(shoottimer % item->timeMod)))
			{
				PlayerBullet::Build(playerindex, i);
			}
		}
	}
	shoottimer++;
	//
	if(shootnotpushtimer > _PLAYER_SHOOTNOTPUSHOVER)
	{
		shoottimer = 0;
		return true;
	}
	return false;
}

bool Player::Drain()
{
	draintimer++;
	scr.Execute(SCR_EVENT, SCR_EVENT_PLAYERDRAIN, playerindex);
	return false;
}

bool Player::Bomb()
{
	BYTE ncharge;
	BYTE nchargemax;
	GetNCharge(&ncharge, &nchargemax);
	if (nchargemax > 1)
	{
		shootCharge(nchargemax);
		AddCharge(-PLAYER_CHARGEMAX, -PLAYER_CHARGEMAX);
	}
	return true;
}

bool Player::SlowChange()
{
	if(hge->Input_GetDIKey(KS_SLOW_MP_(playerindex), DIKEY_DOWN))
		slowtimer = 0;
	bSlow = true;
	slowtimer++;
	if(slowtimer == 1)
	{
		ResetPlayerGhost();
		SE::push(SE_PLAYER_SLOWON, x);
		for(int i=0;i<PLAYERGHOSTMAX;i++)
		{
			pg[i].timer = 0;
		}
	}
	else if(slowtimer == 16)
	{
		esPoint.colorSet(0xffffffff);
		slowtimer = 0;
		return true;
	}

	esPoint.actionSet(0, 0, (24 - slowtimer) * 25);
	esPoint.colorSet(((slowtimer*16)<<24)+0xffffff);
	return false;
}

bool Player::FastChange()
{
	if(hge->Input_GetDIKey(KS_SLOW_MP_(playerindex), DIKEY_UP))
		fasttimer = 0;
	bSlow = false;
	fasttimer++;
	if(fasttimer == 1)
	{
		ResetPlayerGhost();
		SE::push(SE_PLAYER_SLOWOFF, x);
		for(int i=0;i<PLAYERGHOSTMAX;i++)
		{
			pg[i].timer = 0;
		}
	}
	else if(fasttimer == 16)
	{
		esPoint.colorSet(0x00ffffff);
		fasttimer = 0;
		return true;
	}
	esPoint.colorSet(((0xff-fasttimer*16)<<24)+0xffffff);
	return false;
}

bool Player::Charge()
{
	chargetimer++;
	if (chargetimer == 1)
	{
		SE::push(SE_PLAYER_CHARGEON, x);
	}
	BYTE nChargeLevel = AddCharge(chargespeed);
	if (hge->Input_GetDIKey(KS_FIRE_MP_(playerindex), DIKEY_UP))
	{
		shootCharge(nChargeLevel);
		chargetimer = 0;
		fCharge = 0;
		rechargedelaytimer = rechargedelay;
		return true;
	}
	return false;
}

bool Player::PlayerChange()
{
	if(hge->Input_GetDIKey(KS_DRAIN_MP_(playerindex), DIKEY_DOWN))
		playerchangetimer = 0;
	playerchangetimer++;
	if(playerchangetimer == 1)
	{
	}
	else if(playerchangetimer == 16)
	{
		playerchangetimer = 0;
		return true;
	}
	esChange.colorSet(0x3030ff | (((16-playerchangetimer) * 16)<<16));
	return false;
}

void Player::changePlayerID(WORD toID, bool moveghost/* =false */)
{
	nowID = toID;
	ResetPlayerGhost(moveghost);
	UpdatePlayerData();
}

bool Player::Graze()
{
	effGraze.Fire();
	SE::push(SE_PLAYER_GRAZE, x);
	return true;
}

void Player::DoEnemyCollapse(float x, float y)
{
	if (bInfi)
	{
		return;
	}
	float addcharge = nComboHitOri / 128.0f + 1.0f;
	if (addcharge > 2.0f)
	{
		addcharge = 2.0f;
	}
	AddComboHit(1, true);
	AddCharge(0, addcharge);

	AddExPoint(1, x, y);
	int addexpoint;
	addexpoint = nComboHitOri + 3;
	if (addexpoint > 28)
	{
		addexpoint = 28;
	}
	AddGhostPoint(addexpoint, x, y);
	int addbulletpoint;
	addbulletpoint = nComboHitOri * 3 + 27;
	if (addbulletpoint > 60)
	{
		addbulletpoint = 60;
	}
	float _x = x + hge->Random_Float(-4, 4);
	float _y = y + hge->Random_Float(-4, 4);
	AddBulletPoint(addbulletpoint, _x, _y);
	int addspellpoint;
	if (nComboHitOri == 1)
	{
		addspellpoint = 20;
	}
	else
	{
		addspellpoint = nComboHitOri * 30 - 20;
		if (addspellpoint > 3000)
		{
			addspellpoint = 3000;
		}
	}
	AddSpellPoint(addspellpoint);
}

void Player::DoGraze(float x, float y)
{
	if(!(flag & (PLAYER_MERGE | PLAYER_SHOT | PLAYER_COLLAPSE)))
	{
		flag |= PLAYER_GRAZE;
	}
}

void Player::DoPlayerBulletHit(int hitonfactor)
{
}

void Player::DoShot()
{
	if (!bInfi && !(flag & (PLAYER_SHOT | PLAYER_COLLAPSE)))
	{
//		if(nPower >= bombperpower)
			flag |= PLAYER_SHOT;
//		else
//			flag |= PLAYER_COLLAPSE;
	}
}

LONGLONG Player::DoItemGet(WORD itemtype)
{
	LONGLONG retscore = 0;
	switch (itemtype)
	{
	case ITEM_POINT:
		//		nPoint++;
		//		retscore = nFaith * (fPoprate + fPopratebase);
		//		if (fPoprate >= 1.0f)
		//		{
		//			retscore *= 2;
		//		}
		break;
	case ITEM_POWER:
		//		nPower+=_PL_POWERADD;
		retscore = 100;
		break;
	case ITEM_BIGPOWER:
		//		nPower += _PL_BIGPOWERADD;
		retscore = 500;
		SE::push(SE_ITEM_POWERUP, x);
		break;
	case ITEM_FULL:
		//		nPower += _PL_FULLPOWERADD;
		//		Item::ChangeItemID(ITEM_FULL, ITEM_SMALLFAITH);
		SE::push(SE_ITEM_POWERUP, x);
		retscore = 1000;
		break;
	case ITEM_BOMB:
		//		nPower += _PL_BOMBPOWERADD;
		SE::push(SE_ITEM_EXTEND, x);
		retscore = 1000;
		break;
	case ITEM_EXTEND:
		SE::push(SE_ITEM_EXTEND, x);
		nLife++;
		if (nLife > initlife)
		{
			nLife = initlife;
		}
//		if(nLife > PL_NPLAYERMAX)
//		{
//			nLife = PL_NPLAYERMAX;
			//			nPower += _PL_BOMBPOWERADD;
//		}
		retscore = 1000;
		break;
	case ITEM_FAITH:
		//		nFaith += _PL_FAITHADD;
		//		retscore = nPower;
		break;
	case ITEM_SMALLFAITH:
		//		nFaith += _PL_SMALLFAITHADD;
		//		retscore = nPower / 100;
		break;
	}
	return retscore;
}

void Player::GetNCharge(BYTE * ncharge, BYTE * nchargemax)
{
	if (ncharge)
	{
		*ncharge = (BYTE)(fCharge/PLAYER_CHARGEONE);
	}
	if (nchargemax)
	{
		*nchargemax = (BYTE)(fChargeMax/PLAYER_CHARGEONE);
	}
}


void Player::ResetPlayerGhost(bool move /* = false */)
{
	int tid = nowID;
	tid *= PLAYERGHOSTMAX * 2;
	if (bSlow)
	{
		tid += PLAYERGHOSTMAX;
	}
	for (int i=0; i<PLAYERGHOSTMAX; i++)
	{
		pg[i].valueSet(playerindex, tid+i, move);
	}
}

void Player::Render()
{
	sprite->SetColor(alpha<<24|diffuse);
	sprite->RenderEx(x, y, 0, hscale, vscale);
}

void Player::RenderEffect()
{
	effGraze.Render();

	for(int i=0;i<PLAYERGHOSTMAX;i++)
		pg[i].Render();
	if(flag & PLAYER_PLAYERCHANGE)
	{
		esChange.Render();
	}
	if(flag & PLAYER_SHOT)
		esShot.Render();
	effBorderOff.Render();
	if(bSlow || flag & PLAYER_FASTCHANGE)
	{
		esPoint.Render();
		esPoint.headangle = -esPoint.headangle;
		esPoint.Render();
		esPoint.headangle = -esPoint.headangle;
	}
	if(flag & PLAYER_COLLAPSE)
		esCollapse.Render();

	effCollapse.Render();
}

void Player::callCollapse()
{
	if (flag & PLAYER_COLLAPSE)
	{
		return;
	}
	flag |= PLAYER_COLLAPSE;
	collapsetimer = 0;
}

bool Player::callBomb()
{
	if (Chat::chatitem.IsChatting() || (flag & PLAYER_COLLAPSE) || bInfi)
	{
		return false;
	}
	return Bomb();
}

void Player::callSlowFastChange(bool toslow)
{
	if (toslow)
	{
		hge->Input_SetDIKey(KS_SLOW_MP_(playerindex));
	}
	else
	{
		hge->Input_SetDIKey(KS_SLOW_MP_(playerindex), false);
	}
}

void Player::callPlayerChange()
{
	flag |= PLAYER_PLAYERCHANGE;
	playerchangetimer = 0;
}

void Player::shootCharge(BYTE nChargeLevel)
{
	switch (nChargeLevel)
	{
	case 0:
		return;
	case 1:
		SetInfi(PLAYERINFI_SHOOTCHARGE, _PL_SHOOTCHARGEINFI_1);
		break;
	case 2:
		SetInfi(PLAYERINFI_SHOOTCHARGE, _PL_SHOOTCHARGEINFI_2);
		AddCharge(-PLAYER_CHARGEONE, -PLAYER_CHARGEONE);
		break;
	case 3:
		SetInfi(PLAYERINFI_SHOOTCHARGE, _PL_SHOOTCHARGEINFI_3);
		AddCharge(-PLAYER_CHARGEONE*2, -PLAYER_CHARGEONE*2);
		break;
	case 4:
		SetInfi(PLAYERINFI_SHOOTCHARGE, _PL_SHOOTCHARGEINFI_4);
		AddCharge(-PLAYER_CHARGEONE*3, -PLAYER_CHARGEONE*3);
		break;
	}
}

void Player::SendEx(float x, float y, bool bythis/* =true */)
{

}

void Player::AddExPoint(int expoint, float x, float y)
{
	nExPoint += expoint;
	if (nExPoint >= fExSendParaB + fExSendParaA * rank)
	{
		AddExPoint(-(fExSendParaB + fExSendParaA * rank), x, y);
		SendEx(x, y, false);
	}
}

void Player::AddGhostPoint(int ghostpoint, float x, float y)
{
	nGhostPoint += ghostpoint;
	if (nGhostPoint >= 60-rank*1.5f)
	{
		if (nBulletPoint >= 10)
		{
			AddGhostPoint(-(60-rank*2), x, y);
			AddBulletPoint(-10, x, y);
			Ghost::SendGhost(1-playerindex, x, y, false);
		}
	}
}

void Player::AddBulletPoint(int bulletpoint, float x, float y)
{
	nBulletPoint += bulletpoint;
	if (nBulletPoint >= 120-rank*4)
	{
		AddBulletPoint(-(120-rank*4), x, y);
		BYTE setID = EFFSPSET_SYSTEM_SENDBLUEBULLET_0;
		if (hge->Random_Int(0, 2) == 0)
		{
			setID = EFFSPSET_SYSTEM_SENDREDBULLET_0;
		}
		Bullet::SendBullet(1-playerindex, x, y, setID);
	}
}

void Player::AddSpellPoint(int spellpoint)
{
	if (spellpoint < 0)
	{
		nSpellPoint = 0;
		return;
	}
	nSpellPoint += spellpoint;
}

void Player::AddComboHit(int combo, bool ori)
{
	if (combo < 0)
	{
		nComboHit = 0;
		nComboHitOri = 0;
		return;
	}
	nComboHit += combo;
	if (ori)
	{
		nComboHitOri += combo;
	}

	if (nComboGage < 74)
	{
		nComboGage += 30;
		if (nComboGage < 74)
		{
			nComboGage = 74;
		}
	}
	else if (nComboGage < 94)
	{
		nComboGage += 5;
	}
	else
	{
		nComboGage += 2;
	}
	if (nComboGage > PLAYER_COMBOGAGEMAX)
	{
		nComboGage = PLAYER_COMBOGAGEMAX;
	}
}

BYTE Player::AddCharge(float addcharge, float addchargemax)
{
	BYTE ncharge;
	BYTE nchargemax;
	GetNCharge(&ncharge, &nchargemax);
	fChargeMax += addchargemax;
	if (fChargeMax > PLAYER_CHARGEMAX)
	{
		fChargeMax = PLAYER_CHARGEMAX;
	}
	if (fChargeMax < 0)
	{
		fChargeMax = 0;
	}
	fCharge += addcharge;
	if (fCharge > fChargeMax)
	{
		fCharge = fChargeMax;
	}
	if (fCharge < 0)
	{
		fCharge = 0;
	}
	BYTE nchargenow;
	BYTE nchargemaxnow;
	GetNCharge(&nchargenow, &nchargemaxnow);
	if (nchargenow > ncharge)
	{
		SE::push(SE_PLAYER_CHARGEUP);
	}
	if (nchargemaxnow > nchargemax)
	{
		FrontDisplay::fdisp.gameinfodisplay.gaugefilledcountdown[playerindex] = FDISP_COUNTDOWNTIME;
	}
	return nchargenow;
}
