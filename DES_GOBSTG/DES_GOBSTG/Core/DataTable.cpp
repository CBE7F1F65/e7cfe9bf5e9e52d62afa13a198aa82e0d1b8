#include "Data.h"
#include "BResource.h"
#include "DataTable.h"
#include "SpriteItemManager.h"

_DataTable _DataTable::datatable;

void _DataTable::SetFile(FILE * _file)
{
	file = _file;
}

bool _DataTable::DataTableDefine()
{
	fscanf(file, "%s%s",
		buffer, buffer);
	if (feof(file))
	{
		return false;
	}

	strcpy(res.resdata.customconstfilename, res.resdata.datafoldername);
	fscanf(file, "%s%s",
		buffer, buffer);
	strcat(res.resdata.customconstfilename, buffer);
	if (feof(file))
	{
		return false;
	}
	strcpy(res.resdata.spelldefinefilename, res.resdata.datafoldername);
	fscanf(file, "%s%s",
		buffer, buffer);
	strcat(res.resdata.spelldefinefilename, buffer);
	if (feof(file))
	{
		return false;
	}
	strcpy(res.resdata.musicdefinefilename, res.resdata.datafoldername);
	fscanf(file, "%s%s",
		buffer, buffer);
	strcat(res.resdata.musicdefinefilename, buffer);
	if (feof(file))
	{
		return false;
	}
	strcpy(res.resdata.scenedefinefilename, res.resdata.datafoldername);
	fscanf(file, "%s%s",
		buffer, buffer);
	strcat(res.resdata.scenedefinefilename, buffer);
	if (feof(file))
	{
		return false;
	}
	strcpy(res.resdata.bulletdefinefilename, res.resdata.datafoldername);
	fscanf(file, "%s%s",
		buffer, buffer);
	strcat(res.resdata.bulletdefinefilename, buffer);
	if (feof(file))
	{
		return false;
	}
	strcpy(res.resdata.enemydefinefilename, res.resdata.datafoldername);
	fscanf(file, "%s%s",
		buffer, buffer);
	strcat(res.resdata.enemydefinefilename, buffer);
	if (feof(file))
	{
		return false;
	}
	strcpy(res.resdata.playerdefinefilename, res.resdata.datafoldername);
	fscanf(file, "%s%s",
		buffer, buffer);
	strcat(res.resdata.playerdefinefilename, buffer);
	if (feof(file))
	{
		return false;
	}
	strcpy(res.resdata.spritedefinefilename, res.resdata.datafoldername);
	fscanf(file, "%s%s",
		buffer, buffer);
	strcat(res.resdata.spritedefinefilename, buffer);
	if (feof(file))
	{
		return false;
	}
	strcpy(res.resdata.playerbulletdefinefilename, res.resdata.datafoldername);
	fscanf(file, "%s%s",
		buffer, buffer);
	strcat(res.resdata.playerbulletdefinefilename, buffer);
	if (feof(file))
	{
		return false;
	}
	strcpy(res.resdata.playershootdefinefilename, res.resdata.datafoldername);
	fscanf(file, "%s%s",
		buffer, buffer);
	strcat(res.resdata.playershootdefinefilename, buffer);
	if (feof(file))
	{
		return false;
	}
	strcpy(res.resdata.playerghostdefinefilename, res.resdata.datafoldername);
	fscanf(file, "%s%s",
		buffer, buffer);
	strcat(res.resdata.playerghostdefinefilename, buffer);
	if (feof(file))
	{
		return true;
	}
	return false;
}

bool _DataTable::PackageTableDefine()
{
	ZeroMemory(res.resdata.packagefilename, sizeof(char) * PACKAGEMAX * M_PATHMAX);
	fscanf(file, "%s%s",
		buffer, buffer);
	while (!feof(file))
	{
		fscanf(file, "%d", &tindex);
		if (feof(file))
		{
			return true;
		}
		fscanf(file, "%s", res.resdata.packagefilename[tindex]);
	}
	return true;
}

