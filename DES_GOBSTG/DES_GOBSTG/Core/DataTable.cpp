#include "Data.h"
#include "BResource.h"
#include "DataTable.h"
#include "SpriteItemManager.h"

_DataTable _DataTable::datatable;

#define _EOF_DATATABLE	(feof(file))
#define _CHECKEOF_DATATABLE	if (_EOF_DATATABLE)	\
								return false
#define _READSTRINGBUFFERLINE(X)	if (!ReadStringBuffer(X))	\
										return false
#define _BREAKCOMMENTBUFFER	if (!CommentBuffer())	\
								break
#define _INITTINT	ti = -1
#define _LOADTINT	(tint[++ti])
#define _SAVETINT	(&_LOADTINT)

bool _DataTable::ReadStringBuffer(int nCol)
{
	if (!file)
	{
		return false;
	}
	for (int i=0; i<nCol; i++)
	{
		fscanf(file, "%s", buffer);
		_CHECKEOF_DATATABLE;
	}
	return true;
}

bool _DataTable::CommentBuffer()
{
	if (!file)
	{
		return false;
	}
	fscanf(file, "%s", buffer);
	_CHECKEOF_DATATABLE;
	if (buffer[0] == '#')
	{
		fscanf(file, "%[^\r\n]", bufferlong);
		_CHECKEOF_DATATABLE;
		CommentBuffer();
	}
	return true;
}

void _DataTable::SetFile(FILE * _file)
{
	file = _file;
}

bool _DataTable::DataTableDefine()
{
	_READSTRINGBUFFERLINE(2);
	strcpy(res.resdata.customconstfilename, res.resdata.datafoldername);
	_READSTRINGBUFFERLINE(2);
	strcat(res.resdata.customconstfilename, buffer);
	strcpy(res.resdata.spelldefinefilename, res.resdata.datafoldername);
	_READSTRINGBUFFERLINE(2);
	strcat(res.resdata.spelldefinefilename, buffer);
	strcpy(res.resdata.musicdefinefilename, res.resdata.datafoldername);
	_READSTRINGBUFFERLINE(2);
	strcat(res.resdata.musicdefinefilename, buffer);
	strcpy(res.resdata.scenedefinefilename, res.resdata.datafoldername);
	_READSTRINGBUFFERLINE(2);
	strcat(res.resdata.scenedefinefilename, buffer);
	strcpy(res.resdata.bulletdefinefilename, res.resdata.datafoldername);
	_READSTRINGBUFFERLINE(2);
	strcat(res.resdata.bulletdefinefilename, buffer);
	strcpy(res.resdata.enemydefinefilename, res.resdata.datafoldername);
	_READSTRINGBUFFERLINE(2);
	strcat(res.resdata.enemydefinefilename, buffer);
	strcpy(res.resdata.playerdefinefilename, res.resdata.datafoldername);
	_READSTRINGBUFFERLINE(2);
	strcat(res.resdata.playerdefinefilename, buffer);
	strcpy(res.resdata.spritedefinefilename, res.resdata.datafoldername);
	_READSTRINGBUFFERLINE(2);
	strcat(res.resdata.spritedefinefilename, buffer);
	strcpy(res.resdata.playershootdefinefilename, res.resdata.datafoldername);
	_READSTRINGBUFFERLINE(2);
	strcat(res.resdata.playershootdefinefilename, buffer);
	strcpy(res.resdata.playerghostdefinefilename, res.resdata.datafoldername);
	_READSTRINGBUFFERLINE(2);
	strcat(res.resdata.playerghostdefinefilename, buffer);
	return true;
}

bool _DataTable::PackageTableDefine()
{
	ZeroMemory(res.resdata.packagefilename, sizeof(char) * PACKAGEMAX * M_PATHMAX);
	_READSTRINGBUFFERLINE(2);

	while (!feof(file))
	{
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE;
		fscanf(file, "%s", res.resdata.packagefilename[tindex]);
	}
	return true;
}

