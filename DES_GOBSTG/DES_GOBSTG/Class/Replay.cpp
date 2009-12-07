#include "Replay.h"
#include "Process.h"
#include "Player.h"
#include "Data.h"
#include "BResource.h"
#include "Player.h"

Replay Replay::rpy;

Replay::Replay()
{
	replayIndex = 0;
	ZeroMemory(&replayframe, sizeof(replayFrame) * M_SAVEINPUTMAX);
	ZeroMemory(&rpyinfo, sizeof(replayInfo));
}

Replay::~Replay()
{
}

void Replay::Free(char * filename)
{
	if (filename)
	{
		Export::rpyFree(filename);
	}
}

void Replay::Fill()
{
	SYSTEMTIME systime;
	GetLocalTime(&systime);

//	rpyinfo.modeflag = (Process::mp.spellmode?M_RPYMODE_SPELL:0)|(Process::mp.practicemode?M_RPYMODE_PRACTICE:0);

	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		rpyinfo.usingchara[i][0] = Player::p[i].ID;
		rpyinfo.usingchara[i][1] = Player::p[i].ID_sub_1;
		rpyinfo.usingchara[i][2] = Player::p[i].ID_sub_2;
		rpyinfo.initlife[i] = Player::p[i].initlife;
	}

	rpyinfo.scene = Process::mp.scene;
	rpyinfo.alltime = Player::alltime;
	rpyinfo.year = systime.wYear;
	rpyinfo.month = systime.wMonth;
	rpyinfo.day = systime.wDay;
	rpyinfo.hour = systime.wHour;
	rpyinfo.minute = systime.wMinute;

	strcpy(rpyinfo.username, Process::mp.username);

	rpyinfo.lost = Player::lostStack / Process::mp.framecounter;
	rpyinfo.offset = replayIndex;
}

void Replay::partFill(BYTE part)
{
	if (part < RPYPARTMAX)
	{
		partinfo[part].offset = replayIndex + 1;
		partinfo[part].seed = Process::mp.seed;
	}
	else
		part = 0;
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		partinfo[part].nowID[i] = Player::p[i].nowID;
	}
}

bool Replay::Check(char * filename)
{
	BYTE * content;
	bool ret = false;

	char treplayfilename[M_PATHMAX];
	strcpy(treplayfilename, BResource::res.resdata.replayfoldername);
	strcat(treplayfilename, filename);
	hge->Resource_AttachPack(treplayfilename, Data::data.password ^ REPLAYPASSWORD_XORMAGICNUM);

	content = hge->Resource_Load(hge->Resource_GetPackFirstFileName(treplayfilename));
	if(content)
	{
		if(strcmp((char *)(content + RPYOFFSET_SIGNATURE), BResource::res.resdata.replaysignature11))
			goto exit;
		if(*(DWORD *)(content + RPYOFFSET_VERSION) != GAME_VERSION)
			goto exit;
		if(strcmp((char *)(content + RPYOFFSET_COMPLETESIGN), BResource::res.resdata.replaycompletesign3))
			goto exit;
		ret = true;
	}
exit:
	hge->Resource_Free(content);
	return ret;
}

void Replay::WriteInput(WORD nowinput)
{
	replayIndex++;
	replayframe[replayIndex].input = nowinput;
	Export::rpySetBias(&(replayframe[replayIndex]));
}

WORD Replay::ReadInput()
{
	replayIndex++;
	return replayframe[replayIndex].input;
}

float Replay::GetReplayFPS()
{
	return Export::rpyGetReplayFPS(replayframe[replayIndex]);
}

void Replay::InitReplayIndex(bool replaymode, BYTE part)
{
	if (replaymode)
	{
		replayIndex = rpy.partinfo[part].offset - 1;
	}
	else
	{
		replayIndex = 0;
	}
}

bool Replay::Load(char * filename, bool getInput)
{
	bool ret = false;
	if(Check(filename))
	{
        char treplayfilename[M_PATHMAX];
		strcpy(treplayfilename, BResource::res.resdata.replayfoldername);
		strcat(treplayfilename, filename);
		ret = Export::rpyLoad(treplayfilename, &rpyinfo, partinfo, getInput ? replayframe : NULL);
		if (getInput)
		{
			replayIndex = 0;
		}
	}
	return ret;
}

void Replay::Save(char * filename)
{
	if(!filename)
		return;

	char buffer[M_STRITOAMAX];

	DWORD _size = RPYOFFSET_INPUTDATA + (replayIndex + 1) * RPYSIZE_FRAME;
	BYTE * _rpydata = (BYTE *)malloc(_size);
	DWORD tdw;
	memcpy(_rpydata + RPYOFFSET_SIGNATURE, BResource::res.resdata.replaysignature11, RPYSIZE_SIGNATURE);
	tdw = GAME_VERSION;
	memcpy(_rpydata + RPYOFFSET_VERSION, &tdw, RPYSIZE_VERSION);
	memcpy(_rpydata + RPYOFFSET_COMPLETESIGN, BResource::res.resdata.replaycompletesign3, RPYSIZE_COMPLETESIGN);
	memcpy(_rpydata + RPYOFFSET_TAG, BResource::res.resdata.replaytag3, RPYSIZE_TAG);
	tdw = RPYOFFSET_PARTINFO;
	memcpy(_rpydata + RPYOFFSET_INFOOFFSET, &tdw, RPYSIZE_INFOOFFSET);
	strcpy(buffer, "");
	memcpy(_rpydata + RPYOFFSET_APPEND, buffer, RPYSIZE_APPEND);
	memcpy(_rpydata + RPYOFFSET_RPYINFO, &rpyinfo, RPYSIZE_RPYINFO);
	memcpy(_rpydata + RPYOFFSET_PARTINFO, partinfo, RPYSIZE_PARTINFO * RPYPARTMAX);
	memcpy(_rpydata + RPYOFFSET_INPUTDATA, replayframe, replayIndex * RPYSIZE_FRAME);

	replayFrame buff;
	buff.bias = 0;
	buff.input = 0xffff;
	memcpy(_rpydata + _size-sizeof(replayFrame), &buff, sizeof(replayFrame));

	char treplayfilename[M_PATHMAX];
	strcpy(treplayfilename, BResource::res.resdata.replayfoldername);
	strcat(treplayfilename, filename);

	char crcfilename[M_PATHMAX];
	strcpy(crcfilename, filename);
	strcat(crcfilename, itoa(hge->Resource_GetCRC(_rpydata, _size), buffer, 10));
	hgeMemoryFile memfile;
	memfile.filename = crcfilename;
	memfile.data = _rpydata;
	memfile.size = _size;

	hge->Resource_CreatePack(treplayfilename, Data::data.password ^ REPLAYPASSWORD_XORMAGICNUM, &memfile, NULL);

	free(_rpydata);
}