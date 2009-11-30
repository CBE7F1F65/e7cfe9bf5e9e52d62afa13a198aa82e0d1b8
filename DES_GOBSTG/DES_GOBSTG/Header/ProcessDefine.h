#ifndef _PROCESSDEFINE_H
#define _PROCESSDEFINE_H

#define KS_UP		keyKS[0].keyUp
#define KS_DOWN		keyKS[0].keyDown
#define KS_LEFT		keyKS[0].keyLeft
#define KS_RIGHT	keyKS[0].keyRight
#define KS_FIRE		keyKS[0].keyFire
#define KS_QUICK	keyKS[0].keyQuick
#define KS_SLOW		keyKS[0].keySlow
#define KS_DRAIN	keyKS[0].keyDrain
#define KS_PAUSE	keyKS[0].keyPause
#define KS_SKIP		keyKS[0].keySkip
#define KS_ENTER	keyKS[0].keyEnter
#define KS_ESCAPE	keyKS[0].keyEscape
#define KS_CAPTURE	keyKS[0].keyCapture

#define KS_UP_MP		mp.keyKS[0].keyUp
#define KS_DOWN_MP		mp.keyKS[0].keyDown
#define KS_LEFT_MP		mp.keyKS[0].keyLeft
#define KS_RIGHT_MP		mp.keyKS[0].keyRight
#define KS_FIRE_MP		mp.keyKS[0].keyFire
#define KS_QUICK_MP		mp.keyKS[0].keyQuick
#define KS_SLOW_MP		mp.keyKS[0].keySlow
#define KS_DRAIN_MP		mp.keyKS[0].keyDrain
#define KS_PAUSE_MP		mp.keyKS[0].keyPause
#define KS_SKIP_MP		mp.keyKS[0].keySkip
#define KS_ENTER_MP		mp.keyKS[0].keyEnter
#define KS_ESCAPE_MP	mp.keyKS[0].keyEscape
#define KS_CAPTURE_MP	mp.keyKS[0].keyCapture

#define KS_UP_(X)		keyKS[(X)].keyUp
#define KS_DOWN_(X)		keyKS[(X)].keyDown
#define KS_LEFT_(X)		keyKS[(X)].keyLeft
#define KS_RIGHT_(X)	keyKS[(X)].keyRight
#define KS_FIRE_(X)		keyKS[(X)].keyFire
#define KS_QUICK_(X)	keyKS[(X)].keyQuick
#define KS_SLOW_(X)		keyKS[(X)].keySlow
#define KS_DRAIN_(X)	keyKS[(X)].keyDrain
#define KS_PAUSE_(X)	keyKS[(X)].keyPause
#define KS_SKIP_(X)		keyKS[(X)].keySkip
#define KS_ENTER_(X)	keyKS[(X)].keyEnter
#define KS_ESCAPE_(X)	keyKS[(X)].keyEscape
#define KS_CAPTURE_(X)	keyKS[(X)].keyCapture

#define KS_UP_MP_(X)		mp.keyKS[X].keyUp
#define KS_DOWN_MP_(X)		mp.keyKS[(X)].keyDown
#define KS_LEFT_MP_(X)		mp.keyKS[(X)].keyLeft
#define KS_RIGHT_MP_(X)		mp.keyKS[(X)].keyRight
#define KS_FIRE_MP_(X)		mp.keyKS[(X)].keyFire
#define KS_QUICK_MP_(X)		mp.keyKS[(X)].keyQuick
#define KS_SLOW_MP_(X)		mp.keyKS[(X)].keySlow
#define KS_DRAIN_MP_(X)		mp.keyKS[(X)].keyDrain
#define KS_PAUSE_MP_(X)		mp.keyKS[(X)].keyPause
#define KS_SKIP_MP_(X)		mp.keyKS[(X)].keySkip
#define KS_ENTER_MP_(X)		mp.keyKS[(X)].keyEnter
#define KS_ESCAPE_MP_(X)	mp.keyKS[(X)].keyEscape
#define KS_CAPTURE_MP_(X)	mp.keyKS[(X)].keyCapture

#define JS_FIRE				keyJS[0].joyFire
#define JS_QUICK			keyJS[0].joyQuick
#define JS_SLOW				keyJS[0].joySlow
#define JS_DRAIN			keyJS[0].joyDrain
#define JS_PAUSE			keyJS[0].joyPause
#define JS_DEBUG_SPEEDUP	keyJS[0].debug_joySpeedUp

#define JS_FIRE_(X)				keyJS[X].joyFire
#define JS_QUICK_(X)			keyJS[X].joyQuick
#define JS_SLOW_(X)				keyJS[X].joySlow
#define JS_DRAIN_(X)			keyJS[X].joyDrain
#define JS_PAUSE_(X)			keyJS[X].joyPause
#define JS_DEBUG_SPEEDUP_(X)	keyJS[X].debug_joySpeedUp

//process return value
enum
{
	PQUIT,
	PGO,
	POK,
	PBACK,
	PTURN,
	PSKIP
};
//state indicator
enum
{
	STATE_START,
	STATE_PAUSE,
	STATE_CONTINUE,
	STATE_CLEAR,
	STATE_ENDING,
	STATE_TITLE,
	STATE_MATCH_SELECT,
	STATE_PLAYER_SELECT,
	STATE_SCENE_SELECT,
	STATE_OVER,
	STATE_SPELL,
	STATE_REPLAY,
	STATE_RESULT,
	STATE_OPTION,
	STATE_MUSIC,
	STATE_INIT,
};
//errorcode
enum
{
	PROC_ERROR_NONE,
	PROC_ERROR_INIFILE,
	PROC_ERROR_RESOURCE,
	PROC_ERROR_SCRIPT,
	PROC_ERROR_TRANSLATE,
	PROC_ERROR_DATA,
	PROC_ERROR_PACKAGE,
	PROC_ERROR_SOUND,
	PROC_ERROR_FONT,
	PROC_ERROR_TEXTURE
};

#define FRAME_STOPFLAG_WORLDSHAKE	0x0001
#define FRAME_STOPFLAG_PLAYER_0		0x0002
#define FRAME_STOPFLAG_PLAYER_1		0x0004
#define FRAME_STOPFLAG_PLAYERBULLET	0x0008
#define FRAME_STOPFLAG_ENEMY		0x0010
#define FRAME_STOPFLAG_GHOST		0x0020
#define FRAME_STOPFLAG_BULLET		0x0040
#define FRAME_STOPFLAG_BEAM			0x0080
#define FRAME_STOPFLAG_ITEM			0x0100
#define FRAME_STOPFLAG_LAYER		0x0200
#define FRAME_STOPFLAG_EFFECTSYS	0x0400

#define FRAME_STOPFLAG_PLAYERSET	(FRAME_STOPFLAG_WORLDSHAKE|FRAME_STOPFLAG_PLAYER_0|FRAME_STOPFLAG_PLAYER_1|FRAME_STOPFLAG_PLAYERBULLET|FRAME_STOPFLAG_LAYER)
#define FRAME_STOPFLAG_ENEMYSET		(FRAME_STOPFLAG_WORLDSHAKE|FRAME_STOPFLAG_ENEMY|FRAME_STOPFLAG_GHOST|FRAME_STOPFLAG_BULLET|FRAME_STOPFLAG_BEAM|FRAME_STOPFLAG_ITEM)

#endif