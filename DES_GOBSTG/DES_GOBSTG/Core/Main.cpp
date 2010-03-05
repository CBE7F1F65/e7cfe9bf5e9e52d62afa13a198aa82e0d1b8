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

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);
	
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_GFXRESTOREFUNC, GfxRestoreFunc);

	Export::clientInitial(true);

	if(hge->System_Initiate())
	{
		Export::clientAfterInitial();
		gametime = 0;
		Process::mp.state = STATE_INIT;
		hge->System_Start();
	}

	//
	Process::mp.Release();

//	hge->System_Shutdown();
	hge->Release();
	
	return 0;
}