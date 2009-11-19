#ifndef __NOTUSELUA
#ifndef __NOTUSEHDSS

#include "../Header/Export_Lua_HDSS.h"
#include "../Header/LuaConstDefine.h"
#include "../Header/Scripter.h"

#include "../Header/Export_Lua_HDSS_CallGet.h"

int Export_Lua_HDSS::LuaFn_HDSS_Get(LuaState * ls)
{
	LuaStack args(ls);

	DWORD nowval = args[1].GetInteger();

	switch (nowval & SCRKWMASK_CLASS)
	{
		/************************************************************************/
		/* AttackObject                                                         */
		/************************************************************************/
	case SCRKW_CLASS_ATTACKOBJECT:
		switch (nowval)
		{
		case SCR_BUI:
			break;
		case SCR_BUANGLE:
			break;
		case SCR_BUSPEED:
			break;
		case SCR_BUX:
			break;
		case SCR_BUY:
			break;
		case SCR_BUTIMER:
			break;
		case SCR_BUCANCELABLE:
			break;
		case SCR_BUHAVEGRAY:
			break;

		case SCR_BEI:
			break;
		case SCR_BEANGLE:
			break;
		case SCR_BESPEED:
			break;
		case SCR_BEX:
			break;
		case SCR_BEY:
			break;
		case SCR_BETIMER:
			break;
		case SCR_BEHOLDTAR:
			break;
		case SCR_BEPINTAR:
			break;
		}
		break;
		/************************************************************************/
		/* Ghost                                                                */
		/************************************************************************/
	case SCRKW_CLASS_GHOST:
		switch (nowval)
		{
		case SCR_GHX:
			break;
		case SCR_GHY:
			break;
		case SCR_GHTIMER:
			break;
		case SCR_GHI:
			break;
		case SCR_GHANGLE:
			break;
		case SCR_GHSPEED:
			break;
		case SCR_GHAMAP:
			break;
		case SCR_GHRMAP:
			break;
		case SCR_GHAIMX:
			break;
		case SCR_GHAIMY:
			break;
		case SCR_GHLIFE:
			break;
		case SCR_GHAC:
			break;
		}
		break;
		/************************************************************************/
		/* Enemy                                                                */
		/************************************************************************/
	case SCRKW_CLASS_ENEMY:
		switch (nowval)
		{
		case SCR_ENX:
			break;
		case SCR_ENY:
			break;
		case SCR_ENTIMER:
			break;
		case SCR_ENI:
			break;
		case SCR_ENANGLE:
			break;
		case SCR_ENSPEED:
			break;
		case SCR_ENAMAP:
			break;
		case SCR_ENRMAP:
			break;
		case SCR_ENAIMX:
			break;
		case SCR_ENAIMY:
			break;
		case SCR_ENLIFE:
			break;
		}
		break;
		/************************************************************************/
		/* Math                                                                 */
		/************************************************************************/
	case SCRKW_CLASS_MATH:
		switch (nowval)
		{
		case SCR_RAND:
			break;
		case SCR_RANDR:
			break;
		case SCR_SEED:
			break;
		case SCR_SINA:
			break;
		case SCR_COSA:
			break;
		case SCR_TANA:
			break;
		case SCR_ASIN2:
			break;
		case SCR_ACOS2:
			break;
		case SCR_ATAN2:
			break;
		case SCR_SQRT:
			break;
		case SCR_SIGN:
			break;
		case SCR_ROLL:
			break;
		}
		break;
		/************************************************************************/
		/* Other                                                                */
		/************************************************************************/
	case SCRKW_CLASS_OTHER:
		switch (nowval)
		{
		case SCR_D:
			return hdsscallget.Get_D(ls);
		case SCR_DU:
			return hdsscallget.Get_Du(ls);
		case SCR_TX:
			break;
		case SCR_TY:
			break;
		case SCR_TIME:
			break;
		case SCR_NOWNAME:
			break;
		case SCR_NOWCON:
			break;

		case SCR_DIFFI:
			break;
		case SCR_SNOSTAGE:
			break;
		case SCR_SNODIFFI:
			break;
		case SCR_SNOBATTLE:
			break;
		case SCR_SNOUSER:
			break;
		case SCR_CHARA:
			return hdsscallget.Get_CHARA(ls);
		case SCR_GETSCENE:
			break;
		case SCR_MODE:
			break;
		case SCR_REPLAYMODE:
			break;
		case SCR_FRAMESKIP:
			break;
		}
		break;
		/************************************************************************/
		/* Special                                                              */
		/************************************************************************/
	case SCRKW_CLASS_SPECIAL:
		switch (nowval)
		{
		case SCR_CHATI:
			break;

		case SCR_BOSSFAILED:
			break;
		case SCR_BOSSFLAG:
			break;

		case SCR_CHECKKEY:
			break;

		case SCR_GETFLAG:
			break;

		case SCR_PLAYERNAME:
			break;
		case SCR_ENEMYNAME:
			break;
		case SCR_SPELLNAME:
			break;
		case SCR_SPELLUSERNAME:
			break;
		case SCR_SPELLUSERENAME:
			break;
		}
		break;
		/************************************************************************/
		/* Effect                                                               */
		/************************************************************************/
	case SCRKW_CLASS_EFFECT:
		switch (nowval)
		{
		}
		break;
		/************************************************************************/
		/* Player                                                               */
		/************************************************************************/
	case SCRKW_CLASS_PLAYER:
		switch (nowval)
		{
		case SCR_PX:
			break;
		case SCR_PY:
			break;
		case SCR_PLIFE:
			return hdsscallget.Get_PLIFE(ls);
		case SCR_PBOMB:
			break;
		case SCR_PPOWER:
			break;
		case SCR_PFAITH:
			break;
		case SCR_PPOINT:
			break;
		case SCR_PBBORDER:
			break;
		case SCR_PBSLOW:
			break;
		case SCR_PBINFI:
			break;
		case SCR_PSPEED:
			break;
		case SCR_PSLOWSPEED:
			break;
		case SCR_PGX:
			break;
		case SCR_PGY:
			break;
		case SCR_HAVEPLAYER:
			break;
		}
		break;
		/************************************************************************/
		/* Layer                                                                */
		/************************************************************************/
	case SCRKW_CLASS_LAYER:
		switch (nowval)
		{
		case SCR_BGSINDEX:
			break;
		case SCR_BGSTIMER:
			break;
		}
		break;
		/************************************************************************/
		/* Select                                                               */
		/************************************************************************/
	case SCRKW_CLASS_SELECT:
		switch (nowval)
		{
		case SCR_SELCOMPLETE:
			return hdsscallget.Get_SELCOMPLETE(ls);
		case SCR_SEL:
			return hdsscallget.Get_SEL(ls);
		case SCR_SELFIRSTID:
			return hdsscallget.Get_SELFIRSTID(ls);
		case SCR_ISELCOMPLETE:
			break;
		case SCR_ISEL:
			break;
		case SCR_ISELFIRSTID:
			break;
		}
		break;
	}
	return 0;
}

#endif
#endif