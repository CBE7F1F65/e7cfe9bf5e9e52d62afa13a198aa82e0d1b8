#include "processPrep.h"

void Process::frameEnd()
{
	DWORD _stopflag = 0;
	for (int i=0; i<FRAME_STOPINFOMAX; i++)
	{
		if (stoptimer[i])
		{
			_stopflag |= stopflag[i];
		}
	}

	if(active)
	{
		framecounter++;

		WorldShake(_stopflag);

		if (state == STATE_CLEAR)
		{
			for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
			{
				GameInput::SetKey(i, KSI_FIRE, false);
				GameInput::SetKey(i, KSI_QUICK, false);
				GameInput::SetKey(i, KSI_SLOW, false);
				GameInput::SetKey(i, KSI_DRAIN, false);
			}
		}
		if (!Player::Action(_stopflag))
		{
			SetState(STATE_CLEAR, -1);
			return;
		}
		Enemy::Action(_stopflag);
		Bullet::Action(_stopflag);
		EffectSp::Action(_stopflag);
		Beam::Action(_stopflag);
		PlayerBullet::Action(_stopflag);
		Item::Action(_stopflag);
		EventZone::Action(_stopflag);

		/*
		if(BossInfo::flag)
		{
			if(BossInfo::bossinfo.action())
			{
				time = 0;
			}
		}
		*/
	}
	if(active || !Player::CheckAble() && state != STATE_CONTINUE)
	{
		BGLayer::Action(_stopflag, active);
		Effectsys::Action(_stopflag);
	}
	BGLayer::ActionSpecial();
	SelectSystem::Action();

	SE::play();
	if (active)
	{
		for (int i=0; i<FRAME_STOPINFOMAX; i++)
		{
			if (stopflag[i])
			{
				stoptimer[i]--;
				if (stoptimer[i] == 0)
				{
					stopflag[i] = 0;
				}
			}
		}
	}
	active = false;
}