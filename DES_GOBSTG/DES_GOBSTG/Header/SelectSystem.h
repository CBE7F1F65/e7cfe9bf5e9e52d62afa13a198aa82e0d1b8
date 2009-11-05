#ifndef _SELECTSYSTEM_H
#define _SELECTSYSTEM_H

#include "Selector.h"

#define SELSYS_DEFAULTMAXTIME	8

class SelectSystem
{
public:
	SelectSystem();
	~SelectSystem();

	static void Init();
	static void ClearAll();
	Selector * BuildSelector(BYTE ID, int siID, float cenx, float ceny,
		float hscale = 1, float vscale = 0,
		BYTE flag = SEL_NULL);
	void Clear();
	void Setup(int nselect, int select, BYTE keyminus, BYTE keyplus, BYTE keyok, BYTE keycancel, BYTE pushid, int maxtime=SELSYS_DEFAULTMAXTIME);
	bool SetPageNumber(BYTE nPageNum, float fadebegin, float offset, int initshift=0, int shiftangle=9000);
	void SetAction(BYTE typeflag, float xadj, float yadj);

	bool Confirm(BYTE keyminus, BYTE keyplus, BYTE keyok, BYTE keycancel, BYTE pushid, float cenx=M_ACTIVECLIENT_CENTER_X, float ceny=M_ACTIVECLIENT_CENTER_Y, bool settrue=false);

	void shift(int nshift);
	void action();
	void Render();

	Selector * GetPointer(int index);

	void matchSelect();

public:
	seladj	adj[SEL_STATEMAX];

	int nselect;
	int select;

	int sellock;
	bool complete;
	bool plus;

	int nPageNum;
	float fadebegin;
	float offset;
	int shiftangle;
	int firstID;
	int lastID;

	bool confirminit;

	BYTE keyplus;
	BYTE keyminus;
	BYTE keyok;
	BYTE keycancel;
	BYTE pushid;

	list<Selector>sel;
};

extern SelectSystem selsys[SELSYSTEMMAX];

#endif