bool _DataTable::TextureTableDefine()
{
	ZeroMemory(res.resdata.texfilename, sizeof(char) * TEXMAX * M_PATHMAX);
	_READSTRINGBUFFERLINE(2);
	while (!feof(file))
	{
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE;
		fscanf(file, "%s", res.resdata.texfilename[tindex]);
	}
	return true;
}

bool _DataTable::EffectTableDefine()
{
	ZeroMemory(res.resdata.effectsysfilename, sizeof(char) * EFFECTSYSTYPEMAX * M_PATHMAX);
	_READSTRINGBUFFERLINE(2);
	while (!feof(file))
	{
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE;
		fscanf(file, "%s", res.resdata.effectsysfilename[tindex]);
	}
	return true;
}

bool _DataTable::SETableDefine()
{
	ZeroMemory(res.resdata.sefilename, sizeof(char) * SEMAX * M_PATHMAX);
	_READSTRINGBUFFERLINE(2);
	while (!feof(file))
	{
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE;
		fscanf(file, "%s", res.resdata.sefilename[tindex]);
	}
	return true;
}

bool _DataTable::SceneDefineFile()
{
	ZeroMemory(res.scenedata, RSIZE_SCENE);
	_READSTRINGBUFFERLINE(2);
	while (!feof(file))
	{
		fscanf(file, "%d", &tindex);
		sceneData * item = &(res.scenedata[tindex]);
		_CHECKEOF_DATATABLE;
		fscanf(file, "%[^\t\r\n]",
			item->scenename);
	}
	return true;
}

bool _DataTable::CustomConstFile()
{
	res.ReleaseCustomConst();
	res.customconstdata = (customconstData *)malloc(RSIZE_CUSTOMCONST);
	ZeroMemory(res.customconstdata, RSIZE_CUSTOMCONST);
	_READSTRINGBUFFERLINE(4);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE;

		customconstData * item = &(res.customconstdata[tindex]);
		fscanf(file, "%s%d", 
			item->name, 
			&(item->value));

		_INITTINT;
	}
	return true;
}

bool _DataTable::SpellDefineFile()
{
	res.spelldata.clear();
	_READSTRINGBUFFERLINE(10);
	while (!feof(file))
	{
		_INITTINT;
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE;
		spellData _item;

		fscanf(file, "%d\t%[^\t]%d%d%d%I64d%d%x%d", 
			&(_item.spellnumber), 
			_item.spellname, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			&(_item.bonus), 
			&(_item.turntoscene), 
			_SAVETINT, 
			_SAVETINT);

		_INITTINT;
		_item.sno = tindex;
		_item.timelimit = _LOADTINT;
		_item.remain = _LOADTINT;
		_item.userID = _LOADTINT;
		_item.spellflag = _LOADTINT;
		_item.battleID = _LOADTINT;
		res.spelldata.push_back(_item);
	}
	return true;
}

bool _DataTable::MusicDefineFile()
{
	ZeroMemory(res.musdata, RSIZE_MUSIC);
	_READSTRINGBUFFERLINE(10);
	while (!feof(file))
	{
		_INITTINT;
		fscanf(file, "%d", &tindex);
		musicData * item = &(res.musdata[tindex]);
		_CHECKEOF_DATATABLE;

		fscanf(file, "%[^\t]%s%d%d%d\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t\r\n]", 
			item->musicname, 
			item->musicfilename, 
			&(item->startpos), 
			&(item->introlength), 
			&(item->alllength), 
			item->explain_1, 
			item->explain_2, 
			item->explain_3, 
			item->explain_4);

		_INITTINT;
	}
	return true;
}

bool _DataTable::BulletDefineFile()
{
	ZeroMemory(res.bulletdata, RSIZE_BULLET);
	_READSTRINGBUFFERLINE(17);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		bulletData * item = &(res.bulletdata[tindex]);
		_CHECKEOF_DATATABLE;

		fscanf(file, "%d%d%d%d%d%d%d%f%f%d%d%d%d%d%d", 
			&(item->tex_x), 
			&(item->tex_y), 
			&(item->tex_w), 
			&(item->tex_h), 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			&(item->collisionMain), 
			&(item->collisionSub), 
			_SAVETINT, 
			_SAVETINT, 
			&(item->nTurnAngle), 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT);

		_INITTINT;
		item->nRoll = _LOADTINT;
		item->nColor = _LOADTINT;
		item->collisiontype = _LOADTINT;
		item->fadecolor = _LOADTINT;
		item->bonuscolor = _LOADTINT;
		item->seID = _LOADTINT;
		item->blendtype = _LOADTINT;
		item->renderdepth = _LOADTINT;
	}
	return true;
}

