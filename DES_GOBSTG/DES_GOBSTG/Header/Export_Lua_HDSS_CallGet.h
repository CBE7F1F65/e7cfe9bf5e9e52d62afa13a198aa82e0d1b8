#ifndef __NOTUSELUA
#ifndef __NOTUSEHDSS

#ifndef _EXPORT_LUA_HDSS_CALLGET_H
#define _EXPORT_LUA_HDSS_CALLGET_H

#include "../Header/Export_Lua.h"

static class _HDSSCallGet
{
public:
	_HDSSCallGet();
	~_HDSSCallGet();
	int Call_SETSTATE(LuaState * ls);
	int Call_SETTIME(LuaState * ls);
	int Call_SE(LuaState * ls);
	int Call_RETURN(LuaState * ls);
	int Call_BGVALUE(LuaState * ls);
	int Call_BGVALEX(LuaState * ls);
	int Call_SELBUILD(LuaState * ls);
	int Call_SELSET(LuaState * ls);

public:
	int Get_SELCOMPLETE(LuaState * ls);
	int Get_SEL(LuaState * ls);
	int Get_SELFIRSTID(LuaState * ls);

public:
	bool bhavenext;
	LuaObject _para;
	LuaObject _obj;
	int ii;
	int argscount;
}hdsscallget;

#endif

#endif
#endif