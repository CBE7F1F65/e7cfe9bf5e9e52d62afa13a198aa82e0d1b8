#ifndef __NOTUSELUA
#ifndef __NOTUSEHDSS

#include "Export_Lua_HDSS.h"
#include "Export_Lua_HDSS_CallGet.h"
#include "processPrep.h"

#include "../Header/Export_Lua_HDSS_CallGetDefine.h"

bool _HDSSCallGet::bhavenext=false;
LuaObject _HDSSCallGet::_para;
LuaObject _HDSSCallGet::_obj;
int _HDSSCallGet::ii=0;
int _HDSSCallGet::argscount=0;

_HDSSCallGet::_HDSSCallGet()
{
}

_HDSSCallGet::~_HDSSCallGet()
{

}

int _HDSSCallGet::Call_SD(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;

	if (true)
	{
		int _index = _INEXT_HDSS_LUAPARA;
		int _ival = _INEXT_HDSS_LUAPARA;
		scr.SetValue(_index, &_ival, false);
	}
	return 0;
}

int _HDSSCallGet::Call_SDf(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;

	if (true)
	{
		int _index = _INEXT_HDSS_LUAPARA;
		_ONEXT_HDSS_LUAPARA;
		DWORD _dval = _DOBJ_HDSS_LUA;
		scr.SetValue(_index, &_dval, true);
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

int _HDSSCallGet::Call_SETCHARA(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;

	if (true)
	{
		BYTE _playerindex = _INEXT_HDSS_LUAPARA;
		WORD _id = _INEXT_HDSS_LUAPARA;
		WORD _id_sub_1 = 0xffff;
		WORD _id_sub_2 = 0xffff;
		_JNEXT_HDSS_LUAPARA;
		if (bhavenext)
		{
			_id_sub_1 = _IOBJ_HDSS_LUA;
			_JNEXT_HDSS_LUAPARA;
			if (bhavenext)
			{
				_id_sub_2 = _IOBJ_HDSS_LUA;
			}
		}
		Player::p[_playerindex].SetChara(_id, _id_sub_1, _id_sub_2);
	}
	return 0;
}

int _HDSSCallGet::Call_STARTPREP(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;

	if (true)
	{
		bool _callinit = false;
		_JNEXT_HDSS_LUAPARA;
		if (bhavenext)
		{
			_callinit = _BOBJ_HDSS_LUA;
		}
		mp.startPrep(_callinit);
	}
	return 0;
}

int _HDSSCallGet::Call_SETPUSHEVENT(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;

	if (true)
	{
		BYTE _index = _INEXT_HDSS_LUAPARA;
		int _pushkey_1 = PUSHKEY_KEYNULL;
		int _pushkey_2 = PUSHKEY_KEYNULL;
		int _pushkey_3 = PUSHKEY_KEYNULL;
		int _pushkey_4 = PUSHKEY_KEYNULL;
		int _pushfirst = M_PUSH_FIRST;
		int _pushrollto = M_PUSH_ROLLTO;
		_JNEXT_HDSS_LUAPARA;
		if (bhavenext)
		{
			_pushkey_1 = _IOBJ_HDSS_LUA;
			_JNEXT_HDSS_LUAPARA;
			if (bhavenext)
			{
				_pushkey_2 = _IOBJ_HDSS_LUA;
				_JNEXT_HDSS_LUAPARA;
				if (bhavenext)
				{
					_pushkey_3 = _IOBJ_HDSS_LUA;
					_JNEXT_HDSS_LUAPARA;
					if (bhavenext)
					{
						_pushkey_4 = _IOBJ_HDSS_LUA;
						_JNEXT_HDSS_LUAPARA;
						if (bhavenext)
						{
							_pushfirst = _IOBJ_HDSS_LUA;
							_JNEXT_HDSS_LUAPARA;
							if (bhavenext)
							{
								_pushrollto = _IOBJ_HDSS_LUA;
							}
						}
					}
				}
			}
		}
		bool bret = PushKey::SetPushEvent(_index, _pushkey_1, _pushkey_2, _pushkey_3, _pushkey_4, _pushfirst, _pushrollto);
		ls->PushBoolean(bret);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Call_UPDATEPUSHEVENT(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;

	if (true)
	{
		BYTE _index = _INEXT_HDSS_LUAPARA;
		bool bret = PushKey::UpdatePushEvent(_index);
		ls->PushBoolean(bret);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Call_SE(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;

	if (true)
	{
		int _type = _INEXT_HDSS_LUAPARA;

		float _x = M_CLIENT_CENTER_X;
		_JNEXT_HDSS_LUAPARA;
		if (bhavenext)
		{
			_x = _FOBJ_HDSS_LUA;
		}
		SE::push(_type, _x);
	}
	return 0;
}

int _HDSSCallGet::Call_HSVTORGB(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;

	if (true)
	{
		float _h = _FNEXT_HDSS_LUAPARA;
		float _s = _FNEXT_HDSS_LUAPARA;
		float _v = _FNEXT_HDSS_LUAPARA;
		float _a = _FNEXT_HDSS_LUAPARA;
		hgeColorHSV _hsv(_h, _s, _v, _a);
		_PD_HDSS_LUA(_hsv.GetHWColor());
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Call_PRINT(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;

	if (true)
	{
		float _x = _FNEXT_HDSS_LUAPARA;
		float _y = _FNEXT_HDSS_LUAPARA;
		char * _str = _SNEXT_HDSS_LUAPARA;

		int _align = HGETEXT_CENTER | HGETEXT_MIDDLE;
		hgeFont * _font = NULL;
		float _scale = 1.0f;
		float _properation = 1.0f;
		float _rotation = 0;
		float _tracking = 0;
		float _spacing = 1.0f;
		_JNEXT_HDSS_LUAPARA;
		if (bhavenext)
		{
			_align = _IOBJ_HDSS_LUA;
			_JNEXT_HDSS_LUAPARA;
			if (bhavenext)
			{
				_font = (hgeFont *)_DOBJ_HDSS_LUA;
			}
		}
		if (argscount > 2)
		{
			_GETPARAS_HDSS_LUAPARA(3);

			_JNEXT_HDSS_LUAPARA;
			if (bhavenext)
			{
				_scale = _FOBJ_HDSS_LUA;
				_JNEXT_HDSS_LUAPARA;
				if (bhavenext)
				{
					_properation = _FOBJ_HDSS_LUA;
					_JNEXT_HDSS_LUAPARA;
					if (bhavenext)
					{
						_rotation = _FOBJ_HDSS_LUA;
						_JNEXT_HDSS_LUAPARA;
						if (bhavenext)
						{
							_tracking = _FOBJ_HDSS_LUA;
							_JNEXT_HDSS_LUAPARA;
							if (bhavenext)
							{
								_spacing = _FOBJ_HDSS_LUA;
							}
						}
					}
				}
			}
		}
		FrontDisplay::fdisp.BuildPostPrint(_font, _x, _y, _str, _align, _scale, _properation, _rotation, _tracking, _spacing);
	}
	return 0;
}

int _HDSSCallGet::Call_FRONTSPRITE(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;

	if (true)
	{
		DWORD dret;
		int _ID = _INEXT_HDSS_LUAPARA;
		int _index = _INEXT_HDSS_LUAPARA;
		dret = (DWORD)SpriteItemManager::BuildFrontSprite(_ID, _index);
		
		if (argscount > 2)
		{
			_GETPARAS_HDSS_LUAPARA(3);

			float _x = _FNEXT_HDSS_LUAPARA;
			float _y = _FNEXT_HDSS_LUAPARA;
			int _angle = 0;
			float _hscale = 1.0f;
			float _vscale = 0.0f;
			_JNEXT_HDSS_LUAPARA;
			if (bhavenext)
			{
				_angle = _IOBJ_HDSS_LUA;
				_JNEXT_HDSS_LUAPARA;
				if (bhavenext)
				{
					_hscale = _FOBJ_HDSS_LUA;
					_JNEXT_HDSS_LUAPARA;
					if (bhavenext)
					{
						_vscale = _FOBJ_HDSS_LUA;
					}
				}
			}
			SpriteItemManager::SetFrontSpriteValue(_ID, _x, _y, _angle, _hscale, _vscale);
		}

		_PD_HDSS_LUA(dret);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Call_FREEFRONTSPRITE(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;

	if (true)
	{
		int _ID = -1;
		_JNEXT_HDSS_LUAPARA;
		if (bhavenext)
		{
			_ID = _IOBJ_HDSS_LUA;
		}
		SpriteItemManager::FreeFrontSprite(_ID);
	}
	return 0;
}

int _HDSSCallGet::Call_ENBUILD(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;
	if (true)
	{
		WORD _eID = _INEXT_HDSS_LUAPARA;
		BYTE _playerindex = _INEXT_HDSS_LUAPARA;
		float _x = _FNEXT_HDSS_LUAPARA;
		float _y = _FNEXT_HDSS_LUAPARA;
		int _angle = _INEXT_HDSS_LUAPARA;
		float _speed = _FNEXT_HDSS_LUAPARA;
		BYTE _type = _INEXT_HDSS_LUAPARA;
		float _life = _FNEXT_HDSS_LUAPARA;
		int _infitimer = _INEXT_HDSS_LUAPARA;
		int _enindex = Enemy::Build(_eID, _playerindex, _x, _y, _angle, _speed, _type, _life, _infitimer);

		if (_enindex >= 0)
		{
			if (argscount > 2)
			{
				Enemy * _pen = &(Enemy::en[_playerindex][_enindex]);
				_GETPARAS_HDSS_LUAPARA(3);
				BYTE _tarID = _INEXT_HDSS_LUAPARA;
				_pen->setTar(_tarID);

				if (argscount > 3)
				{
					_GETPARAS_HDSS_LUAPARA(4);
					_JNEXT_HDSS_LUAPARA;
					DWORD _take = _DOBJ_HDSS_LUA;
					_pen->setTake(_take);
				}
			}

			_PI_HDSS_LUA(_enindex);
			return 1;
		}
	}
	return 0;
}

int _HDSSCallGet::Call_ENACTIONSET(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;
	if (true)
	{
		WORD _ac = _INEXT_HDSS_LUAPARA;
		BYTE _playerindex = _INEXT_HDSS_LUAPARA;
		float _para0 = 0;
		float _para1 = 0;
		float _para2 = 0;
		float _para3 = 0;
		_JNEXT_HDSS_LUAPARA;
		if (bhavenext)
		{
			_para0 = _FOBJ_HDSS_LUA;
			_JNEXT_HDSS_LUAPARA;
			if (bhavenext)
			{
				_para1 = _FOBJ_HDSS_LUA;
				_JNEXT_HDSS_LUAPARA;
				if (bhavenext)
				{
					_para2 = _FOBJ_HDSS_LUA;
					_JNEXT_HDSS_LUAPARA;
					if (bhavenext)
					{
						_para3 = _FOBJ_HDSS_LUA;
					}
				}
			}
		}
		(*Enemy::en[_playerindex]).setAction(_ac, _para0, _para1, _para2, _para3);
	}
	return 0;
}

int _HDSSCallGet::Call_ENAZBUILD(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;
	if (true)
	{
		BYTE _playerindex = _INEXT_HDSS_LUAPARA;
		BYTE _flag = _INEXT_HDSS_LUAPARA;
		float _x = _FNEXT_HDSS_LUAPARA;
		float _y = _FNEXT_HDSS_LUAPARA;
		float _rPrep = _FNEXT_HDSS_LUAPARA;
		float _rParal = 0;
		int _angle = 9000;
		_JNEXT_HDSS_LUAPARA;
		if (bhavenext)
		{
			_rParal = _FOBJ_HDSS_LUA;
			_JNEXT_HDSS_LUAPARA;
			if (bhavenext)
			{
				_angle = _IOBJ_HDSS_LUA;
			}
		}
		Enemy::BuildENAZ(_playerindex, _flag, _x, _y, _rPrep, _rParal, _angle);
	}
	return 0;
}

int _HDSSCallGet::Call_RAMA(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;
	if (true)
	{
		bool _brma = _BNEXT_HDSS_LUAPARA;
		float _x = _FNEXT_HDSS_LUAPARA;
		float _y = _FNEXT_HDSS_LUAPARA;
		int _angle;
		float _r;
		int iret;
		if (_brma)
		{
			_r = _FNEXT_HDSS_LUAPARA;
		}
		else
		{
			_angle = _INEXT_HDSS_LUAPARA;
		}
		float _aimx = _FNEXT_HDSS_LUAPARA;
		float _aimy = _FNEXT_HDSS_LUAPARA;
		if (_brma)
		{
			iret = BObject::RMainAngle(_x, _y, _aimx, _aimy, _r);
		}
		else
		{
			iret = BObject::AMainAngle(_x, _y, _aimx, _aimy, _angle);
		}
		_PI_HDSS_LUA(iret);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Call_COLLISION_CIRCLE(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;
	if (true)
	{
		float _x = _FNEXT_HDSS_LUAPARA;
		float _y = _FNEXT_HDSS_LUAPARA;
		float _aimx = _FNEXT_HDSS_LUAPARA;
		float _aimy = _FNEXT_HDSS_LUAPARA;
		float _r = _FNEXT_HDSS_LUAPARA;
		bool _bbig = false;
		_JNEXT_HDSS_LUAPARA;
		if (bhavenext)
		{
			_bbig = _BOBJ_HDSS_LUA;
		}
		bool bret;
		if (_bbig)
		{
			bret = BObject::CheckCollisionBigCircle(_x, _y, _aimx, _aimy, _r);
		}
		else
		{
			bret = BObject::CheckCollisionCircle(_x, _y, _aimx, _aimy, _r);
		}
		ls->PushBoolean(bret);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Call_SETPINITLIFE(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;
	if (true)
	{
		BYTE _playerindex = _INEXT_HDSS_LUAPARA;
		BYTE _initlife = _INEXT_HDSS_LUAPARA;
		Player::p[_playerindex].SetInitLife(_initlife);
	}
	return 0;
}

int _HDSSCallGet::Call_BUBUILD(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;
	if (true)
	{
		BYTE _playerindex = _INEXT_HDSS_LUAPARA;
		float _x = _FNEXT_HDSS_LUAPARA;
		float _y = _FNEXT_HDSS_LUAPARA;
		bool _absolute = _BNEXT_HDSS_LUAPARA;
		int _angle = _INEXT_HDSS_LUAPARA;
		float _speed = _FNEXT_HDSS_LUAPARA;
		BYTE _type = _INEXT_HDSS_LUAPARA;
		BYTE _color = _INEXT_HDSS_LUAPARA;

		int _fadeintime = BULLET_FADEINTIME;
		float _avoid = 0;
		BYTE _tarID = 0xff;
		_JNEXT_HDSS_LUAPARA;
		if (bhavenext)
		{
			_fadeintime = _IOBJ_HDSS_LUA;
			_JNEXT_HDSS_LUAPARA;
			if (bhavenext)
			{
				_avoid = _FOBJ_HDSS_LUA;
				_JNEXT_HDSS_LUAPARA;
				if (bhavenext)
				{
					_tarID = _IOBJ_HDSS_LUA;
				}
			}
		}

		int iret = Bullet::Build(_playerindex, _x, _y, _absolute, _angle, _speed, _type, _color, _fadeintime, _avoid, _tarID);
		_PI_HDSS_LUA(iret);
		return 1;
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

		float _w = -1;
		float _h = -1;
		DWORD _col = 0xffffffff;
		_JNEXT_HDSS_LUAPARA;
		if (bhavenext)
		{
			_w = _FOBJ_HDSS_LUA;
			_JNEXT_HDSS_LUAPARA;
			if (bhavenext)
			{
				_h = _FOBJ_HDSS_LUA;
				_JNEXT_HDSS_LUAPARA;
				if (bhavenext)
				{
					_col = _COBJ_HDSS_LUA;
				}
			}
		}

		BGLayer::ubg[_index].valueSet(_siid, _cenx, _ceny, _w, _h, _col);
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

		DWORD _col = 0xffffffff;
		_JNEXT_HDSS_LUAPARA;
		if (bhavenext)
		{
			_col = _COBJ_HDSS_LUA;
		}

		BGLayer::ubg[_index].valueSet(_siid, 0, 0, 0, 0, _col);

		if (argscount > 2)
		{
			_GETPARAS_HDSS_LUAPARA(3);
			float _x = _FNEXT_HDSS_LUAPARA;
			float _y = _FNEXT_HDSS_LUAPARA;
			float _z = _FNEXT_HDSS_LUAPARA;

			float _w = -1;
			float _h = -1;
			int _rotx = 0;
			int _roty = 0;
			int _rotz = 0;
			float _paral = 0;

			_JNEXT_HDSS_LUAPARA;
			if (bhavenext)
			{
				_w = _FOBJ_HDSS_LUA;
				_JNEXT_HDSS_LUAPARA;
				if (bhavenext)
				{
					_h = _FOBJ_HDSS_LUA;
					_JNEXT_HDSS_LUAPARA;
					if (bhavenext)
					{
						_rotx = _IOBJ_HDSS_LUA;
						_JNEXT_HDSS_LUAPARA;
						if (bhavenext)
						{
							_roty = _IOBJ_HDSS_LUA;
							_JNEXT_HDSS_LUAPARA;
							if (bhavenext)
							{
								_rotz = _IOBJ_HDSS_LUA;
								_JNEXT_HDSS_LUAPARA;
								if (bhavenext)
								{
									_paral = _FOBJ_HDSS_LUA;
								}
							}
						}
					}
				}
			}

			BGLayer::ubg[_index].rectSet(_x, _y, _z, _w, _h, _rotx, _roty, _rotz);
			BGLayer::ubg[_index].parallelogram(_paral);

			if (argscount > 3)
			{
				_GETPARAS_HDSS_LUAPARA(4);

				float _speed = _FNEXT_HDSS_LUAPARA;

				int _angle = 9000;
				bool _move = false;
				bool _rotate = false;

				_JNEXT_HDSS_LUAPARA;
				if (bhavenext)
				{
					_angle = _IOBJ_HDSS_LUA;
					_JNEXT_HDSS_LUAPARA;
					if (bhavenext)
					{
						_move = _BOBJ_HDSS_LUA;
						_JNEXT_HDSS_LUAPARA;
						if (bhavenext)
						{
							_rotate = _BOBJ_HDSS_LUA;
						}
					}
				}
				BGLayer::ubg[_index].moveSet(_speed, _angle, _move, _rotate);
			}
		}
	}
	return 0;
}

int _HDSSCallGet::Call_BGFLAG(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;

	if (true)
	{
		int _index = _INEXT_HDSS_LUAPARA;
		BYTE _flag = _INEXT_HDSS_LUAPARA;
		int _maxtime = -1;
		_JNEXT_HDSS_LUAPARA;
		if (bhavenext)
		{
			_maxtime = _IOBJ_HDSS_LUA;
		}
		BGLayer::ubg[_index].SetFlag(_flag, _maxtime);
	}
	return 0;
}

int _HDSSCallGet::Call_BGCOLOR(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;

	if (true)
	{
		int _index = _INEXT_HDSS_LUAPARA;
		DWORD col[4];
		for (int i=0; i<4; i++)
		{
			_JNEXT_HDSS_LUAPARA;
			col[i] = _COBJ_HDSS_LUA;
		}

		BGLayer::ubg[_index].colorSet(col[0], col[1], col[2], col[3]);
	}
	return 0;
}

int _HDSSCallGet::Call_BGOFF(LuaState * ls)
{
	_ENTERCALL_HDSS_LUA;

	if (true)
	{
		int _index = _INEXT_HDSS_LUAPARA;
		if (_index < 0)
		{
			BGLayer::KillOtherLayer();
		}
		else
		{
			BGLayer::ubg[_index].exist = false;
		}
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

int _HDSSCallGet::Call_SELSETUP(LuaState * ls)
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

			if (argscount > 3)
			{
				_GETPARAS_HDSS_LUAPARA(4);
				int _selectframeSIID = _INEXT_HDSS_LUAPARA;
				float _x = _FNEXT_HDSS_LUAPARA;
				float _y = _FNEXT_HDSS_LUAPARA;
				selsys[_selsys].SetSelectFrame(_selectframeSIID, _x, _y);
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
		int _select = -1;
		_JNEXT_HDSS_LUAPARA;
		if (bhavenext)
		{
			_select = _IOBJ_HDSS_LUA;
		}
		_select = selsys[_selsys].SetSelect(_select);
		ls->PushInteger(_select);
		return 1;
	}
	return 0;
}

#endif
#endif