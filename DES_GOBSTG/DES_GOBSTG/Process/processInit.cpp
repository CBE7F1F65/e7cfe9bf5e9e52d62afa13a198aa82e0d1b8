#include "processPrep.h"

int Process::processPreInitial()
{
	bool rebuilddone = false;
	if(_access(CONFIG_STR_FILENAME, 00) == -1)
	{
rebuild:
		if (rebuilddone)
		{
			errorcode = PROC_ERROR_INIFILE;
			return PQUIT;
		}
		DeleteFile(CONFIG_STR_FILENAME);

		hge->	Ini_SetInt(Data::data.translateSection(Data::data.sLinkType(DATAS_HEADER)), Data::data.translateName(Data::data.nLinkType(DATAN_GAMEVERSION)), GAME_VERSION);
		hge->	Ini_SetString(Data::data.translateSection(Data::data.sLinkType(DATAS_HEADER)), Data::data.translateName(Data::data.nLinkType(DATAN_SIGNATURE)), GAME_SIGNATURE);

		hge->	Ini_SetString(RESCONFIGS_RESOURCE, RESCONFIGN_RESOURCEFILE, RESCONFIGDEFAULT_RESOURCEFILE);
		hge->	Ini_SetString(RESCONFIGS_RESOURCE, RESCONFIGN_RESBINNAME, RESCONFIGDEFAULT_RESBINNAME);
		hge->	Ini_SetString(RESCONFIGS_RESOURCE, RESCONFIGN_PASSWORD, RESCONFIGDEFAULT_PASSWORD);

		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYUP, RESCONFIGDEFAULT_KEYUP_1);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYDOWN, RESCONFIGDEFAULT_KEYDOWN_1);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYLEFT, RESCONFIGDEFAULT_KEYLEFT_1);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYRIGHT, RESCONFIGDEFAULT_KEYRIGHT_1);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYFIRE, RESCONFIGDEFAULT_KEYFIRE_1);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYQUICK, RESCONFIGDEFAULT_KEYQUICK_1);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYSLOW, RESCONFIGDEFAULT_KEYSLOW_1);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYDRAIN, RESCONFIGDEFAULT_KEYDRAIN_1);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYPAUSE, RESCONFIGDEFAULT_KEYPAUSE);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYSKIP, RESCONFIGDEFAULT_KEYSKIP);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYENTER, RESCONFIGDEFAULT_KEYENTER);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYESCAPE, RESCONFIGDEFAULT_KEYESCAPE);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYCAPTURE, RESCONFIGDEFAULT_KEYCAPTURE);

		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_JOYFIRE, RESCONFIGDEFAULT_JOYFIRE);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_JOYQUICK, RESCONFIGDEFAULT_JOYQUICK);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_JOYSLOW, RESCONFIGDEFAULT_JOYSLOW);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_JOYDRAIN, RESCONFIGDEFAULT_JOYDRAIN);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_JOYPAUSE, RESCONFIGDEFAULT_JOYPAUSE);

		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYUP, RESCONFIGDEFAULT_KEYUP_2);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYDOWN, RESCONFIGDEFAULT_KEYDOWN_2);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYLEFT, RESCONFIGDEFAULT_KEYLEFT_2);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYRIGHT, RESCONFIGDEFAULT_KEYRIGHT_2);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYFIRE, RESCONFIGDEFAULT_KEYFIRE_2);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYQUICK, RESCONFIGDEFAULT_KEYQUICK_2);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYSLOW, RESCONFIGDEFAULT_KEYSLOW_2);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYDRAIN, RESCONFIGDEFAULT_KEYDRAIN_2);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYPAUSE, RESCONFIGDEFAULT_KEYPAUSE);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYSKIP, RESCONFIGDEFAULT_KEYSKIP);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYENTER, RESCONFIGDEFAULT_KEYENTER);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYESCAPE, RESCONFIGDEFAULT_KEYESCAPE);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYCAPTURE, RESCONFIGDEFAULT_KEYCAPTURE);

		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_JOYFIRE, RESCONFIGDEFAULT_JOYFIRE);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_JOYQUICK, RESCONFIGDEFAULT_JOYQUICK);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_JOYSLOW, RESCONFIGDEFAULT_JOYSLOW);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_JOYDRAIN, RESCONFIGDEFAULT_JOYDRAIN);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_JOYPAUSE, RESCONFIGDEFAULT_JOYPAUSE);

		hge->	Ini_SetInt(RESCONFIGS_VOLUME, RESCONFIGN_VOLMUSIC, RESCONFIGDEFAULT_VOLMUSIC);
		hge->	Ini_SetInt(RESCONFIGS_VOLUME, RESCONFIGN_VOLSE, RESCONFIGDEFAULT_VOLSE);

		hge->	Ini_SetInt(RESCONFIGS_CUSTOM, RESCONFIGN_SCREENMODE, RESCONFIGDEFAULT_SCREENMODE);
		hge->	Ini_SetString(RESCONFIGS_CUSTOM, RESCONFIGN_USERNAME, RESCONFIGDEFAULT_USERNAME);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOM, RESCONFIGN_RENDERSKIP, RESCONFIGDEFAULT_RENDERSKIP);

		hge->	Ini_SetInt(RESCONFIGS_CUSTOMWINDOW, RESCONFIGN_DEFAULTWINDOW, RESCONFIGDEFAULT_DEFAULTWINDOW);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOMWINDOW, RESCONFIGN_WINDOWLEFT, RESCONFIGDEFAULT_WINDOWLEFT);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOMWINDOW, RESCONFIGN_WINDOWTOP, RESCONFIGDEFAULT_WINDOWTOP);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOMWINDOW, RESCONFIGN_WINDOWWIDTH, RESCONFIGDEFAULT_WINDOWWIDTH);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOMWINDOW, RESCONFIGN_WINDOWHEIGHT, RESCONFIGDEFAULT_WINDOWHEIGHT);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOMWINDOW, RESCONFIGN_WINDOWTOPMOST, RESCONFIGDEFAULT_WINDOWTOPMOST);
