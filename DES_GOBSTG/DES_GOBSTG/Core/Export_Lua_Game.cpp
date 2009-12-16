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

	_gameobj.Register("Random_Int", LuaFn_Game_Random_Int);
	_gameobj.Register("Random_Float", LuaFn_Game_Random_Float);
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
	_gameobj.Register("GetPlayerSendExInfo", LuaFn_Game_GetPlayerSendExInfo);
	_gameobj.Register("PlayerSendEx", LuaFn_Game_PlayerSendEx);
	_gameobj.Register("GetPlayerStopInfo", LuaFn_Game_GetPlayerStopInfo);
	_gameobj.Register("GetEnumReplayInfo", LuaFn_Game_GetEnumReplayInfo);
	_gameobj.Register("SetEnumReplayByIndex", LuaFn_Game_SetEnumReplayByIndex);

	return true;
}

int Export_Lua_Game::LuaFn_Game_Random_Int(LuaState * ls)
{
	LuaStack args(ls);

	int argscount = args.Count();
	int _imin = 0;
	int _imax = RAND_MAX;
	if (argscount > 0)
	{
		_imin = args[1].GetInteger();
		if (argscount > 1)
		{
			_imax = args[2].GetInteger() + 1;
		}
	}
	int _iret = randt(_imin, _imax);
	ls->PushInteger(_iret);
	return 1;
}

int Export_Lua_Game::LuaFn_Game_Random_Float(LuaState * ls)
{
	LuaStack args(ls);

	int argscount = args.Count();
	float _fmin = 0.0f;
	float _fmax = 1.0f;
	if (argscount > 0)
	{
		_fmin = args[1].GetFloat();
		if (argscount > 1)
		{
			_fmax = args[2].GetFloat();
		}
	}
	float _fret = randtf(_fmin, _fmax);
	ls->PushNumber(_fret);
	return 1;
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
	int iret = Process::mp.AccessIP();
	ls->PushInteger(iret);
	return 1;
}

int Export_Lua_Game::LuaFn_Game_SetLatency(LuaState * ls)
{
	LuaStack args(ls);

	int _latency = args[1].GetInteger();
	bool bret = Process::mp.SetLatency(_latency);
	ls->PushBoolean(bret);
	return 1;
}

int Export_Lua_Game::LuaFn_Game_SetMatchMode(LuaState * ls)
{
	LuaStack args(ls);

	BYTE _mode = args[1].GetInteger();
	Process::mp.SetMatchMode(_mode);
	return 0;
}

int Export_Lua_Game::LuaFn_Game_GetMatchMode(LuaState * ls)
{
	BYTE _mode = Process::mp.GetMatchMode();
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
			if (!strlen(BResource::res.playerdata[i].name))
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
		ls->PushInteger(BResource::res.playerdata[_index].faceSIID);
		_LuaHelper_PushString(ls, BResource::res.playerdata[_index].name);
		_LuaHelper_PushString(ls, BResource::res.playerdata[_index].ename);
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
			if (!strlen(BResource::res.playerdata[i].scenename))
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
		ls->PushString(BResource::res.playerdata[_index].scenename);
		return 1;
	}
	return 0;
}

