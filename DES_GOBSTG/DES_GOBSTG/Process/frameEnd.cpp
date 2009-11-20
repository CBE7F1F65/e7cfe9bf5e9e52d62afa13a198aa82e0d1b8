#include "processPrep.h"

void Process::frameEnd()
{
	objcount = 0;
	if(active)
	{
		framecounter++;
		float lost = (hge->Timer_GetDelta() - 1/60.0f) * 100 * 60.0f;
		if(lost < 0)
			lost = 0;
		if(lost > 100)
			lost = 100;
		Player::p[0].lostStack += lost;

		if (!(stopflag & FRAME_STOPFLAG_WORLDSHAKE))
		{
			WorldShake();
		}

		if(Player::p[0].exist && state != STATE_CLEAR)
		{
			alltime++;
			if (!(stopflag & FRAME_STOPFLAG_PLAYER))
			{
				Player::p[0].action();
			}
		}
		
		PlayerBullet::locked = PBLOCK_LOST;
		Enemy::Action(!(stopflag & FRAME_STOPFLAG_ENEMY));
		Ghost::Action(!(stopflag & FRAME_STOPFLAG_GHOST));
		/*
		for(int i=0;i<ENEMYMAX;i++)
		{
			if(Enemy::en[i].exist)
			{
				objcount ++;

				if (!(stopflag & FRAME_STOPFLAG_ENEMY))
				{
					Enemy::en[i].action();
				}
				else
				{
					Enemy::en[i].actionInStop();
				}
				if(PlayerBullet::locked == PBLOCK_LOST && Enemy::en[i].able)
				{
					if (Enemy::en[i].x <= M_CLIENT_RIGHT && Enemy::en[i].x >= M_CLIENT_LEFT
						&& Enemy::en[i].y <= M_CLIENT_BOTTOM && Enemy::en[i].y >= M_CLIENT_TOP)
					{
						PlayerBullet::locked = i;
					}
				}
			}
		}
		*/
		/*
		for(int i=0;i<GHOSTMAX;i++)
		{
			if(Ghost::gh[i].exist)
			{
				objcount ++;

				if (!(stopflag & FRAME_STOPFLAG_GHOST))
				{
					Ghost::gh[i].action();
				}
				else
				{
					Ghost::gh[i].actionInStop();
				}
				/*
				if(Player::p.bBorder && PlayerBullet::locked == PBLOCK_LOST && gh[i].able && !gh[i].half)
				{
					if (gh[i].x <= M_CLIENT_RIGHT && gh[i].x >= M_CLIENT_LEFT
						&& gh[i].y <= M_CLIENT_BOTTOM && gh[i].y >= M_CLIENT_TOP)
					{
						PlayerBullet::locked = i + PBLOCK_GHOST;
					}
				}
				* /
			}
		}
		*/
		Enemy::dmgz.clear_item();
		if (bu.size)
		{
			ZeroMemory(Bullet::renderDepth, sizeof(RenderDepth) * BULLETTYPEMAX);
			DWORD i = 0;
			DWORD size = bu.size;
			for (bu.toBegin(); i<size; bu.toNext(), i++)
			{
				if (!bu.isValid())
				{
					continue;
				}
				if ((*bu).exist)
				{
					objcount++;

					if (!(stopflag & FRAME_STOPFLAG_BULLET))
					{
						(*bu).action();
					}
					else
					{
						(*bu).actionInStop();
					}
				}
				else
				{
					bu.pop();
				}
			}
		}
		if (!(stopflag & FRAME_STOPFLAG_BULLET))
		{
			if (Bullet::izel.size)
			{
				DWORD i = 0;
				DWORD size = Bullet::izel.size;
				for (Bullet::izel.toBegin(); i<size; Bullet::izel.toNext(), i++)
				{
					if (Bullet::izel.isValid())
					{
						IzeZone * tize = &(*(Bullet::izel));
						tize->timer++;
						if (tize->timer == tize->maxtime)
						{
							Bullet::izel.pop();
						}
					}
				}
			}
		}
		if (be.size)
		{
			if (!(stopflag & FRAME_STOPFLAG_BEAM))
			{
				DWORD i = 0;
				DWORD size = be.size;
				for (be.toBegin(); i<size; be.toNext(), i++)
				{
					if (!be.isValid())
					{
						continue;
					}
					if ((*be).exist)
					{
						objcount ++;

						(*be).action();
					}
					else
					{
						be.pop();
					}
				}
			}
		}
		if (pb.size)
		{
			if (!(stopflag & FRAME_STOPFLAG_PLAYERBULLET))
			{
				DWORD i = 0;
				DWORD size = pb.size;
				for (pb.toBegin(); i<size; pb.toNext(), i++)
				{
					if (!pb.isValid())
					{
						continue;
					}
					if ((*pb).exist)
					{
						(*pb).action();
					}
					else
					{
						pb.pop();
					}
				}
			}
		}
		if (mi.size)
		{
			if (!(stopflag & FRAME_STOPFLAG_ITEM))
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
		}

		Scripter::stopEdefScript = false;
		if(BossInfo::flag)
		{
			if(bossinfo.action())
			{
				time = 0;
				if(!spellmode)
				{
					scene = BossInfo::turntoscene;
				}
				else
					Player::p[0].exist = false;
			}
			if(BossInfo::flag >= BOSSINFO_COLLAPSE)
				Scripter::stopEdefScript = true;
		}
	}
	if(active || !Player::p[0].exist && state != STATE_CONTINUE)
	{
		if (!(stopflag & FRAME_STOPFLAG_LAYER))
		{
			BGLayer::Action(active);
		}


		if (!(stopflag & FRAME_STOPFLAG_EFFECTSYS))
		{
			for(int i=0; i<EFFECTSYSMAX; i++)
			{
				if(effsys[i].exist)
					effsys[i].action();
			}
		}
	}
	for (int i=0; i<SELSYSTEMMAX; i++)
	{
		selsys[i].action();
	}
	for(list<InfoSelect>::iterator i=infoselect.begin();i!=infoselect.end();i++)
	{
		if(!InfoSelect::complete)
		{
			i->action();
		}
		else
		{
			InfoSelect::Clear();
			break;
		}
	}
	if (Player::p[0].nHiScore < Player::p[0].nScore)
	{
		Player::p[0].nHiScore = Player::p[0].nScore;
	}

	SE::play();
	active = false;
}