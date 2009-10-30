#include "Export_Lua.h"
#include "Const.h"
#include "LuaConstDefine.h"

HGE * Export_Lua::hge = NULL;

Export_Lua::Export_Lua()
{
}

Export_Lua::~Export_Lua()
{
	ReleaseHGE();
}

void Export_Lua::Release(LuaState * ls /* = NULL */)
{
}

HGE * Export_Lua::InitHGE()
{
	if (!hge)
	{
		hge = hgeCreate(HGE_VERSION);
		hge->Resource_SetPath(DEFAULT_RESOURCEPATH);
	}
	return hge;
}

HGE * Export_Lua::ReleaseHGE()
{
	if (hge)
	{
		hge->Release();
	}
	hge = NULL;
	return hge;
}

int Export_Lua::ReadLuaFileTableAndConst(LuaState * ls)
{
	if (_access(hge->Resource_MakePath(DEFAULT_LUAFILETABLEFILE), 0) == -1)
	{
		return -1;
	}
	int iret;
	iret = DoLuaFile(ls, DEFAULT_LUAFILETABLEFILE);
	if (iret == 0)
	{
		if (_access(hge->Resource_MakePath(DEFAULT_LUACONSTFILE), 0) != -1)
		{
			iret = DoLuaFile(ls, DEFAULT_LUACONSTFILE);
		}
	}
	return iret;
}

int Export_Lua::_LoadLuaFile(LuaState * ls, const char * filename, bool bDoFile /* = false */, int * filecount /* = NULL */, FILE * outputfile /* = NULL */)
{
	char fullfilename[MAX_PATH];
	strcpy(fullfilename, hge->Resource_MakePath(filename));
	int iret = 0;
	if (bDoFile)
	{
		iret = ls->DoFile(fullfilename);
	}
	else if (!outputfile)
	{
		iret = ls->LoadFile(fullfilename);
	}

	if (outputfile)
	{
		FILE * infile = fopen(fullfilename, "rb");
		char buffer;
		fseek(outputfile, 0, SEEK_END);
		while (true)
		{
			fread(&buffer, 1, 1, infile);
			if (feof(infile))
			{
				break;
			}
			fwrite(&buffer, 1, 1, outputfile);
		}
		buffer = '\r';
		fwrite(&buffer, 1, 1, outputfile);
		buffer = '\n';
		fwrite(&buffer, 1, 1, outputfile);
	}
	if (iret == 0)
	{
		if (filecount)
		{
			(*filecount)++;
		}
	}
	if (iret != 0)
	{
		ShowError(LUAERROR_LOADINGSCRIPT, ls->GetError(iret));
	}
	return iret;
}

int Export_Lua::LoadLuaFile(LuaState * ls, const char * filename, bool bDoFile /* = false */, int * filecount /* = NULL */, FILE * outputfile /* = NULL */)
{
	bool bTempUseHGE = false;
	if (hge == NULL)
	{
		bTempUseHGE = true;
		InitHGE();
	}
	int iret = 0;
	bool wildcard = false;
	char filenamebuffer[MAX_PATH];
	strcpy(filenamebuffer, filename);
	for (int i=0; i<strlen(filenamebuffer); i++)
	{
		if (filenamebuffer[i] == '*')
		{
			wildcard = true;
			break;
		}
	}
	if (wildcard)
	{
		char * filename;
		char filepath[_MAX_PATH];
		char fullfilename[_MAX_PATH];
		sprintf(filepath, hge->Resource_MakePath(filenamebuffer));
		while (true)
		{
			int _lastindex = strlen(filepath)-1;
			if (filepath[_lastindex] == '\\' || filepath[_lastindex] == '/')
			{
				break;
			}
			filepath[_lastindex] = 0;
		}
		filename = hge->Resource_EnumFiles(filenamebuffer);
		do 
		{
			sprintf(fullfilename, "%s%s", filepath, filename);
			iret = _LoadLuaFile(ls, fullfilename, bDoFile, filecount, outputfile);
			if (iret != 0)
			{
				break;
			}
		} while (filename = hge->Resource_EnumFiles());
	}
	else
	{
		iret = _LoadLuaFile(ls, filenamebuffer, bDoFile, filecount, outputfile);
	}

	if (bTempUseHGE)
	{
		ReleaseHGE();
	}
	return iret;
}

int Export_Lua::LuaChunkWriter(lua_State *L, const void* p, size_t sz, void* ud)
{
	return (fwrite(p, sz, 1, (FILE*)ud) != 1) && (sz != 0);
}

