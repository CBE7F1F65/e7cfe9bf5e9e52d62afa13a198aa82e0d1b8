#ifndef _PROCESS_H
#define _PROCESS_H

#include "Main.h"
#include "Export.h"
#include "Const.h"
#include "ProcessDefine.h"

class Process
{
public:
	Process();
	virtual ~Process();

	void	Release();

	bool	reload();

	int		getInput();
	char	getInputNowChar(bool wide);

	int		processStart();
	int		processPause();
	int		processContinue();
	int		processClear();
	int		processEnding();
	int		processTitle();
	int		processMatchSelect();
	int		processPlayerSelect();
	int		processSceneSelect();
	int		processOver();
	int		processSpell();
	int		processReplay();
	int		processResult();
	int		processOption();
	int		processMusic();
	int		processInit();
	int		processPreInitial();

	int		frame();
	int		render();
	void	_Render(BYTE renderflag=M_RENDER_NULL);
	void	_RenderTar();
	int		renderInit();

	void	startPrep(bool callinit = true);
	void	clearPrep(bool bclearkey = true);

	void	frameStart();
	void	frameEnd();

	void	playSE(const char * sample_name,int pan = 0);
	void	musicChange(BYTE ID, bool force = false);
	void	musicSlide(float slidetime, int tovol = 0, int pan = -101, float pitch = -1);

	void	SnapShot();

	void	SetShake(BYTE round, bool force=false);
	void	WorldShake();

	void	SyncInput();
	void	SetState(int state, int time = 0);
	void	SetReturnValue(int retval);

	int		AccessIP();
	bool	SetLatency(int latency);
	void	SetMatchMode(BYTE mode);
	BYTE	GetMatchMode();
	bool	IsInGame();

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
			int keyCharge;
			int keyPause;
			int keySkip;
			int keyEnter;
			int keyEscape;
			int keyCapture;
		}		keyKS[M_PL_MATCHMAXPLAYER];
		int		keyKey[M_PL_MATCHMAXPLAYER][13];
	};
	union{
		struct{
			int	joyFire;
			int	joyQuick;
			int	joySlow;
			int	joyCharge;
			int	joyPause;
			int debug_joySpeedUp;
		}		keyJS[M_PL_MATCHMAXPLAYER];
		int		joyKey[M_PL_MATCHMAXPLAYER][5];
	};

	//texture
	HTEXTURE	tex[TEXMAX];

	//read ini
	char	username[RPYINFO_USERNAMEMAX];
	int		screenmode;
	int		bgmvol;
	int		sevol;
	int		defaultdifflv;

	//replay
	char	rpyfilename[M_STRITOAMAX];
	DWORD	seed;
	int		framecounter;
	int		frameskip;
	int		renderskip;
	bool	replaymode;
	bool	replayend;
	//playtime
	LONGLONG	playtimeStart;
	bool		playing;
	//music
	HSTREAM		stream;
	HCHANNEL	channel;
	int			musicID;
	hgeChannelSyncInfo channelsyncinfo;

	//shake
	int worldshaketimer;
	BYTE round;

	//main
	DWORD lasttime;
	DWORD alltime;
	bool	active;

	DWORD	stopflag;
	int		stoptimer;

	int retvalue;

	DWORD	scene;
	DWORD	startscene;
	DWORD	endscene;
	//practice
	bool	practicemode;
	bool	spellmode;
	//pause return
	bool	pauseinit;
	//Replayinfo
	float	replayFPS;
	//error
	int	errorcode;
	//fps
	int	objcount;

	//indicator
	BYTE	nowdifflv;
	BYTE	mainchara;
	BYTE	subchara_1;
	BYTE	subchara_2;
	BYTE	titleselect;
	BYTE	state;
	//input
	WORD	nowInput;
	WORD	saveInput;

	//Init
	HTEXTURE	texInit;

	//
	int		latency;
	BYTE	matchmode;
	//
	HTARGET	rendertar[M_PL_MATCHMAXPLAYER];
	hgeSprite * sprendertar[M_PL_MATCHMAXPLAYER];
};

extern Process mp;

extern int randi;
extern BYTE tari;

extern replayFrame replayframe[M_SAVEINPUTMAX];
extern DWORD replayIndex;

extern float worldx;
extern float worldy;
extern float worldz;

#endif