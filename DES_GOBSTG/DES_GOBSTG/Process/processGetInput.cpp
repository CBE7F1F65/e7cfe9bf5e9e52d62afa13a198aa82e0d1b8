#include "Process.h"
#include "GameInput.h"

void Process::SyncInput()
{
	GameInput::SyncControlInput();
}

int Process::getInput()
{
	GameInput::UpdateInput();
	if (replaymode && !replayend && (state == STATE_START || state == STATE_CLEAR))
	{
		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
		{
			GameInput::SetKey(i, KSI_UP, false);
			GameInput::SetKey(i, KSI_DOWN, false);
			GameInput::SetKey(i, KSI_LEFT, false);
			GameInput::SetKey(i, KSI_RIGHT, false);
			GameInput::SetKey(i, KSI_FIRE, false);
			GameInput::SetKey(i, KSI_QUICK, false);
			GameInput::SetKey(i, KSI_DRAIN, false);
			GameInput::SetKey(i, KSI_SLOW, false);
		}
	}

	if (state != STATE_START && state != STATE_PLAYER_SELECT)
	{
		GameInput::SyncForActiveInput();
	}

	return PGO;
}