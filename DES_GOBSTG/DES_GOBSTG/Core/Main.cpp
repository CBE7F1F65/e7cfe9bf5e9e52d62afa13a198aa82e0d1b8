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
		return true;
	if(GameInput::GetKey(0, KSI_CAPTURE, DIKEY_DOWN))
	{
		Process::mp.SnapShot();
	}

	if(Process::mp.frame() == PQUIT)
		return true;

	return false;
}

bool GfxRestoreFunc()
{
	return Fontsys::GfxRestore();
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
	//
	return iret;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_GFXRESTOREFUNC, GfxRestoreFunc);

	Process::mp.usingkaillera = true;
	if (Process::mp.usingkaillera)
	{
		int ret = kailleraInit();
		kailleraInfos ki;
		ZeroMemory(&ki, sizeof(kailleraInfos));
		ki.appName = "";
		char * GameList = GAME_TITLE "\x00" "\x00";
		ki.gameList =GameList;
		ki.chatReceivedCallback = NULL;
		ki.clientDroppedCallback = NULL;
		ki.moreInfosCallback = NULL;
		ki.gameCallback = KailleraGameCallback;
		ret = kailleraSetInfos(&ki);
		ret = kailleraSelectServerDialog(0);
		Process::mp.ReleaseKaillera();
	}
	else
	{
		GameStart();
	}

	//
	if (Process::mp.usingkaillera)
	{
		kailleraShutdown();
	}

	Process::mp.Release();

	//	hge->System_Shutdown();
	hge->Release();
	
	return 0;
}