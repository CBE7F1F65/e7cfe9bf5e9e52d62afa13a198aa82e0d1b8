#include "processPrep.h"

void Process::frameEnd()
{
	if(active)
	{
		framecounter++;

		if (!(stopflag & FRAME_STOPFLAG_WORLDSHAKE))
		{
			WorldShake();
		}

		bool notinstop[M_PL_MATCHMAXPLAYER];
		notinstop[0] = !(stopflag & FRAME_STOPFLAG_PLAYER_0);
		notinstop[1] = !(stopflag & FRAME_STOPFLAG_PLAYER_1);
		if (state != STATE_CLEAR)
		{
			Player::Action(notinstop);
			alltime++;
		}
		Player::AddLostStack();
		
		PlayerBullet::locked = PBLOCK_LOST;
		Enemy::Action(!(stopflag & FRAME_STOPFLAG_ENEMY));
//		Ghost::Action(!(stopflag & FRAME_STOPFLAG_GHOST));
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
		Bullet::Action(!(stopflag & FRAME_STOPFLAG_BULLET));
		if (!(stopflag & FRAME_STOPFLAG_BULLET))
		{
			EffectSp::Action();
		}
		if (!(stopflag & FRAME_STOPFLAG_BEAM))
		{
			Beam::Action();
		}
		if (!(stopflag & FRAME_STOPFLAG_PLAYERBULLET))
		{
			PlayerBullet::Action();
		}
		if (!(stopflag & FRAME_STOPFLAG_ITEM))
		{
			Item::Action(state != STATE_PAUSE);
		}
		EventZone::Action();

		Scripter::stopEdefScript = false;
		if(BossInfo::flag)
		{
			if(bossinfo.action())
			{
				time = 0;
			}
			if(BossInfo::flag >= BOSSINFO_COLLAPSE)
				Scripter::stopEdefScript = true;
		}
	}
	if(active || !Player::CheckAble() && state != STATE_CONTINUE)
	{
		if (!(stopflag & FRAME_STOPFLAG_LAYER))
		{
			BGLayer::Action(active);
		}


		if (!(stopflag & FRAME_STOPFLAG_EFFECTSYS))
		{
			Effectsys::Action();
		}
	}
	SelectSystem::Action();

	SE::play();
	active = false;
}