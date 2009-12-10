#include "Process.h"
#include "Player.h"
#include "Data.h"
#include "DataConnector.h"
#include "Replay.h"
#include "GameInput.h"

void Process::frameStart()
{
	time++;
	WORD nowInput = 0;
	if(!replaymode)
	{
		playing = true;
		nowInput = GameInput::GetNowInput();
		Replay::rpy.WriteInput(nowInput);
	}
	else if(true/*!Player::p[0].ncCont*/)
	{
		nowInput = Replay::rpy.ReadInput();
		replayFPS = Replay::rpy.GetReplayFPS();

		if(nowInput == 0xffff)
		{
			replayend = true;
//			scene = S1;
			clearPrep();
			GameInput::SetKey(0, KSI_PAUSE);
			GameInput::SetKey(1, KSI_PAUSE);
		}
		else
		{
			GameInput::SetNowInput(nowInput);

		}
	}
	active = true;
}