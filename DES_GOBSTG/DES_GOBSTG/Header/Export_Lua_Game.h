#ifndef __NOTUSELUA
#ifndef __NOTINTHISGAME

#include "Export_Lua.h"

class Export_Lua_Game : Export_Lua
{
public:
	static bool _LuaRegistConst(LuaObject * obj);
	static bool _LuaRegistFunction(LuaObject * obj);

	static int LuaFn_Game_SetLastIP(LuaState * ls);
	static int LuaFn_Game_GetLastIP(LuaState * ls);
	static int LuaFn_Game_AccessIP(LuaState * ls);
	static int LuaFn_Game_SetLatency(LuaState * ls);
	static int LuaFn_Game_SetMatchMode(LuaState * ls);
	static int LuaFn_Game_GetMatchMode(LuaState * ls);
	static int LuaFn_Game_GetPlayerContentTable(LuaState * ls);
	static int LuaFn_Game_GetSceneContentTable(LuaState * ls);
	static int LuaFn_Game_GetSendItemInfo(LuaState * ls);
};

#endif
#endif