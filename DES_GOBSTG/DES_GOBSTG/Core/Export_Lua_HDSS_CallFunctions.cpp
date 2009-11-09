#ifndef __NOTUSELUA
#ifndef __NOTUSEHDSS

#include "Export_Lua_HDSS_CallGet.h"
#include "processPrep.h"

#include "../Header/Export_Lua_HDSS_CallGetDefine.h"

_HDSSCallGet::_HDSSCallGet()
{
}

_HDSSCallGet::~_HDSSCallGet()
{

}

int _HDSSCallGet::Call_SETSTATE(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;

	if (true)
	{
		int _state = _INEXT_HDSS_LUAPARA;

		int _time = 0;
		_JNEXT_HDSS_LUAPARA;
		if (bhavenext)
		{
			_time = _IOBJ_HDSS_LUA;
		}

		mp.SetState(_state, _time);
	}
	return 0;
}

int _HDSSCallGet::Call_SETTIME(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;

	if (true)
	{
		time = _INEXT_HDSS_LUAPARA;
	}
	return 0;
}

int _HDSSCallGet::Call_RETURN(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;

	if (true)
	{
		int _retvalue = _INEXT_HDSS_LUAPARA;
		mp.SetReturnValue(_retvalue);
	}
	return 0;
}

int _HDSSCallGet::Call_SE(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;

	if (true)
	{
		int _type = _INEXT_HDSS_LUAPARA;

		float _x = M_ACTIVECLIENT_CENTER_X;
		_JNEXT_HDSS_LUAPARA;
		if (bhavenext)
		{
			_x = _FOBJ_HDSS_LUA;
		}
		SE::push(_type, _x);
	}
	return 0;
}

int _HDSSCallGet::Call_BGVALUE(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;
	if (true)
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
			_col = _COBJ_HDSS_LUA;
		}

		ubg[_index]->valueSet(mp.tex, _siid, _cenx, _ceny, _w, _h, _col);
	}
	return 0;
}

int _HDSSCallGet::Call_BGVALEX(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;
	if (true)
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
			_paral = _FOBJ_HDSS_LUA;
			_JNEXT_HDSS_LUAPARA;
			if (bhavenext)
			{
				_speed = _FOBJ_HDSS_LUA;
				_JNEXT_HDSS_LUAPARA;
				if (bhavenext)
				{
					_move = _BOBJ_HDSS_LUA;
					_JNEXT_HDSS_LUAPARA;
					if (bhavenext)
					{
						_rotate = _BOBJ_HDSS_LUA;
						_JNEXT_HDSS_LUAPARA;
						if (bhavenext)
						{
							_col = _COBJ_HDSS_LUA;
						}
					}
				}
			}
		}

		ubg[_index]->valueSet(mp.tex, _siid, _x, _y, _z, _w, _h, _rotx, _roty, _rotz, _paral, _speed, _angle, _move, _rotate, _col);
	}
	return 0;
}

