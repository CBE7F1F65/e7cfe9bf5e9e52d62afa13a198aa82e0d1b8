#ifndef __NOTUSELUA
#ifndef __NOTINTHISGAME

#include "Export_Lua.h"
#include "processPrep.h"

bool Export_Lua::_LuaRegistGameConst(LuaObject * obj)
{
	return true;
}

bool Export_Lua::_LuaRegistGameFunction(LuaObject * obj)
{
	LuaObject _gameobj;
	_gameobj = obj->CreateTable("game");

	_gameobj.Register("SetLastIP", LuaFn_Game_SetLastIP);
	_gameobj.Register("GetLastIP", LuaFn_Game_GetLastIP);

	return true;
}

int Export_Lua::LuaFn_Game_SetLastIP(LuaState * ls)
{
	LuaStack args(ls);

	LuaObject _obj;
	_obj = args[1];
	DWORD _ipx = _LuaHelper_GetDWORD(&_obj);
	WORD _ipport = args[2].GetInteger();
	Export::SetLastIP(_ipx, _ipport);
	return 0;
}

int Export_Lua::LuaFn_Game_GetLastIP(LuaState * ls)
{
	DWORD _ipx;
	WORD _ipport;
	if (Export::GetLastIP(&_ipx, &_ipport))
	{
		_LuaHelper_PushDWORD(ls, _ipx);
		ls->PushInteger(_ipport);
		return 2;
	}
	return 0;
}

#endif
#endif