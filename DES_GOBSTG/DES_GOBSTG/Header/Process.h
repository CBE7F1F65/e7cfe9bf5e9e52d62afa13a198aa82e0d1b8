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
	~Process();

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

	void	SetShake(BYTE playerindex, BYTE round, bool force=false);
	void	WorldShake(DWORD stopflag);

	void	SyncInput();
	void	SetState(int state, int time = 0);
	void	SetReturnValue(int retval);

	int		AccessIP();
	bool	SetLatency(int latency);
	void	SetMatchMode(BYTE mode);
	BYTE	GetMatchMode();
	bool	IsInGame();

	void	SetStop(DWORD stopflag, int stoptimer);

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
		}		keyKS[M_PL_MATCHMAXPLAYER];
		int		keyKey[M_PL_MATCHMAXPLAYER][13];
	};
	union{
		struct{
			int	joyFire;
			int	joyQuick;
			int	joySlow;
			int	joyDrain;
			int	joyPause;
			int debug_joySpeedUp;
		}		keyJS[M_PL_MATCHMAXPLAYER];
		int		joyKey[M_PL_MATCHMAXPLAYER][6];
	};

	//texture
	HTEXTURE	tex[TEXMAX];

	//read ini
	char	username[RPYINFO_USERNAMEMAX];
	int		screenmode;
	int		bgmvol;
	int		sevol;

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
	int worldshaketimer[M_PL_MATCHMAXPLAYER];
	BYTE worldshakeround[M_PL_MATCHMAXPLAYER];
	float worldx[M_PL_MATCHMAXPLAYER];
	float worldy[M_PL_MATCHMAXPLAYER];
	float worldz[M_PL_MATCHMAXPLAYER];

	//main
	DWORD lasttime;
	DWORD alltime;
	bool	active;

	DWORD	stopflag[FRAME_STOPINFOMAX];
	int		stoptimer[FRAME_STOPINFOMAX];

	int retvalue;

	DWORD	scene;

	//pause return
	bool	pauseinit;

	//Replayinfo
	float	replayFPS;

	//error
	int	errorcode;

	//indicator
	BYTE	titleselect;
	BYTE	state;

	//Init
	HTEXTURE	texInit;

	//
	int		latency;
	BYTE	matchmode;
	//
	HTARGET	rendertar[M_PL_MATCHMAXPLAYER];
	hgeSprite * sprendertar[M_PL_MATCHMAXPLAYER];

	static Process mp;
};

#endif