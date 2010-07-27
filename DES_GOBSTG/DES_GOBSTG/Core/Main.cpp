#include "../Header/Process.h"
#include "../Header/Fontsys.h"

#include "../Header/Main.h"
#include "../Header/GameInput.h"

#ifdef __PSP
#include <pspkernel.h>
PSP_MODULE_INFO("h5nc", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(0);
PSP_HEAP_SIZE_KB(-256);
extern "C"
{
#include "../../include/exception.h"
};
#endif // __PSP

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
	return true;
}

bool ExitFunc()
{
	return true;
}

int GameStart(int seed=0)
{
#ifdef __PSP
	initExceptionHandler();
#endif // __PSP
	Export::clientInitial(true);

	if(hge->System_Initiate())
	{
		Export::clientAfterInitial();

		gametime = 0;
		Process::mp.state = STATE_INIT;
		if (!seed)
		{
			seed = hge->Timer_GetCurrentSystemTime();
//			seed = timeGetTime();
		}
		Process::mp.seed = seed;
		srandt(Process::mp.seed);
		hge->Random_Seed(Process::mp.seed);

		hge->System_Start();
	}
	return 0;
}

#ifdef __WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR lpCmdLine, int)
#else
int main(int argc, char* argv[])
#endif // __WIN32
{
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_GFXRESTOREFUNC, GfxRestoreFunc);
	hge->System_SetState(HGE_EXITFUNC, ExitFunc);

	GameStart();

	//
	Process::mp.Release();
	//	hge->System_Shutdown();
	hge->Release();
	
	return 0;
}