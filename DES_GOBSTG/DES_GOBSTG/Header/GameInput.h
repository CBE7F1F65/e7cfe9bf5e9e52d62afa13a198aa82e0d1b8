#ifndef _GAMEINPUT_H
#define _GAMEINPUT_H

#include "MainDependency.h"

#define GAMEINPUTKEYMAX	13
#define GAMEINPUTJOYMAX	5
#define GAMEACTIVEINPUTMAX	9

#define KSI_UP		0
#define KSI_DOWN	1
#define KSI_LEFT	2
#define KSI_RIGHT	3
#define KSI_FIRE	4
#define KSI_QUICK	5
#define KSI_SLOW	6
#define KSI_DRAIN	7
#define KSI_PAUSE	8
#define KSI_SKIP	9
#define KSI_ENTER	10
#define KSI_ESCAPE	11
#define KSI_CAPTURE	12

class GameInput
{
public:
	GameInput();
	~GameInput();
	static bool InitInput(HGE * hge);
	static bool UpdateInput();
	WORD UpdateActiveInput(bool copylast=false);
	bool getKey(int ksi, int type=DIKEY_PRESSED, bool active=true);
	void setKey(int ksi, bool set=true, bool active=true);
	static bool GetKey(BYTE playerindex, int ksi, int type=DIKEY_PRESSED, bool active=true);
	static void SetKey(BYTE playerindex, int ksi, bool set=true, bool active=true);
public:

	union{
		struct{
			int keyUp;
			int keyDown;
			int keyLeft;
			int keyRight;
			int keyFire;
			int keyQuick;
			int keySlow;
			int keyDrain;
			int keyPause;
			int keySkip;
			int keyEnter;
			int keyEscape;
			int keyCapture;
		}		keyKS;
		int		keyKey[GAMEINPUTKEYMAX];
	};
	union{
		struct{
			int	joyFire;
			int	joyQuick;
			int	joySlow;
			int	joyDrain;
			int	joyPause;
			int debug_joySpeedUp;
		}		keyJS;
		int		joyKey[GAMEINPUTJOYMAX];
	};

	WORD activeInput;
	WORD lastActiveInput;
	WORD input;
	WORD lastInput;

	static HGE * hge;
	static GameInput gameinput[M_PL_MATCHMAXPLAYER];
};

#endif