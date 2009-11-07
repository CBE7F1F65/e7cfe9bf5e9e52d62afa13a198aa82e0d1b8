#ifndef __NOTUSELUA
#ifndef __NOTUSEHDSS

#include "../Header/Export_Lua.h"
#include "../Header/LuaConstDefine.h"
#include "../Header/Scripter.h"

#include "../Header/Export_Lua_HDSS_CallGet.h"

int Export_Lua::LuaFn_HDSS_Call(LuaState * ls)
{
	LuaStack args(ls);

	DWORD nowval = args[1].GetInteger();
	int argscount = args.Count();
	if (argscount < 2)
	{
		ShowError(LUAERROR_LUAERROR, "HDSS args count error.");
		return 0;
	}

	switch (nowval & SCRKWMASK_TYPE)
	{
		/************************************************************************/
		/* Action                                                               */
		/************************************************************************/
	case SCRKW_ACTION:
		switch (nowval & SCRKWMASK_CLASS)
		{
		case SCRKW_CLASS_OTHER:
			switch (nowval)
			{
			}
			break;
		case SCRKW_CLASS_SPECIAL:
			switch (nowval)
			{
			case SCR_SETTIME:
				return hdsscallget.Call_SETTIME(ls);
			case SCR_RETURN:
				return hdsscallget.Call_RETURN(ls);
			}
			break;
		}
		break;
		/************************************************************************/
		/* BASIC                                                                */
		/************************************************************************/
	case SCRKW_BASIC:
		switch (nowval & SCRKWMASK_CLASS)
		{
			/************************************************************************/
			/* LAYER                                                                */
			/************************************************************************/
		case SCRKW_CLASS_LAYER:
			switch (nowval)
			{
			case SCR_BGVALUE:
				return hdsscallget.Call_BGVALUE(ls);
			case SCR_BGVALEX:
				return hdsscallget.Call_BGVALEX(ls);
			}
			break;
			/************************************************************************/
			/* SELECT                                                               */
			/************************************************************************/
		case SCRKW_CLASS_SELECT:
			switch (nowval)
			{
			case SCR_SELBUILD:
				return hdsscallget.Call_SELBUILD(ls);
				break;
			case SCR_SELSET:
				return hdsscallget.Call_SELSET(ls);
			}
		}
	}
	return 0;
}

#endif
#endif