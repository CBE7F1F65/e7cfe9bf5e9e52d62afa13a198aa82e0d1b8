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

		if (state != STATE_CLEAR)
		{
			Player::Action(_stopflag);
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
	active = false;
}