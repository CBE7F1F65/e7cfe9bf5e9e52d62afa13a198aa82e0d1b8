#ifndef __NOTUSELUA
#ifndef __NOTUSEHDSS

#include "../Header/Export_Lua.h"
#include "../Header/LuaConstDefine.h"
#include "../Header/Processprep.h"

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
		obj->SetNumber(scrKeyTable[i].word, CUINT(scrKeyTable[i].code));
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

bool Export_Lua::_Helper_HDSS_GetPara(LuaStack * args, int i, LuaObject * _para)
{
	*_para = (*args)[i];
	if (!_para->IsTable())
	{
		ShowError(LUAERROR_LUAERROR, "HDSS arg must be a table.");
		return false;
	}
	return true;
}

int Export_Lua::LuaFn_HDSS(LuaState * ls)
{
	LuaStack args(ls);

	DWORD nowval = args[1].GetInteger();
	int argscount = args.Count();
	if (argscount < 2)
	{
		ShowError(LUAERROR_LUAERROR, "HDSS args count error.");
		return 0;
	}

	LuaObject _para;
	int ii;
	LuaObject _obj;
	bool bhavenext;

#define _NEXT_LUAPARA		(_para.GetByIndex(++ii))
#define _IOBJ_LUAPARA		(_obj.GetInteger())
#define _FOBJ_LUAPARA		(_obj.GetFloat())
#define _INEXT_LUAPARA		(_NEXT_LUAPARA.GetInteger())
#define _FNEXT_LUAPARA		(_NEXT_LUAPARA.GetFloat())
#define _NILCHECK_LUAPARA	(!_obj.IsNil())
#define _JNEXT_LUAPARA		_obj = _NEXT_LUAPARA;	bhavenext = _NILCHECK_LUAPARA
#define _GETPARAS(X)		if (!_Helper_HDSS_GetPara(&args, (X), &_para))	return false;	ii = 0

	_GETPARAS(2);
	switch (nowval & SCRKWMASK_TYPE)
	{
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
				if (argscount == 2)
				{
					int _index = _INEXT_LUAPARA;
					int _siid = _INEXT_LUAPARA;
					float _cenx = _FNEXT_LUAPARA;
					float _ceny = _FNEXT_LUAPARA;
					float _w = _FNEXT_LUAPARA;
					float _h = _FNEXT_LUAPARA;

					DWORD _col = 0xffffffff;
					_JNEXT_LUAPARA;
					if (bhavenext)
					{
						_col = _LuaHelper_GetColor(&_obj);
					}

					ubg[_index]->valueSet(mp.tex, _siid, _cenx, _ceny, _w, _h, _col);
				}
				return 0;
			case SCR_BGVALEX:
				if (argscount == 2)
				{
					int _index = _INEXT_LUAPARA;
					int _siid = _INEXT_LUAPARA;
					float _x = _FNEXT_LUAPARA;
					float _y = _FNEXT_LUAPARA;
					float _z = _FNEXT_LUAPARA;
					float _w = _FNEXT_LUAPARA;
					float _h = _FNEXT_LUAPARA;
					int _rotx = _INEXT_LUAPARA;
					int _roty = _INEXT_LUAPARA;
					int _rotz = _INEXT_LUAPARA;

					float _paral = 0;
					float _speed = 0;
					float _angle = 0;
					bool _move = false;
					bool _rotate = false;
					DWORD _col = 0xffffffff;
					_JNEXT_LUAPARA;
					if (bhavenext)
					{
						_paral = _obj.GetFloat();
						_JNEXT_LUAPARA;
						if (bhavenext)
						{
							_speed = _obj.GetFloat();
							_JNEXT_LUAPARA;
							if (bhavenext)
							{
								_move = _obj.GetBoolean();
								_JNEXT_LUAPARA;
								if (bhavenext)
								{
									_rotate = _para.GetBoolean();
									_JNEXT_LUAPARA;
									if (bhavenext)
									{
										_col = _LuaHelper_GetColor(&_obj);
									}
								}
							}
						}
					}

					ubg[_index]->valueSet(mp.tex, _siid, _x, _y, _z, _w, _h, _rotx, _roty, _rotz, _paral, _speed, _angle, _move, _rotate, _col);
				}
				return 0;
			}
			break;
			/************************************************************************/
			/* SELECT                                                               */
			/************************************************************************/
		case SCRKW_CLASS_SELECT:
			switch (nowval)
			{
			case SCR_SELBUILD:
				if (argscount == 2 || argscount == 3)
				{
					int _selsys = _INEXT_LUAPARA;
					int _id = _INEXT_LUAPARA;
					int _siid = _INEXT_LUAPARA;
					float _cenx = _FNEXT_LUAPARA;
					float _ceny = _FNEXT_LUAPARA;

					char * _info = NULL;
					float _hscale = 1.0f;
					float _vscale = 0.0f;
					BYTE _flag = SEL_NULL;
					_JNEXT_LUAPARA;
					if (bhavenext)
					{
						_info = (char *)(_obj.GetString());
						_JNEXT_LUAPARA;
						if (bhavenext)
						{
							_hscale = _obj.GetFloat();
							_JNEXT_LUAPARA;
							if (bhavenext)
							{
								_vscale = _obj.GetFloat();
								_JNEXT_LUAPARA;
								if (bhavenext)
								{
									_flag = _obj.GetInteger();
								}
							}
						}
					}

					Selector * _selector = selsys[_selsys].BuildSelector(_id, _siid, _cenx, _ceny, _info, _hscale, _vscale, _flag);
					if (argscount == 3)
					{
						_GETPARAS(3);
						seladj _adj[SEL_STATEMAX];
						ZeroMemory(_adj, sizeof(seladj)*SEL_STATEMAX);
						bool _havestate[SEL_STATEMAX];
						_JNEXT_LUAPARA;
						if (bhavenext)
						{
							_havestate[0] = true;
							_adj[0].xadj = _obj.GetFloat() + _cenx;
							_JNEXT_LUAPARA;
							if (bhavenext)
							{
								_adj[0].yadj = _obj.GetFloat() + _ceny;
								_JNEXT_LUAPARA;
								if (bhavenext)
								{
									_havestate[1] = true;
									_adj[1].xadj = _obj.GetFloat() + _cenx;
									_JNEXT_LUAPARA;
									if (bhavenext)
									{
										_adj[1].yadj = _obj.GetFloat() + _ceny;
										_JNEXT_LUAPARA;
										if (bhavenext)
										{
											_havestate[2] = true;
											_adj[2].xadj = _obj.GetFloat() + _cenx;
											_JNEXT_LUAPARA;
											if (bhavenext)
											{
												_adj[2].yadj = _obj.GetFloat() + _ceny;
												_JNEXT_LUAPARA;
												if (bhavenext)
												{
													_havestate[3] = true;
													_adj[3].xadj = _obj.GetFloat() + _cenx;
													_JNEXT_LUAPARA;
													if (bhavenext)
													{
														_adj[3].yadj = _obj.GetFloat() + _ceny;
														_JNEXT_LUAPARA;
													}
												}
											}
										}
									}
								}
							}
						}
						if (_havestate[0])
						{
							_selector->actionSet(SEL_NONE, _adj);
							if (_havestate[1])
							{
								_selector->actionSet(SEL_OVER, _adj);
								if (_havestate[2])
								{
									_selector->actionSet(SEL_ENTER, _adj);
									if (_havestate[3])
									{
										_selector->actionSet(SEL_LEAVE, _adj);
									}
								}
							}
						}
					}
				}
				break;
			case SCR_SELSET:
				if (argscount == 2 || argscount == 3)
				{
					int _selsys = _INEXT_LUAPARA;
					int _nselect = _INEXT_LUAPARA;
					int _select = _INEXT_LUAPARA;
					BYTE _keyplus = _INEXT_LUAPARA;
					BYTE _keyminus = _INEXT_LUAPARA;
					BYTE _keyok = _INEXT_LUAPARA;
					BYTE _keycancel = _INEXT_LUAPARA;

					int _maxtime = SELSYS_DEFAULTMAXTIME;
					_JNEXT_LUAPARA;
					if (bhavenext)
					{
						_maxtime = _obj.GetInteger();
					}
					selsys[_selsys].Setup(_nselect, _select, _keyplus, _keyminus, _keyok, _keycancel, _selsys, _maxtime);

					if (argscount == 3)
					{
						_GETPARAS(3);
						int _nPageNumber = _INEXT_LUAPARA;
						float _fadebegin = _FNEXT_LUAPARA;
						float _offset = _FNEXT_LUAPARA;

						int _initshift = 0;
						int _shiftangle = 9000;
						_JNEXT_LUAPARA;
						if (bhavenext)
						{
							_initshift = _obj.GetInteger();
							_JNEXT_LUAPARA;
							if (bhavenext)
							{
								_shiftangle = _obj.GetInteger();
							}
						}
						selsys[_selsys].SetPageNumber(_nPageNumber, _fadebegin, _offset, _initshift, _shiftangle);
					}
				}
			}
		}
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