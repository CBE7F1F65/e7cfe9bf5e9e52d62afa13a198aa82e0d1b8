#ifndef __NOTUSELUA

#include "../Header/Export_Lua.h"
#include "../Header/LuaConstDefine.h"

bool Export_Lua::_LuaRegistConst(LuaObject * obj)
{
	// System
	obj->SetInteger("NULL",	NULL);

	// D3D
	obj->SetInteger("D3DTS_WORLD", D3DTS_WORLD);
	obj->SetInteger("D3DTS_VIEW", D3DTS_VIEW);
	obj->SetInteger("D3DTS_PROJECTION", D3DTS_PROJECTION);

	// DI
	obj->SetInteger("DIK_ESCAPE", DIK_ESCAPE);
	obj->SetInteger("DIK_1", DIK_1);
	obj->SetInteger("DIK_2", DIK_2);
	obj->SetInteger("DIK_3", DIK_3);
	obj->SetInteger("DIK_4", DIK_4);
	obj->SetInteger("DIK_5", DIK_5);
	obj->SetInteger("DIK_6", DIK_6);
	obj->SetInteger("DIK_7", DIK_7);
	obj->SetInteger("DIK_8", DIK_8);
	obj->SetInteger("DIK_9", DIK_9);
	obj->SetInteger("DIK_0", DIK_0);
	obj->SetInteger("DIK_MINUS", DIK_MINUS);
	obj->SetInteger("DIK_EQUALS", DIK_EQUALS);
	obj->SetInteger("DIK_BACK", DIK_BACK);
	obj->SetInteger("DIK_TAB", DIK_TAB);
	obj->SetInteger("DIK_Q", DIK_Q);
	obj->SetInteger("DIK_W", DIK_W);
	obj->SetInteger("DIK_E", DIK_E);
	obj->SetInteger("DIK_R", DIK_R);
	obj->SetInteger("DIK_T", DIK_T);
	obj->SetInteger("DIK_Y", DIK_Y);
	obj->SetInteger("DIK_U", DIK_U);
	obj->SetInteger("DIK_I", DIK_I);
	obj->SetInteger("DIK_O", DIK_O);
	obj->SetInteger("DIK_P", DIK_P);
	obj->SetInteger("DIK_LBRACKET", DIK_LBRACKET);
	obj->SetInteger("DIK_RBRACKET", DIK_RBRACKET);
	obj->SetInteger("DIK_RETURN", DIK_RETURN);
	obj->SetInteger("DIK_LCONTROL", DIK_LCONTROL);
	obj->SetInteger("DIK_A", DIK_A);
	obj->SetInteger("DIK_S", DIK_S);
	obj->SetInteger("DIK_D", DIK_D);
	obj->SetInteger("DIK_F", DIK_F);
	obj->SetInteger("DIK_G", DIK_G);
	obj->SetInteger("DIK_H", DIK_H);
	obj->SetInteger("DIK_J", DIK_J);
	obj->SetInteger("DIK_K", DIK_K);
	obj->SetInteger("DIK_L", DIK_L);
	obj->SetInteger("DIK_SEMICOLON", DIK_SEMICOLON);
	obj->SetInteger("DIK_APOSTROPHE", DIK_APOSTROPHE);
	obj->SetInteger("DIK_GRAVE", DIK_GRAVE);
	obj->SetInteger("DIK_LSHIFT", DIK_LSHIFT);
	obj->SetInteger("DIK_BACKSLASH", DIK_BACKSLASH);
	obj->SetInteger("DIK_Z", DIK_Z);
	obj->SetInteger("DIK_X", DIK_X);
	obj->SetInteger("DIK_C", DIK_C);
	obj->SetInteger("DIK_V", DIK_V);
	obj->SetInteger("DIK_B", DIK_B);
	obj->SetInteger("DIK_N", DIK_N);
	obj->SetInteger("DIK_M", DIK_M);
	obj->SetInteger("DIK_COMMA", DIK_COMMA);
	obj->SetInteger("DIK_PERIOD", DIK_PERIOD);
	obj->SetInteger("DIK_SLASH", DIK_SLASH);
	obj->SetInteger("DIK_RSHIFT", DIK_RSHIFT);
	obj->SetInteger("DIK_MULTIPLY", DIK_MULTIPLY);
	obj->SetInteger("DIK_LMENU", DIK_LMENU);
	obj->SetInteger("DIK_SPACE", DIK_SPACE);
	obj->SetInteger("DIK_CAPITAL", DIK_CAPITAL);
	obj->SetInteger("DIK_F1", DIK_F1);
	obj->SetInteger("DIK_F2", DIK_F2);
	obj->SetInteger("DIK_F3", DIK_F3);
	obj->SetInteger("DIK_F4", DIK_F4);
	obj->SetInteger("DIK_F5", DIK_F5);
	obj->SetInteger("DIK_F6", DIK_F6);
	obj->SetInteger("DIK_F7", DIK_F7);
	obj->SetInteger("DIK_F8", DIK_F8);
	obj->SetInteger("DIK_F9", DIK_F9);
	obj->SetInteger("DIK_F10", DIK_F10);
	obj->SetInteger("DIK_NUMLOCK", DIK_NUMLOCK);
	obj->SetInteger("DIK_SCROLL", DIK_SCROLL);
	obj->SetInteger("DIK_NUMPAD7", DIK_NUMPAD7);
	obj->SetInteger("DIK_NUMPAD8", DIK_NUMPAD8);
	obj->SetInteger("DIK_NUMPAD9", DIK_NUMPAD9);
	obj->SetInteger("DIK_SUBTRACT", DIK_SUBTRACT);
	obj->SetInteger("DIK_NUMPAD4", DIK_NUMPAD4);
	obj->SetInteger("DIK_NUMPAD5", DIK_NUMPAD5);
	obj->SetInteger("DIK_NUMPAD6", DIK_NUMPAD6);
	obj->SetInteger("DIK_ADD", DIK_ADD);
	obj->SetInteger("DIK_NUMPAD1", DIK_NUMPAD1);
	obj->SetInteger("DIK_NUMPAD2", DIK_NUMPAD2);
	obj->SetInteger("DIK_NUMPAD3", DIK_NUMPAD3);
	obj->SetInteger("DIK_NUMPAD0", DIK_NUMPAD0);
	obj->SetInteger("DIK_DECIMAL", DIK_DECIMAL);
	obj->SetInteger("DIK_OEM_102", DIK_OEM_102);
	obj->SetInteger("DIK_F11", DIK_F11);
	obj->SetInteger("DIK_F12", DIK_F12);
	obj->SetInteger("DIK_F13", DIK_F13);
	obj->SetInteger("DIK_F14", DIK_F14);
	obj->SetInteger("DIK_F15", DIK_F15);
	obj->SetInteger("DIK_KANA", DIK_KANA);
	obj->SetInteger("DIK_ABNT_C1", DIK_ABNT_C1);
	obj->SetInteger("DIK_CONVERT", DIK_CONVERT);
	obj->SetInteger("DIK_NOCONVERT", DIK_NOCONVERT);
	obj->SetInteger("DIK_YEN", DIK_YEN);
	obj->SetInteger("DIK_ABNT_C2", DIK_ABNT_C2);
	obj->SetInteger("DIK_NUMPADEQUALS", DIK_NUMPADEQUALS);
	obj->SetInteger("DIK_PREVTRACK", DIK_PREVTRACK);
	obj->SetInteger("DIK_AT", DIK_AT);
	obj->SetInteger("DIK_COLON", DIK_COLON);
	obj->SetInteger("DIK_UNDERLINE", DIK_UNDERLINE);
	obj->SetInteger("DIK_KANJI", DIK_KANJI);
	obj->SetInteger("DIK_STOP", DIK_STOP);
	obj->SetInteger("DIK_AX", DIK_AX);
	obj->SetInteger("DIK_UNLABELED", DIK_UNLABELED);
	obj->SetInteger("DIK_NEXTTRACK", DIK_NEXTTRACK);
	obj->SetInteger("DIK_NUMPADENTER", DIK_NUMPADENTER);
	obj->SetInteger("DIK_RCONTROL", DIK_RCONTROL);
	obj->SetInteger("DIK_MUTE", DIK_MUTE);
	obj->SetInteger("DIK_CALCULATOR", DIK_CALCULATOR);
	obj->SetInteger("DIK_PLAYPAUSE", DIK_PLAYPAUSE);
	obj->SetInteger("DIK_MEDIASTOP", DIK_MEDIASTOP);
	obj->SetInteger("DIK_VOLUMEDOWN", DIK_VOLUMEDOWN);
	obj->SetInteger("DIK_VOLUMEUP", DIK_VOLUMEUP);
	obj->SetInteger("DIK_WEBHOME", DIK_WEBHOME);
	obj->SetInteger("DIK_NUMPADCOMMA", DIK_NUMPADCOMMA);
	obj->SetInteger("DIK_DIVIDE", DIK_DIVIDE);
	obj->SetInteger("DIK_SYSRQ", DIK_SYSRQ);
	obj->SetInteger("DIK_RMENU", DIK_RMENU);
	obj->SetInteger("DIK_PAUSE", DIK_PAUSE);
	obj->SetInteger("DIK_HOME", DIK_HOME);
	obj->SetInteger("DIK_UP", DIK_UP);
	obj->SetInteger("DIK_PRIOR", DIK_PRIOR);
	obj->SetInteger("DIK_LEFT", DIK_LEFT);
	obj->SetInteger("DIK_RIGHT", DIK_RIGHT);
	obj->SetInteger("DIK_END", DIK_END);
	obj->SetInteger("DIK_DOWN", DIK_DOWN);
	obj->SetInteger("DIK_NEXT", DIK_NEXT);
	obj->SetInteger("DIK_INSERT", DIK_INSERT);
	obj->SetInteger("DIK_DELETE", DIK_DELETE);
	obj->SetInteger("DIK_LWIN", DIK_LWIN);
	obj->SetInteger("DIK_RWIN", DIK_RWIN);
	obj->SetInteger("DIK_APPS", DIK_APPS);
	obj->SetInteger("DIK_POWER", DIK_POWER);
	obj->SetInteger("DIK_SLEEP", DIK_SLEEP);
	obj->SetInteger("DIK_WAKE", DIK_WAKE);
	obj->SetInteger("DIK_WEBSEARCH", DIK_WEBSEARCH);
	obj->SetInteger("DIK_WEBFAVORITES", DIK_WEBFAVORITES);
	obj->SetInteger("DIK_WEBREFRESH", DIK_WEBREFRESH);
	obj->SetInteger("DIK_WEBSTOP", DIK_WEBSTOP);
	obj->SetInteger("DIK_WEBFORWARD", DIK_WEBFORWARD);
	obj->SetInteger("DIK_WEBBACK", DIK_WEBBACK);
	obj->SetInteger("DIK_MYCOMPUTER", DIK_MYCOMPUTER);
	obj->SetInteger("DIK_MAIL", DIK_MAIL);
	obj->SetInteger("DIK_MEDIASELECT", DIK_MEDIASELECT);

	return true;
}

