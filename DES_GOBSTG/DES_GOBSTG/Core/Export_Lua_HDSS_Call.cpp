#ifndef __NOTUSELUA
#ifndef __NOTUSEHDSS

#include "../Header/Export_Lua.h"
#include "../Header/LuaConstDefine.h"
#include "../Header/Processprep.h"

#define _NEXT_HDSS_LUAPARA		(_para.GetByIndex(++ii))
#define _INEXT_HDSS_LUAPARA		(_NEXT_HDSS_LUAPARA.GetInteger())
#define _FNEXT_HDSS_LUAPARA		(_NEXT_HDSS_LUAPARA.GetFloat())
#define _BNEXT_HDSS_LUAPARA		(_NEXT_HDSS_LUAPARA.GetBoolean())
#define _ONEXT_HDSS_LUAPARA		(_obj = _NEXT_HDSS_LUAPARA)

#define _IOBJ_HDSS_LUAPARA		(_obj.GetInteger())
#define _FOBJ_HDSS_LUAPARA		(_obj.GetFloat())
#define _BOBJ_HDSS_LUAPARA		(_obj.GetBoolean())
#define _SOBJ_HDSS_LUAPARA		((char *)_obj.GetString())
#define _COBJ_HDSS_LUAPARA		(_LuaHelper_GetColor(&_obj))
#define _DOBJ_HDSS_LUAPARA		(_LuaHelper_GetDWORD(&_obj))

