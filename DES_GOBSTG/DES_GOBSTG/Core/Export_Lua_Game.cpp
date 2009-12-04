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
	_gameobj.Register("GetSendItemInfo", LuaFn_Game_GetSendItemInfo);
	_gameobj.Register("AddSendBulletInfo", LuaFn_Game_AddSendBulletInfo);
	_gameobj.Register("AddSendGhostInfo", LuaFn_Game_AddSendGhostInfo);
	_gameobj.Register("GetPlayerDrainInfo", LuaFn_Game_GetPlayerDrainInfo);
	_gameobj.Register("SetDrainSpriteInfo", LuaFn_Game_SetPlayerDrainSpriteInfo);
	_gameobj.Register("SetGhostActiveInfo", LuaFn_Game_SetGhostActiveInfo);

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

	BYTE _mode = args[1].GetInteger();
	mp.SetMatchMode(_mode);
	return 0;
}

int Export_Lua_Game::LuaFn_Game_GetMatchMode(LuaState * ls)
{
	BYTE _mode = mp.GetMatchMode();
	ls->PushInteger(_mode);
	return 1;
}

int Export_Lua_Game::LuaFn_Game_GetPlayerContentTable(LuaState * ls)
{
	LuaStack args(ls);
	if (!args.Count())
	{
		int _playercount = PLAYERTYPEMAX;
		for (int i=0; i<PLAYERTYPEMAX; i++)
		{
			if (!strlen(res.playerdata[i].name))
			{
				_playercount = i;
				break;
			}
		}
		ls->PushInteger(_playercount);
		return 1;
	}
	else
	{
		int _index = args[1].GetInteger();
		ls->PushInteger(res.playerdata[_index].faceSIID);
		_LuaHelper_PushString(ls, res.playerdata[_index].name);
		_LuaHelper_PushString(ls, res.playerdata[_index].ename);
		return 3;
	}
	return 0;
}

int Export_Lua_Game::LuaFn_Game_GetSceneContentTable(LuaState * ls)
{
	LuaStack args(ls);
	if (!args.Count())
	{
		int _scenecount = SCENEMAX;
		for (int i=0; i<SCENEMAX; i++)
		{
			if (!strlen(res.scenedata[i].scenename))
			{
				_scenecount = i;
				break;
			}
		}
		ls->PushInteger(_scenecount);
		return 1;
	}
	else
	{
		int _index = args[1].GetInteger();
		ls->PushString(res.scenedata[_index].scenename);
		return 1;
	}
	return 0;
}

int Export_Lua_Game::LuaFn_Game_GetSendItemInfo(LuaState * ls)
{
	EffectSp * _peffsp = &(*(EffectSp::effsp));
	ls->PushInteger(_peffsp->ID);
	ls->PushNumber(_peffsp->x);
	ls->PushNumber(_peffsp->y);
	if (_peffsp->bAppend)
	{
		ls->PushInteger(_peffsp->nAppend);
		ls->PushNumber(_peffsp->fAppend);
		return 5;
	}
	return 3;
}

int Export_Lua_Game::LuaFn_Game_AddSendBulletInfo(LuaState * ls)
{
	LuaStack args(ls);
	
	BYTE _sendsetID = args[1].GetInteger();
	BYTE _sendtime = args[2].GetInteger();
	BYTE _playerindex = args[3].GetInteger();
	int _index = Bullet::bu[_playerindex].index;
	if (args.Count() > 3)
	{
		_index = args[4].GetInteger();
	}
	Bullet::bu[_playerindex][_index].AddSendInfo(_sendsetID, _sendtime);
	return 0;
}

int Export_Lua_Game::LuaFn_Game_AddSendGhostInfo(LuaState * ls)
{
	LuaStack args(ls);

	BYTE _sendsetID = args[1].GetInteger();
	BYTE _sendtime = args[2].GetInteger();
	BYTE _playerindex = args[3].GetInteger();
	float _accel = args[4].GetFloat();
	float _acceladd = args[5].GetFloat();
	int _index = Enemy::en[_playerindex].index;
	if (args.Count() > 5)
	{
		_index = args[6].GetInteger();
	}
	Enemy::en[_playerindex][_index].AddSendInfo(_sendsetID, _sendtime, _accel, _acceladd);
	return 0;
}

int Export_Lua_Game::LuaFn_Game_GetPlayerDrainInfo(LuaState * ls)
{
	LuaStack args(ls);

	BYTE _playerindex = args[1].GetInteger();
	int _eventID = args[2].GetInteger();
	ls->PushInteger(Player::p[_playerindex].nowID);
	ls->PushNumber(Player::p[_playerindex].x);
	ls->PushNumber(Player::p[_playerindex].y);
	ls->PushInteger(Player::p[_playerindex].draintimer);
	if (_eventID == SCR_EVENT_PLAYERDRAINCHECK)
	{
		ls->PushNumber((*Enemy::en[_playerindex]).type);
		ls->PushNumber((*Enemy::en[_playerindex]).x);
		ls->PushNumber((*Enemy::en[_playerindex]).y);
		return 7;
	}
	return 4;
}

int Export_Lua_Game::LuaFn_Game_SetPlayerDrainSpriteInfo(LuaState * ls)
{
	LuaStack args(ls);

	int argscount = args.Count();

	BYTE _playerindex = args[1].GetInteger();
	float _x = args[2].GetFloat();
	float _y = args[3].GetFloat();
	int _headangle = 0;
	float _hscale = 1.0f;
	float _vscale = 0.0f;
	if (argscount > 3)
	{
		_headangle = args[4].GetInteger();
		if (argscount > 4)
		{
			_hscale = args[5].GetFloat();
			if (argscount > 5)
			{
				_vscale = args[6].GetFloat();
			}
		}
	}
	Player::p[_playerindex].SetDrainSpriteInfo(_x, _y, _headangle, _hscale, _vscale);
	return 0;
}

int Export_Lua_Game::LuaFn_Game_SetGhostActiveInfo(LuaState * ls)
{
	LuaStack args(ls);

	BYTE _playerindex = args[1].GetInteger();
	BYTE _activemaxtime = args[2].GetInteger();
	WORD _eID = args[3].GetInteger();
	BYTE _type = args[4].GetInteger();
	int _angle = args[5].GetInteger();
	float _speed = args[6].GetFloat();
	float _damagerate = args[7].GetFloat();

	(*Enemy::en[_playerindex]).SetActiveInfo(_activemaxtime, _eID, _type, _angle, _speed, _damagerate);
	return 0;
}

#endif
#endif