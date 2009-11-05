#ifndef _FONTSYS_H
#define _FONTSYS_H

#include "MainDependency.h"
#include "Const.h"

#define FONTSYS_CHATUSE			FONTSYSMAX-2
#define FONTSYS_SPELLNAMEUSE	FONTSYSMAX-1

#define FONTSYS_TRANSCHAR		'|'
#define FONTSYS_CONTROLCHAR		'E'
#define FONTSYS_CONTROLSTR		"|E"

#define FONTSYS_TARGETWIDTH		M_CLIENT_WIDTH
#define FONTSYS_TARGETHEIGHT	(M_CLIENT_HEIGHT/2)

#define FONTSYS_CHATTEXTWIDTH	300
#define FONTSYS_CHATTEXTHEIGHT	80

#define FONTSYS_DEFAULT_SHADOW	0.4f

class Fontsys
{
public:
	Fontsys();
	~Fontsys();

	static void Init(HD3DFONT font = NULL);
	static void HeatUp();
	static void FocusChanged();
	static void Release();

	void SignUp(const char * text = NULL, HD3DFONT font=NULL);
	list<Fontsys *>::iterator SignOff();
	void ReleaseTargetAndSprite();
	void Render(float x, float y, DWORD ucol, DWORD dcol, float shadow = FONTSYS_DEFAULT_SHADOW, float hscale = 1, float vscale = 0, BYTE alignflag=HGETEXT_CENTER|HGETEXT_MIDDLE);

	static int strTranslate(char * dtext, const char * stext, int * maxchar);

public:
	char text[M_STRMAX];
	HD3DFONT usingfont;
//	hgeQuad quad;
	hgeSprite * sprite;
	HTARGET tar;
	int lines;
	int maxcharinline;

	static list<Fontsys *> fontsys;
	static HD3DFONT font;
};

#endif