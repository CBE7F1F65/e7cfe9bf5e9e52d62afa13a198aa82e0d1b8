#ifndef __NOTUSELUA
#ifndef __NOTUSEHDSS

#ifndef _EXPORT_LUA_HDSS_CALLGET_H
#define _EXPORT_LUA_HDSS_CALLGET_H

#include "../Header/Export_Lua.h"

class _HDSSCallGet
{
public:
	_HDSSCallGet();
	~_HDSSCallGet();
	static int Call_SD(LuaState * ls);
	static int Call_SDf(LuaState * ls);

	static int Call_RETURN(LuaState * ls);
	static int Call_SETSTATE(LuaState * ls);
	static int Call_SETSCENE(LuaState * ls);
	static int Call_SETTIME(LuaState * ls);
	static int Call_SETCHARA(LuaState * ls);
	static int Call_STARTPREP(LuaState * ls);
	static int Call_SETKEY(LuaState * ls);
	static int Call_SETPUSHEVENT(LuaState * ls);
	static int Call_UPDATEPUSHEVENT(LuaState * ls);
	static int Call_SAVEREPLAY(LuaState * ls);

	static int Call_SE(LuaState * ls);
	static int Call_SEOFF(LuaState * ls);
	static int Call_HSVTORGB(LuaState * ls);
	static int Call_PRINT(LuaState * ls);
	static int Call_FRONTSPRITE(LuaState * ls);
	static int Call_FADEOUTFRONTSPRITE(LuaState * ls);
	static int Call_FREEFRONTSPRITE(LuaState * ls);

	static int Call_SETPINITLIFE(LuaState * ls);

	static int Call_BUBUILD(LuaState * ls);
	static int Call_BUACTIONSET(LuaState * ls);

	static int Call_ENBUILD(LuaState * ls);
	static int Call_ENACTIONSET(LuaState * ls);
	static int Call_ENAZBUILD(LuaState * ls);

	static int Call_RAMA(LuaState * ls);
	static int Call_INTER(LuaState * ls);

	static int Call_COLLISION_CIRCLE(LuaState * ls);

	static int Call_BGVALUE(LuaState * ls);
	static int Call_BGVALEX(LuaState * ls);
	static int Call_BGCOLOR(LuaState * ls);
	static int Call_BGFLAG(LuaState * ls);
	static int Call_BGOFF(LuaState * ls);

	static int Call_SELBUILD(LuaState * ls);
	static int Call_SELCLEAR(LuaState * ls);
	static int Call_SELCONFIRM(LuaState * ls);
	static int Call_SELSETUP(LuaState * ls);
	static int Call_SELSET(LuaState * ls);

public:
	static int Get_D(LuaState * ls);
	static int Get_Du(LuaState * ls);
	static int Get_RANK(LuaState * ls);
	static int Get_CHARA(LuaState * ls);
	static int Get_REPLAYMODE(LuaState * ls);

	static int Get_ENX(LuaState * ls);
	static int Get_ENY(LuaState * ls);

	static int Get_CHECKKEY(LuaState * ls);

	static int Get_PX(LuaState * ls);
	static int Get_PY(LuaState * ls);
	static int Get_PLIFE(LuaState * ls);

	static int Get_SELCOMPLETE(LuaState * ls);
	static int Get_SEL(LuaState * ls);
	static int Get_SELFIRSTID(LuaState * ls);

public:
	static bool bhavenext;
	static LuaObject _para;
	static LuaObject _obj;
	static int ii;
	static int argscount;
};

#endif

#endif
#endif