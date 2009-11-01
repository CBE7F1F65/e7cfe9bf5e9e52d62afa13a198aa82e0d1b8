#ifndef __NOTUSEHDSS

#include "../Header/Export_Lua.h"
#include "../Header/LuaConstDefine.h"
#include "../Header/keytable.h"
#include "../Header/BGLayer.h"
#include "../Header/Process.h"


bool Export_Lua::_LuaRegistHDSSFunction(LuaObject * obj)
{
	LuaObject _hdssobj = obj->CreateTable("hdss");
	_hdssobj.Register("Call", LuaFn_HDSS);
	return true;
}

int Export_Lua::LuaFn_HDSS(LuaState * ls)
{
	LuaStack args(ls);

	LuaObject _obj = args[1];
	DWORD nowval = _LuaHelper_GetDWORD(&_obj);

	switch (nowval & SCRKWMASK_TYPE)
	{
	case SCRKW_CLASS_LAYER:
		switch (nowval)
		{
		case SCR_BGVALUE:
			if (args.Count() == 8)
			{
				_obj = args[8];
				DWORD _col = _LuaHelper_GetColor(&_obj);
				ubg[args[2].GetInteger()]->valueSet(mp.tex, args[3].GetInteger(), args[4].GetFloat(), args[5].GetFloat(), args[6].GetFloat(), args[7].GetFloat(), _col);
			}
			return 0;
		}
		break;
	}
	return 0;
}

#endif