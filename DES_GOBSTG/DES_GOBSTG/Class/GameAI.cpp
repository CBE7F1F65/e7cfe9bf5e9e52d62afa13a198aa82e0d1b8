#include "../header/GameAI.h"
#include "../header/GameInput.h"
#include "../header/Player.h"

GameAI GameAI::ai[M_PL_MATCHMAXPLAYER];

GameAI::GameAI()
{
}

GameAI::~GameAI()
{
}

void GameAI::Init()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		ai[i].playerindex = i;
		ai[i].SetAble(false);
		ai[i].aidraintime = 0;
		ai[i].drainmaxpushtime = 0;
		ai[i].drainpushtimer = 0;
	}
}

void GameAI::ClearAll()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		ai[i].aimtobelow = false;
		ai[i].inrisk = false;
		ai[i].aidraintime = 0;
		ai[i].drainmaxpushtime = 0;
		ai[i].drainpushtimer = 0;
		ai[i].ClearRisk();
	}
}

void GameAI::SetAble(bool _able)
{
	able = _able;
}

bool GameAI::UpdateBasicInfo(float _x, float _y, float _speed, float _slowspeed, float _r, int _aidraintime)
{
	if (!able)
	{
		return false;
	}
	x = _x;
	y = _y;
	speed = _speed;
	slowspeed = _slowspeed;
	r = _r;
	aidraintime = _aidraintime;
	return UpdateMoveAbleInfo();
}

bool GameAI::UpdateMoveAbleInfo()
{
	if (!able)
	{
		return false;
	}
	memcpy(lastmoveablepos, moveablepos, sizeof(GameAIPosition)*GAMEAI_ABLEPOSITIONNUM);
	moveablepos[GAMEAI_ABLEPOSITION_N].x = x;
	moveablepos[GAMEAI_ABLEPOSITION_N].y = y;

	float nowspeed = speed;
	moveablepos[GAMEAI_ABLEPOSITION_U].x = x;
	moveablepos[GAMEAI_ABLEPOSITION_U].y = y - nowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_D].x = x;
	moveablepos[GAMEAI_ABLEPOSITION_D].y = y + nowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_L].x = x - nowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_L].y = y;
	moveablepos[GAMEAI_ABLEPOSITION_R].x = x + nowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_R].y = y;

	nowspeed *= M_SQUARE_2;
	moveablepos[GAMEAI_ABLEPOSITION_LU].x = x - nowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_LU].y = y - nowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_RU].x = x + nowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_RU].y = y - nowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_LD].x = x - nowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_LD].y = y + nowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_RD].x = x + nowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_RD].y = y + nowspeed;

	nowspeed = slowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_US].x = x;
	moveablepos[GAMEAI_ABLEPOSITION_US].y = y - nowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_DS].x = x;
	moveablepos[GAMEAI_ABLEPOSITION_DS].y = y + nowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_LS].x = x - nowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_LS].y = y;
	moveablepos[GAMEAI_ABLEPOSITION_RS].x = x + nowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_RS].y = y;

	nowspeed *= M_SQUARE_2;
	moveablepos[GAMEAI_ABLEPOSITION_LUS].x = x - nowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_LUS].y = y - nowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_RUS].x = x + nowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_RUS].y = y - nowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_LDS].x = x - nowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_LDS].y = y + nowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_RDS].x = x + nowspeed;
	moveablepos[GAMEAI_ABLEPOSITION_RDS].y = y + nowspeed;

	for (int i=0; i<GAMEAI_ABLEPOSITIONNUM; i++)
	{
		if(moveablepos[i].x > PL_MOVABLE_RIGHT_(playerindex))
			moveablepos[i].x = PL_MOVABLE_RIGHT_(playerindex);
		else if(moveablepos[i].x < PL_MOVABLE_LEFT_(playerindex))
			moveablepos[i].x = PL_MOVABLE_LEFT_(playerindex);
		if(moveablepos[i].y > PL_MOVABLE_BOTTOM)
			moveablepos[i].y = PL_MOVABLE_BOTTOM;
		else if(moveablepos[i].y < PL_MOVABLE_TOP)
			moveablepos[i].y = PL_MOVABLE_TOP;
	}

	return true;
}