#ifdef __DEBUG
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_DEBUG_JOYSPEEDUP, RESCONFIGDEFAULT_DEBUG_JOYSPEEDUP);
		HGELOG("Succeeded in rebuilding Config File.");

		rebuilddone = true;
#endif
	}

	if (!GameInput::InitInput(hge))
	{
		goto rebuild;
	}

	bgmvol			= hge->Ini_GetInt(RESCONFIGS_VOLUME, RESCONFIGN_VOLMUSIC, RESCONFIGDEFAULT_VOLMUSIC);
	sevol			= hge->Ini_GetInt(RESCONFIGS_VOLUME, RESCONFIGN_VOLSE, RESCONFIGDEFAULT_VOLSE);

	screenmode		= hge->Ini_GetInt(RESCONFIGS_CUSTOM, RESCONFIGN_SCREENMODE, RESCONFIGDEFAULT_SCREENMODE);
	strcpy(username, hge->Ini_GetString(RESCONFIGS_CUSTOM, RESCONFIGN_USERNAME, RESCONFIGDEFAULT_USERNAME));
	renderskip		= hge->Ini_GetInt(RESCONFIGS_CUSTOM, RESCONFIGN_RENDERSKIP, RESCONFIGDEFAULT_RENDERSKIP);

	//

	if(hge->Ini_GetInt(Data::data.translateSection(Data::data.sLinkType(DATAS_HEADER)), Data::data.translateName(Data::data.nLinkType(DATAN_GAMEVERSION)), -1) != GAME_VERSION)
		goto rebuild;
	
	if(screenmode < 0 || screenmode > 1)
		goto rebuild;
	if(bgmvol < 0 || bgmvol > 100)
		goto rebuild;
	if(sevol < 0 || sevol > 100)
		goto rebuild;
	if (renderskip < 0 || renderskip > 3)
	{
		goto rebuild;
	}
	else
	{
		if (renderskip == 0)
		{
			renderskip = 1;
		}
		hge->System_SetState(HGE_RENDERSKIP, renderskip * M_DEFAULT_RENDERSKIP);
	}

#ifdef __DEBUG
	HGELOG("Succeeded in gaining Data::data from Config File.");
#endif
	hge->Resource_AttachPack(RESLOADING_PCK, Export::GetPassword());
	texInit = hge->Texture_Load(RESLOADING_TEX);

	return PGO;
}

