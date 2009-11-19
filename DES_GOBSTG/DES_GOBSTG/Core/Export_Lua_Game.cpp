#ifndef __NOTUSELUA
#ifndef __NOTINTHISGAME

#include "Export_Lua_Game.h"
#include "processPrep.h"

bool Export_Lua_Game::_LuaRegistConst(LuaObject * obj)
{
	return true;
}

bool Export_Lua_Game::_LuaRegistFunction(LuaObject * obj)
{
	LuaObject _gameobj;
	_gameobj = obj->CreateTable("game");

	_gameobj.Register("SetLastIP", LuaFn_Game_SetLastIP);
	_gameobj.Register("GetLastIP", LuaFn_Game_GetLastIP);
	_gameobj.Register("AccessIP", LuaFn_Game_AccessIP);
	_gameobj.Register("SetLatency", LuaFn_Game_SetLatency);
	_gameobj.Register("SetMatchMode", LuaFn_Game_SetMatchMode);
	_gameobj.Register("GetMatchMode", LuaFn_Game_GetMatchMode);
	_gameobj.Register("GetPlayerContentTable", LuaFn_Game_GetPlayerContentTable);
	_gameobj.Register("GetSceneContentTable", LuaFn_Game_GetSceneContentTable);

	return true;
}

int Export_Lua_Game::LuaFn_Game_SetLastIP(LuaState * ls)
{
	LuaStack args(ls);

	LuaObject _obj;
	_obj = args[1];
	DWORD _ipx = _LuaHelper_GetDWORD(&_obj);
	WORD _ipport = args[2].GetInteger();
	Export::SetLastIP(_ipx, _ipport);
	return 0;
}

int Export_Lua_Game::LuaFn_Game_GetLastIP(LuaState * ls)
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

int Export_Lua_Game::LuaFn_Game_AccessIP(LuaState * ls)
{
	int iret = mp.AccessIP();
	ls->PushInteger(iret);
	return 1;
}

int Export_Lua_Game::LuaFn_Game_SetLatency(LuaState * ls)
{
	LuaStack args(ls);

	int _latency = args[1].GetInteger();
	bool bret = mp.SetLatency(_latency);
	ls->PushBoolean(bret);
	return 1;
}

int Export_Lua_Game::LuaFn_Game_SetMatchMode(LuaState * ls)
{
	LuaStack args(ls);

	BYTE mode = args[1].GetInteger();
	mp.SetMatchMode(mode);
	return 0;
}

int Export_Lua_Game::LuaFn_Game_GetMatchMode(LuaState * ls)
{
	BYTE mode = mp.GetMatchMode();
	ls->PushInteger(mode);
	return 1;
}

int Export_Lua_Game::LuaFn_Game_GetPlayerContentTable(LuaState * ls)
{
	LuaStack args(ls);
	if (!args.Count())
	{
		int playercount = PLAYERTYPEMAX;
		for (int i=0; i<PLAYERTYPEMAX; i++)
		{
			if (!strlen(res.playerdata[i].name))
			{
				playercount = i;
				break;
			}
		}
		ls->PushInteger(playercount);
		return 1;
	}
	else
	{
		int index = args[1].GetInteger();
		ls->PushInteger(SpriteItemManager::faceIndexPlayer + res.playerdata[index].faceIndex);
		_LuaHelper_PushString(ls, res.playerdata[index].name);
		_LuaHelper_PushString(ls, res.playerdata[index].ename);
		return 3;
	}
	return 0;
}

int Export_Lua_Game::LuaFn_Game_GetSceneContentTable(LuaState * ls)
{
	LuaStack args(ls);
	if (!args.Count())
	{
		int scenecount = SCENEMAX;
		for (int i=0; i<SCENEMAX; i++)
		{
			if (!strlen(res.scenedata[i].scenename))
			{
				scenecount = i;
				break;
			}
		}
		ls->PushInteger(scenecount);
		return 1;
	}
	else
	{
		int index = args[1].GetInteger();
		ls->PushString(res.scenedata[index].scenename);
		return 1;
	}
	return 0;
}

#endif
#endif