int _HDSSCallGet::Call_SELBUILD(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;

	if (true)
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
			_hscale = _FOBJ_HDSS_LUA;
			_JNEXT_HDSS_LUAPARA;
			if (bhavenext)
			{
				_vscale = _FOBJ_HDSS_LUA;
				_JNEXT_HDSS_LUAPARA;
				if (bhavenext)
				{
					_flag = _IOBJ_HDSS_LUA;
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
				_adj[0].xadj = _FOBJ_HDSS_LUA + _cenx;
				_JNEXT_HDSS_LUAPARA;
				if (bhavenext)
				{
					_adj[0].yadj = _FOBJ_HDSS_LUA + _ceny;
					_JNEXT_HDSS_LUAPARA;
					if (bhavenext)
					{
						_havestate[1] = true;
						_adj[1].xadj = _FOBJ_HDSS_LUA + _cenx;
						_JNEXT_HDSS_LUAPARA;
						if (bhavenext)
						{
							_adj[1].yadj = _FOBJ_HDSS_LUA + _ceny;
							_JNEXT_HDSS_LUAPARA;
							if (bhavenext)
							{
								_havestate[2] = true;
								_adj[2].xadj = _FOBJ_HDSS_LUA + _cenx;
								_JNEXT_HDSS_LUAPARA;
								if (bhavenext)
								{
									_adj[2].yadj = _FOBJ_HDSS_LUA + _ceny;
									_JNEXT_HDSS_LUAPARA;
									if (bhavenext)
									{
										_havestate[3] = true;
										_adj[3].xadj = _FOBJ_HDSS_LUA + _cenx;
										_JNEXT_HDSS_LUAPARA;
										if (bhavenext)
										{
											_adj[3].yadj = _FOBJ_HDSS_LUA + _ceny;
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
					_info = _SOBJ_HDSS_LUA;
					_JNEXT_HDSS_LUAPARA;
					if (bhavenext)
					{
						_ucol = _COBJ_HDSS_LUA;
						_JNEXT_HDSS_LUAPARA;
						if (bhavenext)
						{
							_dcol = _COBJ_HDSS_LUA;
							_JNEXT_HDSS_LUAPARA;
							if (bhavenext)
							{
								_shadow = _FOBJ_HDSS_LUA;
								_JNEXT_HDSS_LUAPARA;
								if (bhavenext)
								{
									_xoffset = _FOBJ_HDSS_LUA;
									_JNEXT_HDSS_LUAPARA;
									if (bhavenext)
									{
										_yoffset = _FOBJ_HDSS_LUA;
										_JNEXT_HDSS_LUAPARA;
										if (bhavenext)
										{
											_hscale = _FOBJ_HDSS_LUA;
											_JNEXT_HDSS_LUAPARA;
											if (bhavenext)
											{
												_vscale = _FOBJ_HDSS_LUA;
												_JNEXT_HDSS_LUAPARA;
												if (bhavenext)
												{
													_alignflag = _IOBJ_HDSS_LUA;
													_JNEXT_HDSS_LUAPARA;
													if (bhavenext)
													{
														_sync = _BOBJ_HDSS_LUA;
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
	return 0;
}

int _HDSSCallGet::Call_SELSET(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;

	if (true)
	{
		int _selsys = _INEXT_HDSS_LUAPARA;
		int _nselect = _INEXT_HDSS_LUAPARA;
		int _select = _INEXT_HDSS_LUAPARA;

		BYTE _keyplus = PUSHKEY_KEYNULL;
		BYTE _keyminus = PUSHKEY_KEYNULL;
		BYTE _keyok = PUSHKEY_KEYNULL;
		BYTE _keycancel = PUSHKEY_KEYNULL;
		int _maxtime = SELSYS_DEFAULTMAXTIME;
		_JNEXT_HDSS_LUAPARA;
		if (bhavenext)
		{
			_keyplus = _IOBJ_HDSS_LUA;
			_JNEXT_HDSS_LUAPARA;
			if (bhavenext)
			{
				_keyminus = _IOBJ_HDSS_LUA;
				_JNEXT_HDSS_LUAPARA;
				if (bhavenext)
				{
					_keyok = _IOBJ_HDSS_LUA;
					_JNEXT_HDSS_LUAPARA;
					if (bhavenext)
					{
						_keycancel = _IOBJ_HDSS_LUA;
						_JNEXT_HDSS_LUAPARA;
						if (bhavenext)
						{
							_maxtime = _IOBJ_HDSS_LUA;
						}
					}
				}
			}
		}
		selsys[_selsys].Setup(_selsys, _nselect, _select, _keyplus, _keyminus, _keyok, _keycancel, _maxtime);

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
				_initshift = _IOBJ_HDSS_LUA;
				_JNEXT_HDSS_LUAPARA;
				if (bhavenext)
				{
					_shiftangle = _IOBJ_HDSS_LUA;
				}
			}
			selsys[_selsys].SetPageNumber(_nPageNumber, _fadebegin, _offset, _initshift, _shiftangle);
		}
	}
	return 0;
}

int _HDSSCallGet::Call_SELCLEAR(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;

	if (true)
	{
		int _selsys = _INEXT_HDSS_LUAPARA;
		selsys[_selsys].Clear();
	}
	return 0;
}
#endif
#endif