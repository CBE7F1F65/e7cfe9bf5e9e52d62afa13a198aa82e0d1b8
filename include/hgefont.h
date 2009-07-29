/*
** Haaf's Game Engine 1.7
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hgeFont helper class header
*/


#ifndef HGEFONT_H
#define HGEFONT_H


#include "hge.h"
#include "hgesprite.h"


#define HGETEXT_LEFT		0
#define HGETEXT_RIGHT		1
#define HGETEXT_CENTER		2
#define HGETEXT_HORZMASK	0x03

#define HGETEXT_TOP			0
#define HGETEXT_BOTTOM		4
#define HGETEXT_MIDDLE		8
#define HGETEXT_VERTMASK	0x0C

/*
** HGE Font class
*/
class hgeFont
{
public:
	hgeFont();
	hgeFont(const char *filename, bool bMipmap=false);
	~hgeFont();

	void		Render(float x, float y, int align, const char *string);
	void		printf(float x, float y, int align, const char *format, ...);
	void		printfb(float x, float y, float w, float h, int align, const char *format, ...);

	void		SetColor(DWORD col){col0 = col1 = col2 = col3 = col;};
	void		SetColor(DWORD col0, DWORD col1, DWORD col2, DWORD col3);
	void		SetZ(float z);
	void		SetBlendMode(int blend);
	void		SetScale(float scale) {fScale=scale;}
	void		SetProportion(float prop) { fProportion=prop; }
	void		SetRotation(float rot) {fRot=rot;}
	void		SetTracking(float tracking) {fTracking=tracking;}
	void		SetSpacing(float spacing) {fSpacing=spacing;}

	DWORD		GetColor(int i=0);
	float		GetZ() const {return fZ;}
	int			GetBlendMode() const {return nBlend;}
	float		GetScale() const {return fScale;}
	float		GetProportion() const { return fProportion; }
	float		GetRotation() const {return fRot;}
	float		GetTracking() const {return fTracking;}
	float		GetSpacing() const {return fSpacing;}

	void		ChangeSprite(BYTE chr, HTEXTURE tex, float tex_x, float tex_y, float tex_w, float tex_h, float pre_a=-1, float post_c=-1);
	void		ChangeSprite(BYTE chr, hgeSprite * sprite, float pre_a=-1, float post_c=-1);
	hgeSprite*	GetSprite(BYTE chr) const { return letters[chr]; }
	float		GetPreWidth(BYTE chr) const { return pre[chr]; }
	float		GetPostWidth(BYTE chr) const { return post[chr]; }
	float		GetHeight() const { return fHeight; }
	float		GetStringWidth(const char *string, bool bMultiline=true) const;

private:
	hgeFont(const hgeFont &fnt);
	hgeFont&	operator= (const hgeFont &fnt);

	char*		_get_line(char *file, char *line);
	void		_FontInit();

	static HGE	*hge;

	static char	buffer[1024];

	HTEXTURE	hTexture;
public:
	hgeSprite*	letters[256];
	DWORD		col0, col1, col2, col3;
private:
	float		pre[256];
	float		post[256];
	float		fHeight;
	float		fScale;
	float		fProportion;
	float		fRot;
	float		fTracking;
	float		fSpacing;

//	DWORD		dwCol;
	float		fZ;
	int			nBlend;
};


#endif