bool _DataTable::EnemyDefineFile()
{
	ZeroMemory(res.enemydata, RSIZE_ENEMY);
	_READSTRINGBUFFERLINE(21);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		enemyData * item = &(res.enemydata[tindex]);
		_CHECKEOF_DATATABLE;

		fscanf(file, "%d%s%f%f%d%d%d%d%d%d%d%d%d%d%d%f%f\t%[^\t]\t%[^\t\r\n]", 
			_SAVETINT, 
			buffer,
			&(item->collision_w), 
			&(item->collision_h), 
			_SAVETINT, 
			&(item->standshake), 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			&(item->blastr),
			&(item->blastpower),
			item->name,
			item->ename);

		_INITTINT;
		item->faceIndex  = _LOADTINT;
		item->siid = SpriteItemManager::GetIndexByName(buffer);
		item->standFrame  = _LOADTINT;
		item->rightPreFrame  = _LOADTINT;
		item->rightFrame = _LOADTINT;
		item->leftPreFrame  = _LOADTINT;
		item->leftFrame = _LOADTINT;
		item->attackPreFrame  = _LOADTINT;
		item->attackFrame = _LOADTINT;
		item->storePreFrame  = _LOADTINT;
		item->storeFrame  = _LOADTINT;
		item->blastmaxtime = _LOADTINT;
	}
	return true;
}

bool _DataTable::PlayerDefineFile()
{
	ZeroMemory(res.playerdata, RSIZE_PLAYER);
	_READSTRINGBUFFERLINE(26);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		playerData * item = &(res.playerdata[tindex]);
		_CHECKEOF_DATATABLE;

		fscanf(file, "%f%f%f%f%f%d%d%d%f%f%d%d%d%d%d%d%d%d%d%d%f%f\t%[^\t]\t%[^\t\r\n]", 
			&(item->collision_r), 
			&(item->fastspeed), 
			&(item->slowspeed), 
			&(item->graze_r),
			&(item->chargespeed), 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			&(item->exsendparab),
			&(item->exsendparaa),
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			&(item->usetexw),
			&(item->usetexh),
			(item->name),
			(item->ename));

		_INITTINT;
		item->shotdelay = _LOADTINT;
		item->rechargedelay = _LOADTINT;
		item->bomblast = _LOADTINT;
		item->tex = _LOADTINT;
		item->faceIndex = _LOADTINT;
		item->tex_nCol = _LOADTINT;
		item->tex_nRow = _LOADTINT;
		item->startFrame = _LOADTINT;
		item->standFrame = _LOADTINT;
		item->leftPreFrame = _LOADTINT;
		item->leftFrame = _LOADTINT;
		item->rightPreFrame = _LOADTINT;
		item->rightFrame = _LOADTINT;
	}
	return true;
}

bool _DataTable::SpriteDefineFile()
{
	ZeroMemory(res.spritedata, RSIZE_SPRITE);
	_READSTRINGBUFFERLINE(8);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE;
		spriteData * item = &(res.spritedata[tindex]);

		fscanf(file, "%s%d%d%d%d%d", 
			item->spritename, 
			_SAVETINT, 
			&(item->tex_x), 
			&(item->tex_y), 
			&(item->tex_w), 
			&(item->tex_h));

		_INITTINT;
		item->tex = _LOADTINT;
	}
	return true;
}

