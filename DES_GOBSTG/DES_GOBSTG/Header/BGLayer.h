#ifndef _BGLAYER_H
#define _BGLAYER_H

#include "MainDependency.h"
#include "Const.h"
#include "BObject.h"

#define BG_NONE			0x00

#define BG_FLAGMASK		0xf0

#define BG_FLASHFLAG	0x10
#define BG_WHITEFLASH	0x10
#define BG_REDFLASH		0x11
#define BG_YELLOWFLASH	0x12
#define BGMT_FLASH		0x20

#define BG_OUTFLAG		0x20
#define BG_WHITEOUT		0x20
#define BG_REDOUT		0x21
#define BGMT_OUT		0x80

#define BG_FADEFLAG		0x40
#define BG_FADEIN		0x40
#define BG_FADEINHALF	0x41
#define BG_FADEOUT		0x42
#define BGMT_FADE		0x40

#define BG_LIGHTFLAG		0x80
#define BG_LIGHTUP			0x80
#define BG_LIGHTRED			0x81
#define BG_LIGHTUPNORMAL	0x82
#define BGMT_LIGHT			0x40

#define FG_PAUSEFLAG	0xf0
#define FG_PAUSEIN		0xf0
#define FG_PAUSEOUT		0xf1
#define FGMT_PAUSE		0x18

#define UBGID_BGMASK		UBGLAYERMAX - 2
#define UBGID_FGPAUSE		UBGLAYERMAX - 1

struct BGLayerSet
{
	DWORD timer;
	DWORD quittime;
	WORD sID;
};

#define BGLAYERSET_NONE	0

class BGLayer : public BObject
{
public:
	BGLayer();
	virtual ~BGLayer();

	static void Init();
	static void KillOtherLayer();
	static void Action(bool active);
	static void RenderBG();
	static void RenderFG();

	void Render();
	void valueSet(HTEXTURE * tex, int siID, float x, float y, float z, float w, float h, int rotx, int roty, int rotz, float paral, float speed = 0, int angle = 9000, bool move = false, bool rotate = false, DWORD col = 0xffffffff);
	void valueSet(HTEXTURE * tex, int siID, float cenx, float ceny, float width, float height, DWORD col = 0xffffffff);
	void valueSetByName(HTEXTURE * tex, const char * spritename, float cenx, float ceny, float width=-1, float height=-1, DWORD col = 0xffffffff);
	void texRectSet(float texx, float texy, float texw, float texh);
	void rectSet(float x, float y, float z, float w, float h, int rotx, int roty, int rotz);
	void zSet(float z0, float z1, float z2, float z3);
	void scaleSet(float hscale, float vscale);
	void colorSet(DWORD col0, DWORD col1, DWORD col2, DWORD col3);
	void moveSet(bool move, bool rotate);
	void parallelogram(float paral);
	void vertexSet(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
	void SetFlag(BYTE flag, int maxtime=-1);
	void SetBlend(int blend);

	void action();

public:
//	hgeQuad	quad;
	hgeSprite * sprite;
	DWORD	ocol[4];
	DWORD	acol[4];
	bool	move;			//move vertex
	bool	rotate;			//set move to enable
	float	width;
	float	height;
	int		tw;
	int		th;
	BYTE	flag;
	BYTE	changetimer;
	BYTE	mtimer;

	static BGLayerSet set[BGLAYERSETMAX];
	static WORD setindex;

	static BGLayer ubg[UBGLAYERMAX];
};

#endif