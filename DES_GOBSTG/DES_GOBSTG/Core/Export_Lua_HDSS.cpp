#ifndef __NOTUSELUA
#ifndef __NOTUSEHDSS

#include "../Header/Export_Lua.h"
#include "../Header/LuaConstDefine.h"
#include "../Header/keytable.h"
#include "../Header/BGLayer.h"
#include "../Header/Process.h"
#include "../Header/BResource.h"
LuaFunction<bool> * Export_Lua::controlExecute;
LuaFunction<bool> * Export_Lua::stageExecute;
LuaFunction<bool> * Export_Lua::edefExecute;
LuaFunction<bool> * Export_Lua::sceneExecute;
LuaFunction<bool> * Export_Lua::functionExecute;
LuaFunction<bool> * Export_Lua::eventExecute;

void Export_Lua::_ChangeSpecialChar(char * str)
{
	int length = strlen(str);
	if (str[length-1] == '#')
	{
		str[length-1] = '_';
		str[length] = '3';
		str[length+1] = 0;
	}
	else if (str[length-1] == '@')
	{
		str[length-1] = '_';
		str[length] = '2';
		str[length+1] = 0;
	}
}

bool Export_Lua::_LuaRegistHDSSConst(LuaObject * obj)
{
	int i = 0;
	char str[M_STRMAX];
	for (; scrKeyTable[i].code != SCR_CONST || strcmp(scrKeyTable[i].word, SCR_CONST_STR); i++)
	{
		sprintf(str, "%s%s", HDSS_PREFIX, scrKeyTable[i].word);
		_ChangeSpecialChar(str);
		obj->SetInteger(str, scrKeyTable[i].code);
	}
	i++;
	i++;	//true
	i++;	//false
	for (; scrKeyTable[i].code != SCR_KEYSTATE || strcmp(scrKeyTable[i].word, SCR_KEYSTATE_STR); i++)
	{
		obj->SetInteger(scrKeyTable[i].word, scrKeyTable[i].code);
	}
	i++;
	for (; scrKeyTable[i].code != SCR_NULL || strcmp(scrKeyTable[i].word, SCR_NULL_STR); i++)
	{
		obj->SetNumber(scrKeyTable[i].word, CDOUBLEN(scrKeyTable[i].code));
	}

	//SI
	for (i=0; i<SPRITEITEMMAX; i++)
	{
		if (strlen(res.spritedata[i].spritename))
		{
			obj->SetInteger(res.spritedata[i].spritename, i);
		}
	}
	return true;
}

bool Export_Lua::_LuaRegistHDSSFunction(LuaObject * obj)
{
	LuaObject _hdssobj = obj->CreateTable("hdss");
	_hdssobj.Register("Call", LuaFn_HDSS);
	return true;
}

int Export_Lua::LuaFn_HDSS(LuaState * ls)
{
	LuaStack args(ls);

	DWORD nowval = args[1].GetInteger();
	int argscount = args.Count();
	if (argscount != 2)
	{
		ShowError(LUAERROR_LUAERROR, "HDSS args count error.");
		return 0;
	}
	LuaObject _para = args[2];
	if (!_para.IsTable())
	{
		ShowError(LUAERROR_LUAERROR, "HDSS arg must be a table.");
		return 0;
	}

	switch (nowval & SCRKWMASK_TYPE)
	{
	case SCRKW_BASIC:
		switch (nowval)
		{
		case SCR_BGVALUE:
			if (true)
			{
				int _index = _para.GetByIndex(1).GetInteger();
				int _siid = _para.GetByIndex(2).GetInteger();
				float _cenx = _para.GetByIndex(3).GetFloat();
				float _ceny = _para.GetByIndex(4).GetFloat();
				float _w = _para.GetByIndex(5).GetFloat();
				float _h = _para.GetByIndex(6).GetFloat();

				LuaObject _obj = _para.GetByIndex(7);
				DWORD _col = 0xffffffff;
				if (!_obj.IsNil())
				{
					_col = _LuaHelper_GetColor(&_obj);
				}

				ubg[_index]->valueSet(mp.tex, _siid, _cenx, _ceny, _w, _h, _col);
			}
			return 0;
		case SCR_BGVALEX:
			if (true)
			{
				int _index = _para.GetByIndex(1).GetInteger();
				int _siid = _para.GetByIndex(2).GetInteger();
				float _x = _para.GetByIndex(3).GetFloat();
				float _y = _para.GetByIndex(4).GetFloat();
				float _z = _para.GetByIndex(5).GetFloat();
				float _w = _para.GetByIndex(6).GetFloat();
				float _h = _para.GetByIndex(7).GetFloat();
				int _rotx = _para.GetByIndex(8).GetInteger();
				int _roty = _para.GetByIndex(9).GetInteger();
				int _rotz = _para.GetByIndex(10).GetInteger();

				LuaObject _obj = _para.GetByIndex(11);
				float _paral = 0;
				float _speed = 0;
				float _angle = 0;
				bool _move = false;
				bool _rotate = false;
				DWORD _col = 0xffffffff;
				if (!_obj.IsNil())
				{
					_paral = _obj.GetFloat();
					_obj = _para.GetByIndex(12);
					if (!_obj.IsNil())
					{
						_speed = _obj.GetFloat();
						_obj = _para.GetByIndex(13);
						if (!_obj.IsNil())
						{
							_move = _obj.GetBoolean();
							_obj = _para.GetByIndex(14);
							if (!_obj.IsNil())
							{
								_rotate = _para.GetBoolean();
								_obj = _para.GetByIndex(15);
								if (!_obj.IsNil())
								{
									_col = _LuaHelper_GetColor(&_obj);
								}
							}
						}
					}
				}

				ubg[_index]->valueSet(mp.tex, _siid, _x, _y, _z, _w, _h, _rotx, _roty, _rotz, _paral, _speed, _angle, _move, _rotate, _col);
			}
		}
		break;
	}
	return 0;
}

