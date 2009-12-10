#ifndef __NOTUSELUA
#ifndef __NOTUSEHDSS

#include "Export_Lua_HDSS_CallGet.h"
#include "processPrep.h"

#include "../Header/Export_Lua_HDSS_CallGetDefine.h"

int _HDSSCallGet::Get_D(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		int _index = _INEXT_HDSS_LUAFUNC;
		if (Scripter::scr.d[_index].bfloat)
		{
			_PD_HDSS_LUA(CUINT(Scripter::scr.d[_index].value));
		}
		else
		{
			_PI_HDSS_LUA(CAST(Scripter::scr.d[_index]));
		}
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_Du(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		int _index = _INEXT_HDSS_LUAFUNC;
		_PD_HDSS_LUA(UCAST(Scripter::scr.d[_index]));
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_RANK(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (true)
	{
		_PI_HDSS_LUA(Player::rank);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_CHARA(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		BYTE _playerindex = _INEXT_HDSS_LUAFUNC;
		_PI_HDSS_LUA(Player::p[_playerindex].nowID);
		_PI_HDSS_LUA(Player::p[_playerindex].ID);
		_PI_HDSS_LUA(Player::p[_playerindex].ID_sub_1);
		_PI_HDSS_LUA(Player::p[_playerindex].ID_sub_2);
		return 4;
	}
	return 0;
}

int _HDSSCallGet::Get_SELCOMPLETE(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		int _selsys = _INEXT_HDSS_LUAFUNC;

		bool _bclearaftercomplete = true;
		_JNEXT_HDSS_LUAFUNC;
		if (bhavenext)
		{
			_bclearaftercomplete = _IOBJ_HDSS_LUA;
		}

		if (_selsys >= 0 && _selsys < SELSYSTEMMAX)
		{
			_PB_HDSS_LUA(SelectSystem::selsys[_selsys].complete);
			_PI_HDSS_LUA(SelectSystem::selsys[_selsys].select);
			if (SelectSystem::selsys[_selsys].complete && _bclearaftercomplete)
			{
				SelectSystem::selsys[_selsys].Clear();
			}
			return 2;
		}
	}
	return 0;
}

int _HDSSCallGet::Get_ENX(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		BYTE _playerindex = _INEXT_HDSS_LUAFUNC;
		BYTE _enindex = Enemy::en[_playerindex].getIndex();
		_JNEXT_HDSS_LUAFUNC;
		if (bhavenext)
		{
			_enindex = _IOBJ_HDSS_LUA;
		}
		_PF_HDSS_LUA(Enemy::en[_playerindex][_enindex].x);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_ENY(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		BYTE _playerindex = _INEXT_HDSS_LUAFUNC;
		BYTE _enindex = Enemy::en[_playerindex].getIndex();
		_JNEXT_HDSS_LUAFUNC;
		if (bhavenext)
		{
			_enindex = _IOBJ_HDSS_LUA;
		}
		_PF_HDSS_LUA(Enemy::en[_playerindex][_enindex].y);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_PX(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		BYTE _playerindex = _INEXT_HDSS_LUAFUNC;
		_PF_HDSS_LUA(Player::p[_playerindex].x);
		_PI_HDSS_LUA(Player::p[_playerindex].nowID);
		return 2;
	}
	return 0;
}

int _HDSSCallGet::Get_CHECKKEY(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 2)
	{
		BYTE _playerindex = _INEXT_HDSS_LUAFUNC;
		int _ksi = _INEXT_HDSS_LUAFUNC;
		int _type = DIKEY_PRESSED;
		_JNEXT_HDSS_LUAFUNC;
		if (bhavenext)
		{
			_type = _IOBJ_HDSS_LUA;
		}
		bool bret = GameInput::GetKey(_playerindex, _ksi, _type);
		_PB_HDSS_LUA(bret);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_PY(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		BYTE _playerindex = _INEXT_HDSS_LUAFUNC;
		_PF_HDSS_LUA(Player::p[_playerindex].y);
		_PI_HDSS_LUA(Player::p[_playerindex].nowID);
		return 2;
	}
	return 0;
}

int _HDSSCallGet::Get_PLIFE(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		BYTE _playerindex = _INEXT_HDSS_LUAFUNC;
		_PI_HDSS_LUA(Player::p[_playerindex].nLife);
		_PI_HDSS_LUA(Player::p[_playerindex].initlife);
		return 2;
	}
	return 0;
}

int _HDSSCallGet::Get_SEL(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		int _selsys = _INEXT_HDSS_LUAFUNC;
		if (_selsys >= 0 && _selsys < SELSYSTEMMAX)
		{
			_PI_HDSS_LUA(SelectSystem::selsys[_selsys].select);
			return 1;
		}
	}
	return 0;
}

int _HDSSCallGet::Get_SELFIRSTID(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		int _selsys = _INEXT_HDSS_LUAFUNC;
		if (_selsys >= 0 && _selsys < SELSYSTEMMAX)
		{
			_PI_HDSS_LUA(SelectSystem::selsys[_selsys].firstID);
			return 1;
		}
	}
	return 0;
}

#endif
#endif