bool Export_Lua::CheckUseUnpackedFiles(LuaState * ls)
{
	LuaObject _obj = ls->GetGlobals().GetByName(DEFAULT_BUSEUNPACKEDFILESNAME);
	bool bUseUnpackedFiles = false;
	if (_obj.IsBoolean())
	{
		bUseUnpackedFiles = _obj.GetBoolean();
	}
	return bUseUnpackedFiles;
}

int Export_Lua::PackLuaFiles(LuaState * ls)
{
	int iret = 0;
	int filecount = 0;
	bool bUseUnpackedFiles = CheckUseUnpackedFiles(ls);
	LuaObject _obj = ls->GetGlobals().GetByName(DEFAULT_LUAFILETABLENAME);
	FILE * tempoutputfile = fopen(hge->Resource_MakePath(DEFAULT_TEMPLUAFILE), "wb");
	//	LoadLuaFile(ls, DEFAULT_LUACONSTFILE, bUseUnpackedFiles, &filecount, tempoutputfile);
	for (int i=1; i<=_obj.GetCount(); i++)
	{
		iret = LoadLuaFile(ls, _obj.GetByIndex(i).GetString(), bUseUnpackedFiles, &filecount, tempoutputfile);
		if (iret != 0)
		{
			return iret;
		}
	}
	fclose(tempoutputfile);
	iret = LoadLuaFile(ls, DEFAULT_TEMPLUAFILE, false);

	lua_Chunkwriter writer = Export_Lua::LuaChunkWriter;
	FILE * outputfile = fopen(hge->Resource_MakePath(DEFAULT_BINLUAFILE), "wb");
	if (!outputfile)
	{
		return 0;
	}
	iret = ls->Dump(writer, (void *)outputfile, 1, '=');
	fclose(outputfile);

	DeleteFile(hge->Resource_MakePath(DEFAULT_TEMPLUAFILE));
	if (iret != 0)
	{
		ShowError(LUAERROR_DUMPINGSCRIPT, ls->GetError(iret));
	}

	hgeMemoryFile memfile;
	DWORD size;
	memfile.data = hge->Resource_Load(DEFAULT_BINLUAFILE, &size);
	memfile.filename = DEFAULT_BINLUAFILE;
	memfile.size = size;
	hge->Resource_CreatePack(DEFAULT_BINSCRIPTFILE, M_SCRIPT_PASSWORD, &memfile, NULL);
	hge->Resource_Free(memfile.data);

	return iret;
}

int Export_Lua::DoLuaFileInMemroy(LuaState * ls, const char * buffer, DWORD size, const char * name)
{
	return ls->DoBuffer(buffer, size, name);
}

int Export_Lua::LoadPackedLuaFiles(LuaState * ls)
{
	int iret = 0;
	if (CheckUseUnpackedFiles(ls))
	{
		return iret;
	}
	hge->Resource_AttachPack(DEFAULT_BINSCRIPTFILE, M_SCRIPT_PASSWORD);
	DWORD size = 0;
	BYTE * content = hge->Resource_Load(DEFAULT_BINLUAFILE, &size);
	iret = DoLuaFileInMemroy(ls, (const char *)content, size, DEFAULT_BINLUAFILE);
	if (iret != 0)
	{
		ShowError(LUAERROR_LOADINGSCRIPT, ls->GetError(iret));
	}
	hge->Resource_Free(content);
	DeleteFile(hge->Resource_MakePath(DEFAULT_BINLUAFILE));
	return iret;
}

void Export_Lua::ShowError(int errortype, const char * err)
{
	char msgtitle[M_MESSAGESTRMAX];
	switch (errortype)
	{
	case LUAERROR_LOADINGSCRIPT:
		strcpy(msgtitle, "Error in loading script!");
		break;
	case LUAERROR_NOTFUNCTION:
		strcpy(msgtitle, "Error in getting function!");
		break;
	case LUAERROR_LUAERROR:
		strcpy(msgtitle, "Error in parsing function!");
		break;
	case LUAERROR_DUMPINGSCRIPT:
		strcpy(msgtitle, "Errpr in dumping Script!");
		break;
	default:
		strcpy(msgtitle, "Error!");
	}
	MessageBox(hge->System_GetState(HGE_HWND), err, msgtitle, MB_OK);
	if (!hge->System_GetState(HGE_LOGFILE) || !strlen(hge->System_GetState(HGE_LOGFILE)))
	{
		hge->System_SetState(HGE_LOGFILE, LOG_STR_FILENAME);
	}
	hge->System_Log("%s: %s", msgtitle, err);
}