#define _NILCHECK_HDSS_LUAPARA	(!_obj.IsNil())
#define _JNEXT_HDSS_LUAPARA		_ONEXT_HDSS_LUAPARA;	bhavenext = _NILCHECK_HDSS_LUAPARA
#define _GETPARAS_HDSS_LUAPARA(X)		if (!_Helper_HDSS_GetPara(&args, (X), &_para))	return false;	ii = 0

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

	LuaObject _para;
	int ii;
	LuaObject _obj;
	bool bhavenext;

	_GETPARAS_HDSS_LUAPARA(2);
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
				time = _INEXT_HDSS_LUAPARA;
				return 0;
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
				if (argscount == 2)
				{
					int _index = _INEXT_HDSS_LUAPARA;
					int _siid = _INEXT_HDSS_LUAPARA;
					float _cenx = _FNEXT_HDSS_LUAPARA;
					float _ceny = _FNEXT_HDSS_LUAPARA;
					float _w = _FNEXT_HDSS_LUAPARA;
					float _h = _FNEXT_HDSS_LUAPARA;

					DWORD _col = 0xffffffff;
					_JNEXT_HDSS_LUAPARA;
					if (bhavenext)
					{
						_col = _COBJ_HDSS_LUAPARA;
					}

					ubg[_index]->valueSet(mp.tex, _siid, _cenx, _ceny, _w, _h, _col);
				}
				return 0;
			case SCR_BGVALEX:
				if (argscount == 2)
				{
					int _index = _INEXT_HDSS_LUAPARA;
					int _siid = _INEXT_HDSS_LUAPARA;
					float _x = _FNEXT_HDSS_LUAPARA;
					float _y = _FNEXT_HDSS_LUAPARA;
					float _z = _FNEXT_HDSS_LUAPARA;
					float _w = _FNEXT_HDSS_LUAPARA;
					float _h = _FNEXT_HDSS_LUAPARA;
					int _rotx = _INEXT_HDSS_LUAPARA;
					int _roty = _INEXT_HDSS_LUAPARA;
					int _rotz = _INEXT_HDSS_LUAPARA;

					float _paral = 0;
					float _speed = 0;
					float _angle = 0;
					bool _move = false;
					bool _rotate = false;
					DWORD _col = 0xffffffff;
					_JNEXT_HDSS_LUAPARA;
					if (bhavenext)
					{
						_paral = _FOBJ_HDSS_LUAPARA;
						_JNEXT_HDSS_LUAPARA;
						if (bhavenext)
						{
							_speed = _FOBJ_HDSS_LUAPARA;
							_JNEXT_HDSS_LUAPARA;
							if (bhavenext)
							{
								_move = _BOBJ_HDSS_LUAPARA;
								_JNEXT_HDSS_LUAPARA;
								if (bhavenext)
								{
									_rotate = _BOBJ_HDSS_LUAPARA;
									_JNEXT_HDSS_LUAPARA;
									if (bhavenext)
									{
										_col = _COBJ_HDSS_LUAPARA;
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
				if (argscount > 1 && argscount <= 4)
				{
					int _selsys = _INEXT_HDSS_LUAPARA;
					int _id = _INEXT_HDSS_LUAPARA;
					int _siid = _INEXT_HDSS_LUAPARA;
					float _cenx = _FNEXT_HDSS_LUAPARA;
					float _ceny = _FNEXT_HDSS_LUAPARA;

					float _hscale = 1.0f;
					float _vscale = 0.0f;
					BYTE _flag = SEL_NULL;
					_JNEXT_HDSS_LUAPARA;
					if (bhavenext)
					{
						_hscale = _FOBJ_HDSS_LUAPARA;
						_JNEXT_HDSS_LUAPARA;
						if (bhavenext)
						{
							_vscale = _FOBJ_HDSS_LUAPARA;
							_JNEXT_HDSS_LUAPARA;
							if (bhavenext)
							{
								_flag = _IOBJ_HDSS_LUAPARA;
							}
						}
					}

					Selector * _selector = selsys[_selsys].BuildSelector(_id, _siid, _cenx, _ceny, _hscale, _vscale, _flag);

					if (argscount > 2)
					{
						_GETPARAS_HDSS_LUAPARA(3);

						seladj _adj[SEL_STATEMAX];
						ZeroMemory(_adj, sizeof(seladj)*SEL_STATEMAX);
						bool _havestate[SEL_STATEMAX];
						_JNEXT_HDSS_LUAPARA;
						if (bhavenext)
						{
							_havestate[0] = true;
							_adj[0].xadj = _FOBJ_HDSS_LUAPARA + _cenx;
							_JNEXT_HDSS_LUAPARA;
							if (bhavenext)
							{
								_adj[0].yadj = _FOBJ_HDSS_LUAPARA + _ceny;
								_JNEXT_HDSS_LUAPARA;
								if (bhavenext)
								{
									_havestate[1] = true;
									_adj[1].xadj = _FOBJ_HDSS_LUAPARA + _cenx;
									_JNEXT_HDSS_LUAPARA;
									if (bhavenext)
									{
										_adj[1].yadj = _FOBJ_HDSS_LUAPARA + _ceny;
										_JNEXT_HDSS_LUAPARA;
										if (bhavenext)
										{
											_havestate[2] = true;
											_adj[2].xadj = _FOBJ_HDSS_LUAPARA + _cenx;
											_JNEXT_HDSS_LUAPARA;
											if (bhavenext)
											{
												_adj[2].yadj = _FOBJ_HDSS_LUAPARA + _ceny;
												_JNEXT_HDSS_LUAPARA;
												if (bhavenext)
												{
													_havestate[3] = true;
													_adj[3].xadj = _FOBJ_HDSS_LUAPARA + _cenx;
													_JNEXT_HDSS_LUAPARA;
													if (bhavenext)
													{
														_adj[3].yadj = _FOBJ_HDSS_LUAPARA + _ceny;
														_JNEXT_HDSS_LUAPARA;
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

						if (argscount > 3)
						{
							_GETPARAS_HDSS_LUAPARA(4);

							char * _info = NULL;
							DWORD _ucol = 0xFFFFFFFF;
							DWORD _dcol = 0xFFFFFFFF;
							float _shadow = FONTSYS_DEFAULT_SHADOW;
							float _xoffset = 0;
							float _yoffset = 0;
							_hscale = 1.0f;
							_vscale = 0.0f;
							BYTE _alignflag = HGETEXT_CENTER|HGETEXT_MIDDLE;
							bool _sync = false;

							_JNEXT_HDSS_LUAPARA;
							if (bhavenext)
							{
								_info = _SOBJ_HDSS_LUAPARA;
								_JNEXT_HDSS_LUAPARA;
								if (bhavenext)
								{
									_ucol = _COBJ_HDSS_LUAPARA;
									_JNEXT_HDSS_LUAPARA;
									if (bhavenext)
									{
										_dcol = _COBJ_HDSS_LUAPARA;
										_JNEXT_HDSS_LUAPARA;
										if (bhavenext)
										{
											_shadow = _FOBJ_HDSS_LUAPARA;
											_JNEXT_HDSS_LUAPARA;
											if (bhavenext)
											{
												_xoffset = _FOBJ_HDSS_LUAPARA;
												_JNEXT_HDSS_LUAPARA;
												if (bhavenext)
												{
													_yoffset = _FOBJ_HDSS_LUAPARA;
													_JNEXT_HDSS_LUAPARA;
													if (bhavenext)
													{
														_hscale = _FOBJ_HDSS_LUAPARA;
														_JNEXT_HDSS_LUAPARA;
														if (bhavenext)
														{
															_vscale = _FOBJ_HDSS_LUAPARA;
															_JNEXT_HDSS_LUAPARA;
															if (bhavenext)
															{
																_alignflag = _IOBJ_HDSS_LUAPARA;
																_JNEXT_HDSS_LUAPARA;
																if (bhavenext)
																{
																	_sync = _BOBJ_HDSS_LUAPARA;
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
							_selector->infoSet(_info, _ucol, _dcol, _shadow, _xoffset, _yoffset, _hscale, _vscale, _alignflag, _sync);
						}
					}
				}
				break;
			case SCR_SELSET:
				if (argscount > 1 && argscount <= 3)
				{
					int _selsys = _INEXT_HDSS_LUAPARA;
					int _nselect = _INEXT_HDSS_LUAPARA;
					int _select = _INEXT_HDSS_LUAPARA;
					BYTE _keyplus = _INEXT_HDSS_LUAPARA;
					BYTE _keyminus = _INEXT_HDSS_LUAPARA;
					BYTE _keyok = _INEXT_HDSS_LUAPARA;
					BYTE _keycancel = _INEXT_HDSS_LUAPARA;

					int _maxtime = SELSYS_DEFAULTMAXTIME;
					_JNEXT_HDSS_LUAPARA;
					if (bhavenext)
					{
						_maxtime = _INEXT_HDSS_LUAPARA;
					}
					selsys[_selsys].Setup(_nselect, _select, _keyplus, _keyminus, _keyok, _keycancel, _selsys, _maxtime);

					if (argscount > 2)
					{
						_GETPARAS_HDSS_LUAPARA(3);
						int _nPageNumber = _INEXT_HDSS_LUAPARA;
						float _fadebegin = _FNEXT_HDSS_LUAPARA;
						float _offset = _FNEXT_HDSS_LUAPARA;

						int _initshift = 0;
						int _shiftangle = 9000;
						_JNEXT_HDSS_LUAPARA;
						if (bhavenext)
						{
							_initshift = _INEXT_HDSS_LUAPARA;
							_JNEXT_HDSS_LUAPARA;
							if (bhavenext)
							{
								_shiftangle = _INEXT_HDSS_LUAPARA;
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

#endif
#endif