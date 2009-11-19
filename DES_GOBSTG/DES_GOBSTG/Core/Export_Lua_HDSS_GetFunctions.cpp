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
		if (scr.d[_index].bfloat)
		{
			_PD_HDSS_LUA(CUINT(scr.d[_index].value));
		}
		else
		{
			_PI_HDSS_LUA(CAST(scr.d[_index]));
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
		_PD_HDSS_LUA(UCAST(scr.d[_index]));
		return 1;
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
			_PB_HDSS_LUA(selsys[_selsys].complete);
			_PI_HDSS_LUA(selsys[_selsys].select);
			if (selsys[_selsys].complete && _bclearaftercomplete)
			{
				selsys[_selsys].Clear();
			}
			return 2;
		}
	}
	return 0;
}

int _HDSSCallGet::Get_PLIFE(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		int _index = _INEXT_HDSS_LUAFUNC;
		_PI_HDSS_LUA(Player::p[_index].nLife);
		_PI_HDSS_LUA(Player::p[_index].initlife);
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
			_PI_HDSS_LUA(selsys[_selsys].select);
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
			_PI_HDSS_LUA(selsys[_selsys].firstID);
			return 1;
		}
	}
	return 0;
}

#endif
#endif