bool Export_Lua::_LuaRegistHGEConst(LuaObject * obj)
{
	// Math
	obj->SetNumber("M_PI", M_PI);
	obj->SetNumber("M_PI_2", M_PI_2);
	obj->SetNumber("M_PI_4", M_PI_4);
	obj->SetNumber("M_1_PI", M_1_PI);
	obj->SetNumber("M_2_PI", M_2_PI);

	obj->SetNumber("M_E", M_E);
	obj->SetNumber("M_LOG2E", M_LOG2E);
	obj->SetNumber("M_LOG10E", M_LOG10E);
	obj->SetNumber("M_LN2", M_LN2);
	obj->SetNumber("M_LN10", M_LN10);
	obj->SetNumber("M_PI", M_PI);
	obj->SetNumber("M_PI_2", M_PI_2);
	obj->SetNumber("M_PI_4", M_PI_4);
	obj->SetNumber("M_1_PI", M_1_PI);
	obj->SetNumber("M_2_PI", M_2_PI);
	obj->SetNumber("M_2_SQRTPI", M_2_SQRTPI);
	obj->SetNumber("M_SQRT2", M_SQRT2);
	obj->SetNumber("M_SQRT1_2", M_SQRT1_2);

	// Blend
	obj->SetInteger("BLEND_COLORADD", BLEND_COLORADD);
	obj->SetInteger("BLEND_COLORMUL", BLEND_COLORMUL);
	obj->SetInteger("BLEND_ALPHABLEND", BLEND_ALPHABLEND);
	obj->SetInteger("BLEND_ALPHAADD", BLEND_ALPHAADD);
	obj->SetInteger("BLEND_ZWRITE", BLEND_ZWRITE);
	obj->SetInteger("BLEND_NOZWRITE", BLEND_NOZWRITE);

	obj->SetInteger("BLEND_DEFAULT", BLEND_DEFAULT);
	obj->SetInteger("BLEND_DEFAULT_Z", BLEND_DEFAULT_Z);

	// hgeState
	obj->SetInteger("HGE_WINDOWED", HGE_WINDOWED);
	obj->SetInteger("HGE_ZBUFFER", HGE_ZBUFFER);
	obj->SetInteger("HGE_TEXTUREFILTER", HGE_TEXTUREFILTER);

	obj->SetInteger("HGE_USESOUND", HGE_USESOUND);

	obj->SetInteger("HGE_DONTSUSPEND", HGE_DONTSUSPEND);
	obj->SetInteger("HGE_HIDEMOUSE", HGE_HIDEMOUSE);

	obj->SetInteger("HGE_SHOWSPLASH", HGE_SHOWSPLASH);

	obj->SetInteger("HGE_HWND", HGE_HWND);
	obj->SetInteger("HGE_HWNDPARENT", HGE_HWNDPARENT);
	obj->SetInteger("HGE_SCREENWIDTH", HGE_SCREENWIDTH);
	obj->SetInteger("HGE_SCREENHEIGHT", HGE_SCREENHEIGHT);
	obj->SetInteger("HGE_SCREENBPP", HGE_SCREENBPP);

	obj->SetInteger("HGE_SAMPLERATE", HGE_SAMPLERATE);
	obj->SetInteger("HGE_SAMPLEVOLUME", HGE_SAMPLEVOLUME);
	obj->SetInteger("HGE_FXVOLUME", HGE_FXVOLUME);
	obj->SetInteger("HGE_STREAMVOLUME", HGE_STREAMVOLUME);
	obj->SetInteger("HGE_FPS", HGE_FPS);

	obj->SetInteger("HGE_FRAMECOUNTER", HGE_FRAMECOUNTER);
	obj->SetInteger("HGE_FRAMESKIP", HGE_FRAMESKIP);
	obj->SetInteger("HGE_RENDERSKIP", HGE_RENDERSKIP);

	obj->SetInteger("HGE_ICON", HGE_ICON);
	obj->SetInteger("HGE_TITLE", HGE_TITLE);

	obj->SetInteger("HGE_INIFILE", HGE_INIFILE);
	obj->SetInteger("HGE_LOGFILE", HGE_LOGFILE);

	obj->SetInteger("HGE_BASSDLLFILE", HGE_BASSDLLFILE);

	// Input
	obj->SetInteger("INPUT_KEYDOWN", INPUT_KEYDOWN);
	obj->SetInteger("INPUT_KEYUP", INPUT_KEYUP);
	obj->SetInteger("INPUT_MBUTTONDOWN", INPUT_MBUTTONDOWN);
	obj->SetInteger("INPUT_MBUTTONUP", INPUT_MBUTTONUP);
	obj->SetInteger("INPUT_MOUSEMOVE", INPUT_MOUSEMOVE);
	obj->SetInteger("INPUT_MOUSEWHEEL", INPUT_MOUSEWHEEL);

	obj->SetInteger("HGEINP_SHIFT", HGEINP_SHIFT);
	obj->SetInteger("HGEINP_CTRL", HGEINP_CTRL);
	obj->SetInteger("HGEINP_ALT", HGEINP_ALT);
	obj->SetInteger("HGEINP_CAPSLOCK", HGEINP_CAPSLOCK);
	obj->SetInteger("HGEINP_SCROLLLOCK", HGEINP_SCROLLLOCK);
	obj->SetInteger("HGEINP_NUMLOCK", HGEINP_NUMLOCK);
	obj->SetInteger("HGEINP_REPEAT", HGEINP_REPEAT);

	obj->SetInteger("HGEK_LBUTTON", HGEK_LBUTTON);
	obj->SetInteger("HGEK_RBUTTON", HGEK_RBUTTON);
	obj->SetInteger("HGEK_MBUTTON", HGEK_MBUTTON);

	obj->SetInteger("HGEK_ESCAPE", HGEK_ESCAPE);
	obj->SetInteger("HGEK_BACKSPACE", HGEK_BACKSPACE);
	obj->SetInteger("HGEK_TAB", HGEK_TAB);
	obj->SetInteger("HGEK_ENTER", HGEK_ENTER);
	obj->SetInteger("HGEK_SPACE", HGEK_SPACE);

	obj->SetInteger("HGEK_SHIFT", HGEK_SHIFT);
	obj->SetInteger("HGEK_CTRL", HGEK_CTRL);
	obj->SetInteger("HGEK_ALT", HGEK_ALT);

	obj->SetInteger("HGEK_LWIN", HGEK_LWIN);
	obj->SetInteger("HGEK_RWIN", HGEK_RWIN);
	obj->SetInteger("HGEK_APPS", HGEK_APPS);

	obj->SetInteger("HGEK_PAUSE", HGEK_PAUSE);
	obj->SetInteger("HGEK_CAPSLOCK", HGEK_CAPSLOCK);
	obj->SetInteger("HGEK_NUMLOCK", HGEK_NUMLOCK);
	obj->SetInteger("HGEK_SCROLLLOCK", HGEK_SCROLLLOCK);

	obj->SetInteger("HGEK_PGUP", HGEK_PGUP);
	obj->SetInteger("HGEK_PGDN", HGEK_PGDN);
	obj->SetInteger("HGEK_HOME", HGEK_HOME);
	obj->SetInteger("HGEK_END", HGEK_END);
	obj->SetInteger("HGEK_INSERT", HGEK_INSERT);
	obj->SetInteger("HGEK_DELETE", HGEK_DELETE);

	obj->SetInteger("HGEK_LEFT", HGEK_LEFT);
	obj->SetInteger("HGEK_UP", HGEK_UP);
	obj->SetInteger("HGEK_RIGHT", HGEK_RIGHT);
	obj->SetInteger("HGEK_DOWN", HGEK_DOWN);

	obj->SetInteger("HGEK_0", HGEK_0);
	obj->SetInteger("HGEK_1", HGEK_1);
	obj->SetInteger("HGEK_2", HGEK_2);
	obj->SetInteger("HGEK_3", HGEK_3);
	obj->SetInteger("HGEK_4", HGEK_4);
	obj->SetInteger("HGEK_5", HGEK_5);
	obj->SetInteger("HGEK_6", HGEK_6);
	obj->SetInteger("HGEK_7", HGEK_7);
	obj->SetInteger("HGEK_8", HGEK_8);
	obj->SetInteger("HGEK_9", HGEK_9);

	obj->SetInteger("HGEK_A", HGEK_A);
	obj->SetInteger("HGEK_B", HGEK_B);
	obj->SetInteger("HGEK_C", HGEK_C);
	obj->SetInteger("HGEK_D", HGEK_D);
	obj->SetInteger("HGEK_E", HGEK_E);
	obj->SetInteger("HGEK_F", HGEK_F);
	obj->SetInteger("HGEK_G", HGEK_G);
	obj->SetInteger("HGEK_H", HGEK_H);
	obj->SetInteger("HGEK_I", HGEK_I);
	obj->SetInteger("HGEK_J", HGEK_J);
	obj->SetInteger("HGEK_K", HGEK_K);
	obj->SetInteger("HGEK_L", HGEK_L);
	obj->SetInteger("HGEK_M", HGEK_M);
	obj->SetInteger("HGEK_N", HGEK_N);
	obj->SetInteger("HGEK_O", HGEK_O);
	obj->SetInteger("HGEK_P", HGEK_P);
	obj->SetInteger("HGEK_Q", HGEK_Q);
	obj->SetInteger("HGEK_R", HGEK_R);
	obj->SetInteger("HGEK_S", HGEK_S);
	obj->SetInteger("HGEK_T", HGEK_T);
	obj->SetInteger("HGEK_U", HGEK_U);
	obj->SetInteger("HGEK_V", HGEK_V);
	obj->SetInteger("HGEK_W", HGEK_W);
	obj->SetInteger("HGEK_X", HGEK_X);
	obj->SetInteger("HGEK_Y", HGEK_Y);
	obj->SetInteger("HGEK_Z", HGEK_Z);

	obj->SetInteger("HGEK_GRAVE", HGEK_GRAVE);
	obj->SetInteger("HGEK_MINUS", HGEK_MINUS);
	obj->SetInteger("HGEK_EQUALS", HGEK_EQUALS);
	obj->SetInteger("HGEK_BACKSLASH", HGEK_BACKSLASH);
	obj->SetInteger("HGEK_LBRACKET", HGEK_LBRACKET);
	obj->SetInteger("HGEK_RBRACKET", HGEK_RBRACKET);
	obj->SetInteger("HGEK_SEMICOLON", HGEK_SEMICOLON);
	obj->SetInteger("HGEK_APOSTROPHE", HGEK_APOSTROPHE);
	obj->SetInteger("HGEK_COMMA", HGEK_COMMA);
	obj->SetInteger("HGEK_PERIOD", HGEK_PERIOD);
	obj->SetInteger("HGEK_SLASH", HGEK_SLASH);

	obj->SetInteger("HGEK_NUMPAD0", HGEK_NUMPAD0);
	obj->SetInteger("HGEK_NUMPAD1", HGEK_NUMPAD1);
	obj->SetInteger("HGEK_NUMPAD2", HGEK_NUMPAD2);
	obj->SetInteger("HGEK_NUMPAD3", HGEK_NUMPAD3);
	obj->SetInteger("HGEK_NUMPAD4", HGEK_NUMPAD4);
	obj->SetInteger("HGEK_NUMPAD5", HGEK_NUMPAD5);
	obj->SetInteger("HGEK_NUMPAD6", HGEK_NUMPAD6);
	obj->SetInteger("HGEK_NUMPAD7", HGEK_NUMPAD7);
	obj->SetInteger("HGEK_NUMPAD8", HGEK_NUMPAD8);
	obj->SetInteger("HGEK_NUMPAD9", HGEK_NUMPAD9);

	obj->SetInteger("HGEK_MULTIPLY", HGEK_MULTIPLY);
	obj->SetInteger("HGEK_DIVIDE", HGEK_DIVIDE);
	obj->SetInteger("HGEK_ADD", HGEK_ADD);
	obj->SetInteger("HGEK_SUBTRACT", HGEK_SUBTRACT);
	obj->SetInteger("HGEK_DECIMAL", HGEK_DECIMAL);

	obj->SetInteger("HGEK_F1", HGEK_F1);
	obj->SetInteger("HGEK_F2", HGEK_F2);
	obj->SetInteger("HGEK_F3", HGEK_F3);
	obj->SetInteger("HGEK_F4", HGEK_F4);
	obj->SetInteger("HGEK_F5", HGEK_F5);
	obj->SetInteger("HGEK_F6", HGEK_F6);
	obj->SetInteger("HGEK_F7", HGEK_F7);
	obj->SetInteger("HGEK_F8", HGEK_F8);
	obj->SetInteger("HGEK_F9", HGEK_F9);
	obj->SetInteger("HGEK_F10", HGEK_F10);
	obj->SetInteger("HGEK_F11", HGEK_F11);
	obj->SetInteger("HGEK_F12", HGEK_F12);

	// DI
	obj->SetInteger("DIKEY_PRESSED", DIKEY_PRESSED);
	obj->SetInteger("DIKEY_UP", DIKEY_UP);
	obj->SetInteger("DIKEY_DOWN", DIKEY_DOWN);

	obj->SetInteger("JOY_LEFT", JOY_LEFT);
	obj->SetInteger("JOY_RIGHT", JOY_RIGHT);
	obj->SetInteger("JOY_UP", JOY_UP);
	obj->SetInteger("JOY_DOWN", JOY_DOWN);

	return true;
}

bool Export_Lua::_LuaRegistHGEHelpConst(LuaObject * obj)
{
	// hgeFont
	obj->SetInteger("HGETEXT_LEFT", HGETEXT_LEFT);
	obj->SetInteger("HGETEXT_RIGHT", HGETEXT_RIGHT);
	obj->SetInteger("HGETEXT_CENTER", HGETEXT_CENTER);
	obj->SetInteger("HGETEXT_HORZMASK", HGETEXT_HORZMASK);

	obj->SetInteger("HGETEXT_TOP", HGETEXT_TOP);
	obj->SetInteger("HGETEXT_BOTTOM", HGETEXT_BOTTOM);
	obj->SetInteger("HGETEXT_MIDDLE", HGETEXT_MIDDLE);
	obj->SetInteger("HGETEXT_VERTMASK", HGETEXT_VERTMASK);

	return true;
}

#endif