bool _DataTable::TextureTableDefine()
{
	ZeroMemory(res.resdata.texfilename, sizeof(char) * TEXMAX * M_PATHMAX);
	fscanf(file, "%s%s",
		buffer, buffer);
	while (!feof(file))
	{
		fscanf(file, "%d", &tindex);
		if (feof(file))
		{
			return true;
		}
		fscanf(file, "%s", res.resdata.texfilename[tindex]);
	}
	return true;
}

bool _DataTable::EffectTableDefine()
{
	ZeroMemory(res.resdata.effectsysfilename, sizeof(char) * EFFECTSYSTYPEMAX * M_PATHMAX);
	fscanf(file, "%s%s",
		buffer, buffer);
	while (!feof(file))
	{
		fscanf(file, "%d", &tindex);
		if (feof(file))
		{
			return true;
		}
		fscanf(file, "%s", res.resdata.effectsysfilename[tindex]);
	}
	return true;
}

bool _DataTable::SETableDefine()
{
	ZeroMemory(res.resdata.sefilename, sizeof(char) * SEMAX * M_PATHMAX);
	fscanf(file, "%s%s",
		buffer, buffer);
	while (!feof(file))
	{
		fscanf(file, "%d", &tindex);
		if (feof(file))
		{
			return true;
		}
		fscanf(file, "%s", res.resdata.sefilename[tindex]);
	}
	return true;
}

bool _DataTable::CustomConstFile()
{
	res.ReleaseCustomConst();
	res.customconstdata = (customconstData *)malloc(RSIZE_CUSTOMCONST);
	ZeroMemory(res.customconstdata, RSIZE_CUSTOMCONST);
	fscanf(file, "%s%s%s", 
		buffer, buffer, buffer);
	while (!feof(file))
	{
		fscanf(file, "%d", &tindex);
		if (feof(file))
		{
			return true;
		}
		customconstData * item = &(res.customconstdata[tindex]);
		fscanf(file, "%s%d", 
			item->name, 
			&(item->value));
	}
	return true;
}

bool _DataTable::SpellDefineFile()
{
	res.spelldata.clear();
	fscanf(file, "%s%s%s%s%s%s%s%s%s%s", 
		buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer);
	while (!feof(file))
	{
		fscanf(file, "%d", &tindex);
		if (feof(file))
		{
			return true;
		}
		spellData _item;
		fscanf(file, "%d\t%[^\t]%d%d%d%I64d%d%x%d", 
			&(_item.spellnumber), 
			_item.spellname, 
			&(tint[0]), 
			&(tint[1]), 
			&(tint[2]), 
			&(_item.bonus), 
			&(_item.turntoscene), 
			&(tint[3]), 
			&(tint[4]));
		_item.sno = tindex;
		_item.timelimit = tint[0];
		_item.remain = tint[1];
		_item.userID = tint[2];
		_item.spellflag = tint[3];
		_item.battleID = tint[4];
		res.spelldata.push_back(_item);
	}
	return true;
}

bool _DataTable::MusicDefineFile()
{
	ZeroMemory(res.musdata, RSIZE_MUSIC);
	fscanf(file, "%s%s%s%s%s%s%s%s%s%s", 
		buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer);
	while (!feof(file))
	{
		fscanf(file, "%d", &tindex);
		musicData * item = &(res.musdata[tindex]);
		if (feof(file))
		{
			return true;
		}
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
	}
	return true;
}

bool _DataTable::SceneDefineFile()
{
	ZeroMemory(res.scenedata, RSIZE_SCENE);
	fscanf(file, "%s%s",
		buffer, buffer);
	while (!feof(file))
	{
		fscanf(file, "%d", &tindex);
		sceneData * item = &(res.scenedata[tindex]);
		if (feof(file))
		{
			return true;
		}
		fscanf(file, "%[^\t\r\n]",
			item->scenename);
	}
	return true;
}