bool GameAI::SetAim(float _aimx, float _aimy, bool tobelow)
{
	if (!able)
	{
		return false;
	}
	aimx = _aimx;
	aimy = _aimy;
	if(aimx > PL_MOVABLE_RIGHT_(playerindex))
		aimx = PL_MOVABLE_RIGHT_(playerindex);
	else if(aimx < PL_MOVABLE_LEFT_(playerindex))
		aimx = PL_MOVABLE_LEFT_(playerindex);
	if(aimy > PL_MOVABLE_BOTTOM)
		aimy = PL_MOVABLE_BOTTOM;
	else if(aimy < PL_MOVABLE_TOP)
		aimy = PL_MOVABLE_TOP;
	aimtobelow = tobelow;
	return true;
}

bool GameAI::IsPlayerSafe()
{
	if (!able)
	{
		return true;
	}
	if (Player::p[playerindex].bInfi && Player::p[playerindex].infitimer > 3)
	{
		return true;
	}
	return false;
}

bool GameAI::CheckBulletCollision(Bullet * item)
{
	if (IsPlayerSafe())
	{
		return false;
	}
	if (item->fadeout)
	{
		return false;
	}
	if (!item->isInRect(x, y, r+speed, 1))
	{
		return false;
	}
	bool bret = false;
	for (int i=0; i<GAMEAI_ABLEPOSITIONNUM; i++)
	{
		if (moveablepos[i].risk < GAMEAI_RISK_FULL)
		{
			if (item->isInRect(moveablepos[i].x, moveablepos[i].y, r, 1)/* || item->isInRect(moveablepos[i].x, moveablepos[i].y, r)*/)
			{
				moveablepos[i].risk = GAMEAI_RISK_FULL;
				bret = true;
			}
		}
	}
	return bret;
}

bool GameAI::CheckBeamCollision(Beam * item)
{
	if (IsPlayerSafe())
	{
		return false;
	}
	if (item->fadeout)
	{
		return false;
	}
	bool bret = false;
	for (int i=0; i<GAMEAI_ABLEPOSITIONNUM; i++)
	{
		if (moveablepos[i].risk < GAMEAI_RISK_FULL)
		{
			if (item->isInRect(moveablepos[i].x, moveablepos[i].y, r*4, 1) || item->isInRect(moveablepos[i].x, moveablepos[i].y, r*4, 0))
			{
				moveablepos[i].risk = GAMEAI_RISK_FULL;
				bret = true;
			}
		}
	}
	return bret;
}

bool GameAI::CheckEnemyCollision(Enemy * item, float w, float h)
{
	if (IsPlayerSafe())
	{
		return false;
	}
	if (item->fadeout)
	{
		return false;
	}
	bool bret = false;
	for (int i=0; i<GAMEAI_ABLEPOSITIONNUM; i++)
	{
		if (moveablepos[i].risk < GAMEAI_RISK_FULL)
		{
			if (item->isInRect(moveablepos[i].x, moveablepos[i].y, r*4, w, h, 1) || item->isInRect(moveablepos[i].x, moveablepos[i].y, r*4, w, h, 0))
			{
				moveablepos[i].risk = GAMEAI_RISK_FULL;
				bret = true;
			}
		}
	}
	return bret;
}

bool GameAI::CheckEventZoneCollision(EventZone * item)
{
	if (IsPlayerSafe())
	{
		return false;
	}
	if (item->type != EVENTZONE_TYPE_PLAYERDAMAGE)
	{
		return false;
	}
	bool bret = false;
	for (int i=0; i<GAMEAI_ABLEPOSITIONNUM; i++)
	{
		if (moveablepos[i].risk < GAMEAI_RISK_FULL)
		{
			if (item->isInRect(moveablepos[i].x, moveablepos[i].y, r*4, 1))
			{
				moveablepos[i].risk = GAMEAI_RISK_FULL;
				bret = true;
			}
		}
	}
	return bret;
}