bool _DataTable::PlayerShootDefineFile()
{
	ZeroMemory(res.playershootdata, RSIZE_PLAYERSHOOT);
	_READSTRINGBUFFERLINE(16);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE;
		playershootData * item = &(res.playershootdata[tindex]);

		fscanf(file, "%d%s%d%x%f%d%d%d%f%f%f%f%f%d", 
			_SAVETINT, 
			buffer,
			_SAVETINT, 
			_SAVETINT, 
			&(item->power), 
			&(item->hitonfactor),
			_SAVETINT, 
			&(item->angle), 
			&(item->speed), 
			&(item->scale),
			&(item->xbias), 
			&(item->ybias), 
			&(item->accelspeed), 
			_SAVETINT);

		_INITTINT;
		item->userID = _LOADTINT;
		item->siid = SpriteItemManager::GetIndexByName(buffer);
		item->timeMod = _LOADTINT;
		item->flag = _LOADTINT;
		item->arrange = _LOADTINT;
		item->seID = _LOADTINT;
	}
	return true;
}

bool _DataTable::PlayerGhostDefineFile()
{
	ZeroMemory(res.playerghostdata, RSIZE_PLAYERGHOST);
	_READSTRINGBUFFERLINE(11);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE;
		playerghostData * item = &(res.playerghostdata[tindex]);

		fscanf(file, "%d%f%f%f%x%d%f%d%d", 
			&(item->siID), 
			&(item->xadj), 
			&(item->yadj), 
			&(item->speed), 
			_SAVETINT, 
			&(item->shootangle), 
			&(item->mover), 
			&(item->startangle),
			_SAVETINT);

		_INITTINT;
		item->flag = _LOADTINT;
		item->blend = _LOADTINT;
	}
	return true;
}


FILE * Data::checkTableFile(BYTE type)
{
	getFile(type);
	if (!nowfilename)
	{
		return NULL;
	}
	FILE * file = fopen(nowfilename, "rb");
	if (!file)
	{
		return NULL;
	}
	int tgameversion = -1;
	char tsignature[M_STRMAX];
	int tfiletype = -1;

	fscanf(file, "%x%s%x", &tgameversion, tsignature, &tfiletype);
	if (tgameversion != GAME_VERSION || strcmp(tsignature, GAME_SIGNATURE) || tfiletype != type)
	{
		fclose(file);
		return NULL;
	}
	return file;
}

bool Data::GetTableFile(BYTE type)
{
	if (!(type & DATA_TABLEHEADER))
	{
		return false;
	}
	FILE * file = checkTableFile(type);
	if (file == NULL)
	{
		return false;
	}

	_DataTable::datatable.SetFile(file);

	char buffer[M_STRMAX];
	int tindex;
	int tint[32];
	switch (type)
	{
	case DATA_DATATABLEDEFINE:
		_DataTable::datatable.DataTableDefine();
		break;
	case DATA_PACKAGETABLEDEFINE:
		_DataTable::datatable.PackageTableDefine();
		break;
	case DATA_TEXTURETABLEDEFINE:
		_DataTable::datatable.TextureTableDefine();
		break;
	case DATA_EFFECTTABLEDEFINE:
		_DataTable::datatable.EffectTableDefine();
		break;
	case DATA_SETABLEDEFINE:
		_DataTable::datatable.SETableDefine();
		break;

	case DATA_CUSTOMCONSTFILE:
		_DataTable::datatable.CustomConstFile();
		break;
	case DATA_SPELLDEFINEFILE:
		_DataTable::datatable.SpellDefineFile();
		break;
	case DATA_MUSICDEFINEFILE:
		_DataTable::datatable.MusicDefineFile();
		break;
	case DATA_SCENEDEFINEFILE:
		_DataTable::datatable.SceneDefineFile();
		break;

	case DATA_BULLETDEFINEFILE:
		_DataTable::datatable.BulletDefineFile();
		break;
	case DATA_ENEMYDEFINEFILE:
		_DataTable::datatable.EnemyDefineFile();
		break;
	case DATA_PLAYERDEFINEFILE:
		_DataTable::datatable.PlayerDefineFile();
		break;
	case DATA_SPRITEDEFINEFILE:
		_DataTable::datatable.SpriteDefineFile();
		break;

	case DATA_PLAYERSHOOTDEFINE:
		_DataTable::datatable.PlayerShootDefineFile();
		break;
	case DATA_PLAYERGHOSTDEFINE:
		_DataTable::datatable.PlayerGhostDefineFile();
		break;
	}
	fclose(file);
	return true;
}