bool _DataTable::BulletDefineFile()
{
	ZeroMemory(res.bulletdata, RSIZE_BULLET);
	fscanf(file, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", 
		buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer);
	while (!feof(file))
	{
		fscanf(file, "%d", &tindex);
		bulletData * item = &(res.bulletdata[tindex]);
		if (feof(file))
		{
			return true;
		}
		fscanf(file, "%d%d%d%d%d%d%d%f%f%d%d%d%d%d%d", 
			&(item->tex_x), 
			&(item->tex_y), 
			&(item->tex_w), 
			&(item->tex_h), 
			&(tint[0]), 
			&(tint[1]), 
			&(tint[2]), 
			&(item->collisionMain), 
			&(item->collisionSub), 
			&(tint[3]),
			&(tint[4]), 
			&(item->nTurnAngle), 
			&(tint[5]), 
			&(tint[6]), 
			&(tint[7]));
		item->nRoll = tint[0];
		item->nColor = tint[1];
		item->collisiontype = tint[2];
		item->fadecolor = tint[3];
		item->bonuscolor = tint[4];
		item->seID = tint[5];
		item->blendtype = tint[6];
		item->renderdepth = tint[7];
	}
	return true;
}

bool _DataTable::EnemyDefineFile()
{
	ZeroMemory(res.enemydata, RSIZE_ENEMY);
	fscanf(file, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", 
		buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer);
	while (!feof(file))
	{
		fscanf(file, "%d", &tindex);
		enemyData * item = &(res.enemydata[tindex]);
		if (feof(file))
		{
			return true;
		}
		fscanf(file, "%d%s%f%f%d%d%d%d%d%d%d%d%d%d%d%f%f\t%[^\t]\t%[^\t\r\n]", 
			&(tint[0]), 
			buffer,
			&(item->collision_w), 
			&(item->collision_h), 
			&(tint[1]), 
			&(item->standshake), 
			&(tint[2]), 
			&(tint[3]),
			&(tint[4]), 
			&(tint[5]),
			&(tint[6]), 
			&(tint[7]),
			&(tint[8]), 
			&(tint[9]), 
			&(tint[10]),
			&(item->blastr),
			&(item->blastpower),
			item->name,
			item->ename);
		item->faceIndex  = tint[0];
		item->siid = SpriteItemManager::GetIndexByName(buffer);
		item->standFrame  = tint[1];
		item->rightPreFrame  = tint[2];
		item->rightFrame = tint[3];
		item->leftPreFrame  = tint[4];
		item->leftFrame = tint[5];
		item->attackPreFrame  = tint[6];
		item->attackFrame = tint[7];
		item->storePreFrame  = tint[8];
		item->storeFrame  = tint[9];
		item->blastmaxtime = tint[10];
	}
	return true;
}

bool _DataTable::PlayerDefineFile()
{
	ZeroMemory(res.playerdata, RSIZE_PLAYER);
	fscanf(file, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", 
		buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer);
	while (!feof(file))
	{
		fscanf(file, "%d", &tindex);
		playerData * item = &(res.playerdata[tindex]);
		if (feof(file))
		{
			return true;
		}
		fscanf(file, "%f%f%f%f%f%d%d%d%d%d%d%d%d%d%d%d%d%d%f%f\t%[^\t]\t%[^\t\r\n]", 
			&(item->collision_r), 
			&(item->fastspeed), 
			&(item->slowspeed), 
			&(item->graze_r),
			&(item->chargespeed), 
			&(tint[0]), 
			&(tint[1]), 
			&(tint[2]), 
			&(tint[3]), 
			&(tint[4]), 
			&(tint[5]), 
			&(tint[6]), 
			&(tint[7]), 
			&(tint[8]), 
			&(tint[9]), 
			&(tint[10]), 
			&(tint[11]), 
			&(tint[12]), 
			&(item->usetexw),
			&(item->usetexh),
			(item->name),
			(item->ename));
		item->shotdelay = tint[0];
		item->rechargedelay = tint[1];
		item->bomblast = tint[2];
		item->tex = tint[3];
		item->faceIndex = tint[4];
		item->tex_nCol = tint[5];
		item->tex_nRow = tint[6];
		item->startFrame = tint[7];
		item->standFrame = tint[8];
		item->leftPreFrame = tint[9];
		item->leftFrame = tint[10];
		item->rightPreFrame = tint[11];
		item->rightFrame = tint[12];
	}
	return true;
}