bool GameAI::SetMove()
{
	if (!able)
	{
		return false;
	}
	float tox;
	float toy;

	float overr = 80.0f;

	//below
	if (aimtobelow)
	{
		if (aimy < y)
		{
			if (aimy < M_CLIENT_CENTER_Y)
			{
				aimy = M_CLIENT_CENTER_Y;
			}
			else
			{
				aimy = y;
			}
		}
	}
	//

	tox = (aimx - x) / speed / overr;
	toy = (aimy - y) / speed / overr;

	if (tox > 1.0f)
	{
		tox = 1.0f;
	}
	else if (tox < -1.0f)
	{
		tox = -1.0f;
	}
	if (toy > 1.0f)
	{
		toy = 1.0f;
	}
	else if (toy < -1.0f)
	{
		toy = -1.0f;
	}

	float neutral = 0.05f;

	float randxprop = randtf(-1.0f-neutral, 1.0f+neutral);
	float randyprop = randtf(-1.0f-neutral, 1.0f+neutral);

	AnalyzeCheckOrder(tox, toy, neutral, randxprop, randyprop);

	BYTE nCharge;
	BYTE nChargeMax;
	Player::p[playerindex].GetNCharge(&nCharge, &nChargeMax);

	bool bdone = false;
	int risknum = 0;
	for (int i=0; i<GAMEAI_ABLEPOSITIONNUM; i++)
	{
		if (moveablepos[i].risk >= GAMEAI_RISK_MEDIUM)
		{
			risknum++;
		}
	}
	if (risknum > GAMEAI_ABLEPOSITIONNUM/2)
	{
		inrisk = true;
	}
	else if (nCharge)
	{
		inrisk = false;
	}
	if (Player::p[playerindex].timer % 8 != 0 && Player::p[playerindex].nComboGage < PLAYER_COMBOGAGEMAX * 2 / 3)
	{
		GameInput::SetKey(playerindex, KSI_FIRE, true);
	}
	if (inrisk && nChargeMax && !nCharge || nChargeMax == 4 && nCharge < 2)
	{
		GameInput::SetKey(playerindex, KSI_FIRE, true);
//		GameInput::SetKey(playerindex, KSI_DRAIN, true);
	}
	if (Player::p[playerindex].nSpellPoint > 500000)
	{
		GameInput::SetKey(playerindex, KSI_FIRE, true);
	}


	drainpushtimer++;
	if (drainpushtimer >= drainmaxpushtime)
	{
		drainmaxpushtime = randt(aidraintime/2, aidraintime);
		drainpushtimer = -randt(aidraintime/2, aidraintime);
	}
	else if(drainpushtimer >= 0)
	{
		GameInput::SetKey(playerindex, KSI_DRAIN, true);
	}

	for (int i=0; i<GAMEAI_ABLEPOSITIONNUM; i++)
	{
		int tindex = checkorderlist[i];
		if (moveablepos[tindex].risk < GAMEAI_RISK_FULL)
		{
			bdone = true;
			switch (tindex)
			{
			case GAMEAI_ABLEPOSITION_U:
				GameInput::SetKey(playerindex, KSI_UP);
				break;
			case GAMEAI_ABLEPOSITION_RU:
				GameInput::SetKey(playerindex, KSI_UP);
				GameInput::SetKey(playerindex, KSI_RIGHT);
				break;
			case GAMEAI_ABLEPOSITION_R:
				GameInput::SetKey(playerindex, KSI_RIGHT);
				break;
			case GAMEAI_ABLEPOSITION_RD:
				GameInput::SetKey(playerindex, KSI_RIGHT);
				GameInput::SetKey(playerindex, KSI_DOWN);
				break;
			case GAMEAI_ABLEPOSITION_D:
				GameInput::SetKey(playerindex, KSI_DOWN);
				break;
			case GAMEAI_ABLEPOSITION_LD:
				GameInput::SetKey(playerindex, KSI_DOWN);
				GameInput::SetKey(playerindex, KSI_LEFT);
				break;
			case GAMEAI_ABLEPOSITION_L:
				GameInput::SetKey(playerindex, KSI_LEFT);
				break;
			case GAMEAI_ABLEPOSITION_LU:
				GameInput::SetKey(playerindex, KSI_LEFT);
				GameInput::SetKey(playerindex, KSI_UP);
				break;

			case GAMEAI_ABLEPOSITION_US:
				GameInput::SetKey(playerindex, KSI_UP);
				GameInput::SetKey(playerindex, KSI_SLOW);
				break;
			case GAMEAI_ABLEPOSITION_RUS:
				GameInput::SetKey(playerindex, KSI_UP);
				GameInput::SetKey(playerindex, KSI_RIGHT);
				GameInput::SetKey(playerindex, KSI_SLOW);
				break;
			case GAMEAI_ABLEPOSITION_RS:
				GameInput::SetKey(playerindex, KSI_RIGHT);
				GameInput::SetKey(playerindex, KSI_SLOW);
				break;
			case GAMEAI_ABLEPOSITION_RDS:
				GameInput::SetKey(playerindex, KSI_RIGHT);
				GameInput::SetKey(playerindex, KSI_DOWN);
				GameInput::SetKey(playerindex, KSI_SLOW);
				break;
			case GAMEAI_ABLEPOSITION_DS:
				GameInput::SetKey(playerindex, KSI_DOWN);
				GameInput::SetKey(playerindex, KSI_SLOW);
				break;
			case GAMEAI_ABLEPOSITION_LDS:
				GameInput::SetKey(playerindex, KSI_DOWN);
				GameInput::SetKey(playerindex, KSI_LEFT);
				GameInput::SetKey(playerindex, KSI_SLOW);
				break;
			case GAMEAI_ABLEPOSITION_LS:
				GameInput::SetKey(playerindex, KSI_LEFT);
				GameInput::SetKey(playerindex, KSI_SLOW);
				break;
			case GAMEAI_ABLEPOSITION_LUS:
				GameInput::SetKey(playerindex, KSI_LEFT);
				GameInput::SetKey(playerindex, KSI_UP);
				GameInput::SetKey(playerindex, KSI_SLOW);
				break;

			case GAMEAI_ABLEPOSITION_N:
				break;
			}
			break;
		}
	}
	bool bshot = Player::p[playerindex].flag & PLAYER_SHOT;
	if ((bdone == false || bshot) && !Player::p[playerindex].bInfi)
	{
		if (bshot && !nCharge && nChargeMax > 1)
		{
			GameInput::SetKey(playerindex, KSI_QUICK, true);
		}
		GameInput::SetKey(playerindex, KSI_FIRE, false);
	}
	ClearRisk();
	return true;
}

