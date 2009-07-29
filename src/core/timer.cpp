/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Core functions implementation: timer
*/


#include "hge_impl.h"


float CALL HGE_Impl::Timer_GetTime()
{
	return fTime;
}
//edit by Thor/h5nc
//begin
float CALL HGE_Impl::Timer_GetDelta()
{
	return fDeltaTime;
}
//end

float CALL HGE_Impl::Timer_GetFPS(int mod)
{
	if(mod < 1)
		return fFPS;
	else
	{
		static float nowFPS = 0;
		static float fLastTime = 0;
		static DWORD nLastFrameCounter = 0;
		int modbase = nFrameSkip < 2 ? nFrameCounter : (nFrameCounter / nFrameSkip);
		if((modbase) % mod == 1)
		{
			if (nFrameCounter > nLastFrameCounter && fTime > fLastTime)
			{
				nowFPS = 1 / ((fTime - fLastTime) / (nFrameCounter - nLastFrameCounter));
			}
			fLastTime = fTime;
			nLastFrameCounter = nFrameCounter;
		}
		return nowFPS;
	}
}

float CALL HGE_Impl::Timer_GetWorstFPS(int mod)
{
	if(mod <= 1)
		return fFPS;
	static float worstFPS = HGEFPS_MAX;
	static float worstFPSMod = worstFPS;
	if(worstFPS > fFPS)
		worstFPS = fFPS;
	int modbase = nFrameSkip < 2 ? nFrameCounter : (nFrameCounter / nFrameSkip);
	if((modbase) % mod == 1)
	{
		worstFPSMod = worstFPS;
		worstFPS = HGEFPS_MAX;
	}
	return worstFPSMod;
}