int Export_Lua_Game::LuaFn_Game_GetSendItemInfo(LuaState * ls)
{
	LuaStack args(ls);
	BYTE _playerindex = args[1].GetInteger();

	EffectSp * _peffsp = &(*(EffectSp::effsp[_playerindex]));
	ls->PushInteger(_peffsp->setID);
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
	int _index = Bullet::bu[_playerindex].getIndex();
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
	int _index = Enemy::en[_playerindex].getIndex();
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
		return 5;
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

int Export_Lua_Game::LuaFn_Game_GetPlayerSendExInfo(LuaState * ls)
{
	LuaStack args(ls);
	BYTE _playerindex = args[1].GetInteger();
	int _esindex = EffectSp::effsp[_playerindex].getIndex();
	EffectSp * _peffsp = &(*EffectSp::effsp[_playerindex]);

	ls->PushInteger(_esindex);
	ls->PushInteger(Player::p[1-_playerindex].nowID);
	ls->PushNumber(Player::p[_playerindex].x);
	ls->PushNumber(Player::p[_playerindex].y);
	ls->PushNumber(Player::p[1-_playerindex].x);
	ls->PushNumber(Player::p[1-_playerindex].y);
	ls->PushInteger(Player::p[_playerindex].nowID);
	return 7;
}

int Export_Lua_Game::LuaFn_Game_PlayerSendEx(LuaState * ls)
{
	LuaStack args(ls);

	BYTE _playerindex = args[1].GetInteger();
	int _esindex = args[2].GetInteger();
	EffectSp * _peffsp = &(EffectSp::effsp[_playerindex][_esindex]);

	float _aimx = args[3].GetFloat();
	float _aimy = args[4].GetFloat();
	int _chasetimer = args[5].GetInteger();
	DWORD _color = 0xa0ffffff;
	int _headangleadd = SIGN(_playerindex) * 800;
	float _appendfloat = 0;

	int argscount = args.Count();
	if (argscount > 5)
	{
		LuaObject _tobj = args[6];
		_color = _LuaHelper_GetDWORD(&_tobj);
		if (argscount > 6)
		{
			_headangleadd = args[7].GetInteger();
			if (argscount > 7)
			{
				_appendfloat = args[8].GetFloat();
				if (argscount > 8)
				{
					int _siid = args[9].GetInteger();
					_peffsp->siid = _siid;
				}
			}
		}

	}
	_peffsp->colorSet(_color, BLEND_ALPHAADD);
	_peffsp->actionSet(9000, 0, _headangleadd);
	_peffsp->chaseSet(EFFSP_CHASE_FREE, _aimx, _aimy, _chasetimer);
	_peffsp->AppendData(Player::p[1-_playerindex].nowID, _appendfloat);

	return 0;
}

int Export_Lua_Game::LuaFn_Game_GetPlayerStopInfo(LuaState * ls)
{
	LuaStack args(ls);

	BYTE _playerindex = args[1].GetInteger();

	if (Player::raisestopplayerindex >= M_PL_MATCHMAXPLAYER)
	{
		return 0;
	}

	if (Player::raisestopplayerindex == _playerindex)
	{
		ls->PushBoolean(true);
	}
	else
	{
		_playerindex = 1 - _playerindex;
		ls->PushBoolean(false);
	}
	ls->PushInteger(Player::p[_playerindex].nowID);
	ls->PushInteger(Player::p[1-_playerindex].nowID);
	ls->PushInteger(Player::p[_playerindex].stoptimer);
	ls->PushInteger(PL_SHOOTINGCHARGE_STOPTIME);
	BYTE _spellclass = 0;
	BYTE _spelllevel = 0;
	Player::p[_playerindex].GetSpellClassAndLevel(&_spellclass, &_spelllevel);
	ls->PushInteger(_spellclass);
	ls->PushInteger(_spelllevel);
	return 7;
}

int Export_Lua_Game::LuaFn_Game_GetEnumReplayInfo(LuaState * ls)
{
	LuaStack args(ls);

	int _index = args[1].GetInteger();
	_index = Replay::nenumrpy - _index - 1;
	if (_index >= RPYENUMMAX || _index < 0)
	{
		ls->PushString("");
		return 1;
	}

	LuaStackObject _table = ls->CreateTable();
	_table.SetInteger("year", Replay::enumrpy[_index].rpyinfo.year);
	_table.SetInteger("month", Replay::enumrpy[_index].rpyinfo.month);
	_table.SetInteger("day", Replay::enumrpy[_index].rpyinfo.day);
	LuaStackObject _usernametable = _table.CreateTable("username");
	LuaStackObject _usingcharatable = _table.CreateTable("usingchara");
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		_usernametable.SetString(i+1, Replay::enumrpy[_index].rpyinfo.username[i]);
		LuaStackObject _usingcharasubtable = _usingcharatable.CreateTable(i+1);
		for (int j=0; j<M_PL_ONESETPLAYER; j++)
		{
			_usingcharasubtable.SetString(j+1, Data::data.getPlayerName(Replay::enumrpy[_index].rpyinfo.usingchara[i][j]));
		}
	}
	ls->PushString(Replay::enumrpy[_index].filename);
	ls->PushValue(_table);
	return 2;
}

int Export_Lua_Game::LuaFn_Game_SetEnumReplayByIndex(LuaState * ls)
{
	LuaStack args(ls);

	int _index = args[1].GetInteger();

	if (strlen(Replay::enumrpy[_index].filename))
	{
		strcpy(Process::mp.rpyfilename, Replay::enumrpy[_index].filename);
		Process::mp.replaymode = true;
	}
	return 0;
}

#endif
#endif