void GameAI::ClearRisk()
{
	for (int i=0; i<GAMEAI_ABLEPOSITIONNUM; i++)
	{
		moveablepos[i].risk = 0;
	}
}

void GameAI::AnalyzeCheckOrder(float tox, float toy, float neutral, float randxprop, float randyprop)
{
	if (!able)
	{
		return;
	}
	int xtend = AnalyzeCheckOrderXY(tox, neutral, randxprop);
	int ytend = AnalyzeCheckOrderXY(toy, neutral, randyprop);
	AnalyzeCheckOrderFinal(tox, toy, xtend, ytend);
}

void GameAI::AnalyzeCheckOrderFinal(float tox, float toy, int xtend, int ytend)
{
	int absxtend = xtend > 0 ? xtend : -xtend;
	int absytend = ytend > 0 ? ytend : -ytend;

	if (xtend == ytend)
	{
		if (tox > toy)
		{
			if (xtend < 0)
			{
				xtend++;
			}
			else
			{
				xtend--;
			}
		}
		else
		{
			if (ytend < 0)
			{
				ytend++;
			}
			else
			{
				ytend--;
			}
		}
	}
	if (xtend == -ytend)
	{
		if (tox > -toy)
		{
			if (xtend > 0)
			{
				ytend--;
			}
			else
			{
				ytend++;
			}
		}
		else
		{
			if (ytend > 0)
			{
				xtend--;
			}
			else
			{
				xtend++;
			}
		}
	}

	float neutralprop = (fabsf(xtend) + fabsf(ytend)) / 2.0f;
	int neutralpos = 0;
	if (neutralprop <= 2.0f)
	{
	}
	else if (neutralprop <= 3.0f)
	{
		neutralpos = 3;
	}
	else if (neutralpos <= 4.0f)
	{
		neutralpos = 8;
	}
	else
	{
		neutralpos = 12;
	}

	UpdateCheckOrder(xtend, ytend, neutralpos);
}

