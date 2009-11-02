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

class Fontsys
{
public:
	Fontsys();
	~Fontsys();

	static void Init();
	static void HeatUp();
	static void FocusChanged();
	static void Release();

	void SignUp(const char * text = NULL, HD3DFONT font=NULL);
	void SignOff();
	void Render(float x, float y, DWORD ucol, DWORD dcol, float shadow = 0, float hext = 0, float vext = 0);

	static int strTranslate(char * dtext, const char * stext);

public:
	char text[M_STRMAX];
	HD3DFONT usingfont;
	hgeQuad quad;
	HTARGET tar;
	int lines;

	static list<Fontsys *> fontsys;
	static HD3DFONT font;
};

#endif