int Process::processInit()
{
	time++;

	if (time == 1)
	{
		return processPreInitial();
	}

	if (texInit)
	{
		hge->Texture_Free(texInit);
		texInit = NULL;
	}
	hge->Resource_RemovePack(RESLOADING_PCK);

	bool binmode = Export::GetResourceFile();

	Data::data.GetIni();

	if(binmode)
	{
		Data::data.binmode = true;
		Scripter::scr.binmode = true;
#ifdef __RELEASE
//		hge->System_SetState(HGE_LOGFILE, "");
#endif // __RELEASE
	}
	else
	{
		if(!BResource::res.Fill())
		{
#ifdef __DEBUG
			HGELOG("Error in Filling Resource Data.");
#endif
			errorcode = PROC_ERROR_RESOURCE;
			return PQUIT;
		}
		if(!Scripter::scr.LoadAll(tex))
		{
			errorcode = PROC_ERROR_SCRIPT;
			return PQUIT;
		}
		if(!BResource::res.Pack(Scripter::strdesc, BResource::res.customconstdata))
		{
#ifdef __DEBUG
			HGELOG("Error in Packing Resource Data.");
#endif
			errorcode = PROC_ERROR_TRANSLATE;
			return PQUIT;
		}
		if(!BResource::res.SetDataFile())
		{
			errorcode = PROC_ERROR_DATA;
			return PQUIT;
		}
	}
	if(!BResource::res.Gain(Scripter::strdesc, binmode?BResource::res.customconstdata:NULL))
	{
#ifdef __DEBUG
		HGELOG("Error in Gaining Resource Data.");
#endif
		errorcode = PROC_ERROR_DATA;
		return PQUIT;
	}
	if(Scripter::scr.binmode && !Scripter::scr.LoadAll(tex))
	{
		errorcode = PROC_ERROR_SCRIPT;
		return PQUIT;
	}
	if(!Data::data.SetFile(Export::resourcefilename, DATA_RESOURCEFILE))
	{
#ifdef __DEBUG
		HGELOG("Error in Setting Resource File");
#endif
		errorcode = PROC_ERROR_DATA;
		return PQUIT;
	}

	if(!BResource::res.LoadPackage())
	{
		errorcode = PROC_ERROR_PACKAGE;
		return PQUIT;
	}

	BGLayer::Init(tex);

	SE::vol = sevol;
	if(!SE::Initial())
	{
		errorcode = PROC_ERROR_SOUND;
		return PQUIT;
	}

	char tnbuffer[M_STRMAX];
	for(int i=1;i<TEXMAX;i++)
	{
		if(tex[i])
			hge->Texture_Free(tex[i]);
		tex[i] = NULL;

		strcpy(tnbuffer, BResource::res.resdata.texfilename[i]);
		if(!strlen(tnbuffer))
		{
			strcpy(tnbuffer, BResource::res.resdata.texfilename[TEX_WHITE]);
		}

		tex[i] = hge->Texture_Load(tnbuffer);
#ifdef __DEBUG
		if(tex[i] == NULL)
		{
			HGELOG("%s\nFailed in loading Texture File %s.(To be assigned to Index %d).", HGELOG_ERRSTR, tnbuffer, i);
			errorcode = PROC_ERROR_TEXTURE;
			return PQUIT;
		}
		else
		{
			HGELOG("Succeeded in loading Texture File %s.(Assigned to Index %d).", tnbuffer, i);
		}
#endif
	}

	tex[TEX_WORD] = hge->Texture_Load(BResource::res.resdata.texfilename[TEX_WORD]);
#ifdef __DEBUG
	if(tex[TEX_WORD] == NULL)
	{
		HGELOG("%s\nFailed in loading Texture File %s.(To be assigned to Index %d).", HGELOG_ERRSTR, BResource::res.resdata.texfilename[TEX_WORD], TEX_WORD);
		errorcode = PROC_ERROR_TEXTURE;
		return PQUIT;
	}
	else
	{
		HGELOG("Succeeded in loading Texture File %s.(Assigned to Index %d).", BResource::res.resdata.texfilename[TEX_WORD], TEX_WORD);
	}
#endif

	SpriteItemManager::Init(tex);

	Fontsys::Init();
	if(!Effectsys::Init(tex, BResource::res.resdata.effectsysfoldername, BResource::res.resdata.effectsysfilename))
	{
#ifdef __DEBUG
		HGELOG("%s\nFailed in Initializing Effectsys.", HGELOG_ERRSTR);
#endif
		return false;
	}

#ifdef __DEBUG
	HGELOG("Succeeded in loading all resources.\n");
#endif

	hge->System_SetState(HGE_WINDOWED, !(bool)screenmode);
	hge->System_SetState(HGE_HIDEMOUSE, (bool)screenmode);

	if(!screenmode)
	{
		Export::clientAdjustWindow();
	}

	Chat::chatitem.Init();

	SelectSystem::ClearAll();

	errorcode = PROC_ERROR_NONE;
	titleselect = 0;

	replaymode = false;

	playing = false;
	playtimeStart = 0;

	time = 0;
	state = STATE_TITLE;
	return PTURN;
}