struct _gameai_ordertable_struct{
	int xtend;
	int ytend;
	int order[GAMEAI_ABLEPOSITIONNUM];
};

static _gameai_ordertable_struct _gameai_ordertable[]	=	{
	{-6,	5,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_DS,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RDS,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_RS,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-6,	4,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_DS,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RDS,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_RS,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-6,	3,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_DS,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RDS,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_RS,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-6,	2,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_DS,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RDS,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_RS,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-6,	1,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_DS,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RDS,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_RS,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-5,	4,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_DS,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RDS,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_RS,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-5,	2,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_DS,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RDS,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_RS,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-4,	3,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_DS,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RDS,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_RS,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-4,	2,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_DS,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RDS,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_RS,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-4,	1,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_DS,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RDS,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_RS,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-3,	2,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_DS,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RDS,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_RS,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-2,	1,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_DS,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RDS,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_RS,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-5,	6,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-4,	6,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-3,	6,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-2,	6,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-1,	6,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-4,	5,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-2,	5,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-3,	4,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-2,	4,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-1,	4,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-2,	3,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{-1,	2,	GAMEAI_ABLEPOSITION_LDS,	GAMEAI_ABLEPOSITION_LD,	GAMEAI_ABLEPOSITION_LS,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_LUS,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_D,	GAMEAI_ABLEPOSITION_L,	GAMEAI_ABLEPOSITION_RD,	GAMEAI_ABLEPOSITION_LU,	GAMEAI_ABLEPOSITION_US,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_R,	GAMEAI_ABLEPOSITION_U,	GAMEAI_ABLEPOSITION_RUS,	GAMEAI_ABLEPOSITION_RU},
	{0}
};

void GameAI::UpdateCheckOrder(int xtend, int ytend, int neutralpos)
{
	if (!able)
	{
		return;
	}
	int addrollval = 0;
	if (xtend < 0 && ytend < 0)
	{
		addrollval = 2;
		ytend = -ytend;
	}
	else if (xtend > 0)
	{
		if (ytend < 0)
		{
			addrollval = 4;
			ytend = -ytend;
		}
		else
		{
			addrollval = 6;
		}
		xtend = -xtend;
	}

	int i=0;
	while (_gameai_ordertable[i].xtend)
	{
		if (xtend == _gameai_ordertable[i].xtend && ytend == _gameai_ordertable[i].ytend)
		{
			int neutraladdindex = 0;
			for (int j=0; j<GAMEAI_ABLEPOSITIONNUM; j++)
			{
				if (j == neutralpos)
				{
					checkorderlist[j] = GAMEAI_ABLEPOSITION_N;
					neutraladdindex = 1;
					continue;
				}
				checkorderlist[j] = _gameai_ordertable[i].order[j+neutraladdindex];
			}
			break;
		}
		i++;
	}

	if (addrollval)
	{
		for (int i=0; i<GAMEAI_ABLEPOSITIONNUM; i++)
		{
			if (checkorderlist[i] < 8)
			{
				checkorderlist[i] = (checkorderlist[i] + addrollval) % 8;
			}
			else if (checkorderlist[i] < 16)
			{
				checkorderlist[i] = (checkorderlist[i] + addrollval) % 8 + 8;
			}
		}
	}
}

int GameAI::AnalyzeCheckOrderXY(float toxy, float neutral, float randxyprop)
{
	int iret;
	if (toxy > neutral)
	{
		if (fabsf(toxy) < fabsf(randxyprop))
		{
			iret = 4;
		}
		else
		{
			iret = 6;
		}
	}
	else if (toxy > -neutral)
	{
		if (toxy > 0)
		{
			iret = 2;
		}
		else
		{
			iret = -2;
		}
	}
	else
	{
		if (fabsf(toxy) < fabsf(randxyprop))
		{
			iret = -4;
		}
		else
		{
			iret = -6;
		}
	}
	return iret;
}