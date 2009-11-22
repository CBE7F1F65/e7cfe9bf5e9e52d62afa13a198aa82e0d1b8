#include "vld.h"

#include "Process.h"
#include "Fontsys.h"

#include "Main.h"

char strdesc[STRINGDESCMAX][M_STRMAX*2];

HGE *hge = NULL;

int time = 0;

DWORD strdescIndex = 0;

bool RenderFunc()
{

	mp.render();
	
	return false;
}

bool FrameFunc()
{
	mp.SyncInput();
	if (hge->Input_GetDIKey(KS_ESCAPE_MP))
		return true;
	if(hge->Input_GetDIKey(KS_CAPTURE_MP, DIKEY_DOWN))
	{
		mp.SnapShot();
	}

	if(mp.frame() == PQUIT)
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
		mp.state = STATE_INIT;
		hge->System_Start();
	}

	//
	mp.Release();

//	hge->System_Shutdown();
	hge->Release();
	
	return 0;
}