#ifndef _REPLAY_H
#define _REPLAY_H

#include "Export.h"

class Replay
{
public:
	Replay();
	~Replay();

	void Fill();
	void partFill(BYTE part);
	bool Load(char * filename, bool getInput = false);
	void Save(char * filename);
	bool Check(char * filename);

	void WriteInput(WORD nowinput);
	WORD ReadInput();
	float GetReplayFPS();
	void InitReplayIndex(bool replaymode=false, BYTE part=0);

	static void Free(char * filename);

public:
	partInfo partinfo[RPYPARTMAX];
	replayInfo rpyinfo;
	replayFrame replayframe[M_SAVEINPUTMAX];
	int replayIndex;

	static Replay rpy;
};

#endif