#include "vld.h"

#include "Process.h"
#include "Fontsys.h"

#include "Main.h"

HGE *hge = NULL;

int time = 0;

bool RenderFunc()
{

	Process::mp.render();
	
	return false;
}

bool FrameFunc()
{
	Process::mp.SyncInput();
	if (hge->Input_GetDIKey(KS_ESCAPE_MP))
		return true;
	if(hge->Input_GetDIKey(KS_CAPTURE_MP, DIKEY_DOWN))
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
		time = 0;
		Process::mp.state = STATE_INIT;
		hge->System_Start();
	}

	//
	Process::mp.Release();

//	hge->System_Shutdown();
	hge->Release();
	
	return 0;
}