#include "../Header/Process.h"
#include "../Header/Fontsys.h"

#include "../Header/Main.h"
#include "../Header/GameInput.h"

#include "../Header/ConstResource.h"

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

#ifdef __IPHONE
#include "MainApplicationFunctions.h"
#endif

HGE *hge = NULL;

int gametime = 0;

bool application_lastactive = true;
bool application_active = false;

bool RenderFunc()
{

	Process::mp.render();
	
	return false;
}

#include "../Header/GameInput.h"

bool FrameFunc()
{
#ifdef __IPHONE
#endif
	
	if (!application_lastactive) {
		application_lastactive = true;
		if (Process::mp.state == STATE_START) {
			hge->Input_SetDIKey(GameInput::KS_PAUSE_(0));
//			GameInput::SetKey(0, KSI_PAUSE);
		}
	}
	
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

#if defined __IPHONE
void TouchCallback_ButtonDown(float x, float y, int ID)
{
	return Process::mp.TouchCallback_ButtonDown(x, y, ID);
}

void TouchCallback_ButtonUp(float x, float y, int ID)
{
	return Process::mp.TouchCallback_ButtonUp(x, y, ID);
}

void TouchCallback_Move(float x, float y, int ID)
{
	return Process::mp.TouchCallback_Move(x, y, ID);
}
#endif

int GameStart(int seed/*=0*/)
{
#ifdef __PSP
	initExceptionHandler();
#endif // __PSP
	Export::clientInitial( true );

	if(hge->System_Initiate())
	{
		Export::clientAfterInitial(Process::mp.screenscale);

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
#ifndef __IPHONE
		hge->System_Start();
#endif
	}
	return 0;
}

int GameEnd()
{
	//
	Process::mp.Release();
	hge->Release();
	return 0;
}

#if defined __IPHONE
int Application_Loop()
{
	if (application_active) {
		hge->System_Start();
	}
	return 0;
}

int Application_Quit()
{
	GameEnd();
	return 1;
}

void Application_SetActive(bool toactive)
{
	if (application_active != toactive) {
		application_lastactive = application_active;
		application_active = toactive;
	}
}
#endif

#if defined __WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR lpCmdLine, int)
#elif defined __PSP
int main(int argc, char* argv[])
#elif defined __IPHONE
int Application_Init()
#endif // __WIN32
{
	
	hge = hgeCreate(HGE_VERSION);
	
#if defined __IPHONE
	hge->Resource_SetPath(ResourceGetBaseDirectory());
	hge->System_SetState(HGE_LOGFILE, LOG_STR_FILENAME);
	hge->System_SetState(HGE_INIFILE, CONFIG_STR_FILENAME);
	hge->Resource_SetPath(ResourceGetAppDirectory());
	hge->System_SetState(HGE_USESOUND, false);
	hge->System_SetState(HGE_MANAGELOOP, false);
#endif

	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_GFXRESTOREFUNC, GfxRestoreFunc);
	hge->System_SetState(HGE_EXITFUNC, ExitFunc);
	
	GameStart();
#ifndef __IPHONE
	GameEnd();
#endif

	
	return 0;
}