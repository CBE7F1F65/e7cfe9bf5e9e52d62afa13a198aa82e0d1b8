#include <vld.h>

#include "../Header/Process.h"
#include "../Header/Fontsys.h"

#include "../Header/Main.h"
#include "../Header/GameInput.h"

HGE *hge = NULL;

int gametime = 0;

bool RenderFunc()
{

	Process::mp.render();
	
	return false;
}

bool FrameFunc()
{
	Process::mp.SyncInput();
	if (GameInput::GetKey(0, KSI_ESCAPE))
	{
		return true;
	}
	if(GameInput::GetKey(0, KSI_CAPTURE, DIKEY_DOWN))
	{
		Process::mp.SnapShot();
	}

	if(Process::mp.frame() == PQUIT)
	{
		return true;
	}

	return false;
}

bool GfxRestoreFunc()
{
	return Fontsys::GfxRestore();
}

bool ExitFunc()
{
	if (Process::mp.usingkaillera)
	{
		kailleraEndGame();
	}
	return true;
}

int GameStart(int seed=0)
{
	Export::clientInitial(true);

	if(hge->System_Initiate())
	{
		Export::clientAfterInitial();

		gametime = 0;
		Process::mp.state = STATE_INIT;
		if (!seed)
		{
			seed = timeGetTime();
		}
		Process::mp.seed = seed;
		srandt(Process::mp.seed);
		hge->Random_Seed(Process::mp.seed);

		hge->System_Start();
	}
	return 0;
}

int WINAPI KailleraGameCallback(char *game, int player, int numplayers)
{
	int seed = timeGetTime();
	while (!seed)
	{
		seed = timeGetTime();
	}
	int iret = Process::mp.InitKaillera(game, player, numplayers, &seed);

	if (!iret)
	{
		return GameStart(seed);
	}
	MessageBox(NULL, "Game Version Error", "Error", MB_OK);
	//
	return iret;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR lpCmdLine, int)
{
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_GFXRESTOREFUNC, GfxRestoreFunc);
	hge->System_SetState(HGE_EXITFUNC, ExitFunc);

	if (strlen(lpCmdLine))
	{
		Process::mp.usingkaillera = true;
	}
	if (Process::mp.usingkaillera)
	{
		int ret = kailleraInit();
		kailleraInfos ki;
		ZeroMemory(&ki, sizeof(kailleraInfos));
		ki.appName = GAME_TITLE_STR;
		char * GameList = GAME_TITLE_STR "\x00" "\x00";
		ki.gameList =GameList;
		ki.chatReceivedCallback = NULL;
		ki.clientDroppedCallback = NULL;
		ki.moreInfosCallback = NULL;
		ki.gameCallback = KailleraGameCallback;
		ret = kailleraSetInfos(&ki);
		if (ret >= 0)
		{
			ret = kailleraSelectServerDialog(0);
		}
		Process::mp.ReleaseKaillera();
	}
	else
	{
		GameStart();
	}

	//
	Process::mp.Release();
	//	hge->System_Shutdown();
	hge->Release();
	if (Process::mp.usingkaillera)
	{
		kailleraShutdown();
	}


	
	return 0;
}