bool Export_Lua::InitCallbacks()
{
	LuaState * ls = state;
	LuaObject _obj = ls->GetGlobal(LUAFN_CONTROLEXECUTE);
	if (!_obj.IsFunction())
	{
		ShowError(LUAERROR_NOTFUNCTION, LUAFN_CONTROLEXECUTE);
		return false;
	}
	static LuaFunction<bool> _fcontrol = _obj;
	_fcontrol = _obj;
	controlExecute = &_fcontrol;
	_obj = ls->GetGlobal(LUAFN_STAGEEXECUTE);
	if (!_obj.IsFunction())
	{
		ShowError(LUAERROR_NOTFUNCTION, LUAFN_STAGEEXECUTE);
		return false;
	}
	static LuaFunction<bool> _fstage = _obj;
	_fstage = _obj;
	stageExecute = &_fstage;
	_obj = ls->GetGlobal(LUAFN_EDEFEXECUTE);
	if (!_obj.IsFunction())
	{
		ShowError(LUAERROR_NOTFUNCTION, LUAFN_EDEFEXECUTE);
		return false;
	}
	static LuaFunction<bool> _fedef = _obj;
	_fedef = _obj;
	edefExecute = &_fedef;
	_obj = ls->GetGlobal(LUAFN_SCENEEXECUTE);
	if (!_obj.IsFunction())
	{
		ShowError(LUAERROR_NOTFUNCTION, LUAFN_SCENEEXECUTE);
		return false;
	}
	static LuaFunction<bool> _fscene = _obj;
	_fscene = _obj;
	sceneExecute = &_fscene;
	_obj = ls->GetGlobal(LUAFN_FUNCTIONEXECUTE);
	if (!_obj.IsFunction())
	{
		ShowError(LUAERROR_NOTFUNCTION, LUAFN_FUNCTIONEXECUTE);
		return false;
	}
	static LuaFunction<bool> _ffunction = _obj;
	_ffunction = _obj;
	functionExecute = &_ffunction;
	_obj = ls->GetGlobal(LUAFN_EVENTEXECUTE);
	if (!_obj.IsFunction())
	{
		ShowError(LUAERROR_NOTFUNCTION, LUAFN_EVENTEXECUTE);
		return false;
	}
	static LuaFunction<bool> _fevent = _obj;
	_fevent = _obj;
	eventExecute = &_fevent;
	return true;
}

bool Export_Lua::Execute(DWORD typeflag, DWORD name, DWORD con)
{
	LuaState * ls = state;
	LuaFunction<bool> *_f;
	switch (typeflag)
	{
	case SCR_CONTROL:
		_f = controlExecute;
		break;
	case SCR_STAGE:
		_f = stageExecute;
		break;
	case SCR_EDEF:
		_f = edefExecute;
		break;
	case SCR_SCENE:
		_f = sceneExecute;
		break;
	case SCR_FUNCTION:
		_f = functionExecute;
		break;
	case SCR_EVENT:
		_f = eventExecute;
		break;
	}
	return (*_f)(name, con);
}

#endif
#endif