bool _DataTable::SpriteDefineFile()
{
	ZeroMemory(res.spritedata, RSIZE_SPRITE);
	fscanf(file, "%s%s%s%s%s%s%s", 
		buffer, buffer, buffer, buffer, buffer, buffer, buffer);
	while (!feof(file))
	{
		fscanf(file, "%d", &tindex);
		if (feof(file))
		{
			return true;
		}
		spriteData * item = &(res.spritedata[tindex]);
		fscanf(file, "%s%d%d%d%d%d", 
			item->spritename, 
			&(tint[0]), 
			&(item->tex_x), 
			&(item->tex_y), 
			&(item->tex_w), 
			&(item->tex_h));
		item->tex = tint[0];
	}
	return true;
}

bool _DataTable::PlayerBulletDefineFile()
{
	ZeroMemory(res.playerbulletdata, RSIZE_PLAYERBULLET);
	fscanf(file, "%s%s%s%s%s%s", 
		buffer, buffer, buffer, buffer, buffer, buffer);
	while (!feof(file))
	{
		fscanf(file, "%d", &tindex);
		if (feof(file))
		{
			return true;
		}
		playerbulletData * item = &(res.playerbulletdata[tindex]);
		fscanf(file, "%d%f%f%f%f", 
			&(tint[0]), 
			&(item->x), 
			&(item->y), 
			&(item->w), 
			&(item->h));
		item->tex = tint[0];
	}
	return true;
}

bool _DataTable::PlayerShootDefineFile()
{
	ZeroMemory(res.playershootdata, RSIZE_PLAYERSHOOT);
	fscanf(file, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", 
		buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer);
	while (!feof(file))
	{
		fscanf(file, "%d", &tindex);
		if (feof(file))
		{
			return true;
		}
		playershootData * item = &(res.playershootdata[tindex]);
		fscanf(file, "%d%d%d%x%f%d%d%d%f%f%f%f%f%d", 
			&(tint[0]), 
			&(tint[1]), 
			&(tint[2]), 
			&(tint[3]), 
			&(item->power), 
			&(item->hitonfactor),
			&(tint[4]), 
			&(item->angle), 
			&(item->speed), 
			&(item->scale),
			&(item->xbias), 
			&(item->ybias), 
			&(item->accelspeed), 
			&(tint[5]));
		item->userID = tint[0];
		item->ID = tint[1];
		item->timeMod = tint[2];
		item->flag = tint[3];
		item->arrange = tint[4];
		item->seID = tint[5];
	}
	return true;
}

bool _DataTable::PlayerGhostDefineFile()
{
	ZeroMemory(res.playerghostdata, RSIZE_PLAYERGHOST);
	fscanf(file, "%s%s%s%s%s%s%s%s%s%s", 
		buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer);
	while (!feof(file))
	{
		fscanf(file, "%d", &tindex);
		if (feof(file))
		{
			return true;
		}
		playerghostData * item = &(res.playerghostdata[tindex]);
		fscanf(file, "%d%f%f%f%x%d%f%d%d", 
			&(item->siID), 
			&(item->xadj), 
			&(item->yadj), 
			&(item->speed), 
			&(tint[0]), 
			&(item->shootangle), 
			&(item->mover), 
			&(item->startangle),
			&(tint[1]));
		item->flag = tint[0];
		item->blend = tint[1];
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

	case DATA_PLAYERBULLETDEFINE:
		_DataTable::datatable.PlayerBulletDefineFile();
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
