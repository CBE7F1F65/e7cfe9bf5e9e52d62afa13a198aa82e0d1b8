#include "SpriteItemManager.h"
#include "FrontDisplayName.h"
#include "BResource.h"

HTEXTURE * SpriteItemManager::tex;
int SpriteItemManager::yesIndex = 0;
int SpriteItemManager::noIndex = 0;
int SpriteItemManager::cancelIndex = 0;
int SpriteItemManager::confirmIndex = 0;

FrontSprite SpriteItemManager::frontsprite[FRONTSPRITEMAX];

SpriteItemManager::SpriteItemManager()
{
	ZeroMemory(frontsprite, sizeof(FrontSprite) * FRONTSPRITEMAX);
}

SpriteItemManager::~SpriteItemManager()
{

}

void SpriteItemManager::Init(HTEXTURE * _tex)
{
	tex = _tex;
	FreeFrontSprite();
}

void SpriteItemManager::Release()
{
	FreeFrontSprite();
}

HTEXTURE SpriteItemManager::GetTexture(int index)
{
	if (index < 0 || index >= res.spritenumber || !tex)
	{
		return NULL;
	}
	return tex[res.spritedata[index].tex];
}

float SpriteItemManager::GetTexX(int index)
{
	if (index < 0 || index >= res.spritenumber)
	{
		return 0;
	}
	return res.spritedata[index].tex_x;
}

float SpriteItemManager::GetTexY(int index)
{
	if (index < 0 || index >= res.spritenumber)
	{
		return 0;
	}
	return res.spritedata[index].tex_y;
}

float SpriteItemManager::GetTexW(int index)
{
	if (index < 0 || index >= res.spritenumber)
	{
		return 0;
	}
	return res.spritedata[index].tex_w;
}

float SpriteItemManager::GetTexH(int index)
{
	if (index < 0 || index >= res.spritenumber)
	{
		return 0;
	}
	return res.spritedata[index].tex_h;
}

void SpriteItemManager::RenderFrontSprite()
{
	for (int i=0; i<FRONTSPRITEMAX; i++)
	{
		if (frontsprite[i].sprite)
		{
			frontsprite[i].sprite->RenderEx(frontsprite[i].x, frontsprite[i].y, frontsprite[i].rot, frontsprite[i].hscale, frontsprite[i].vscale);
		}
	}
}

int SpriteItemManager::GetIndexByName(const char * spritename)
{
	if (!spritename)
	{
		return -1;
	}
	if (!strlen(spritename))
	{
		return -1;
	}
	for (int i=0; i<res.spritenumber; i++)
	{
		if (!strcmp(spritename, res.spritedata[i].spritename))
		{
			return i;
			break;
		}
	}
	return -1;
}

spriteData * SpriteItemManager::CastSprite(int index)
{
	if (index >= 0 && index < res.spritenumber)
	{
		return &(res.spritedata[index]);
	}
	return NULL;
}

bool SpriteItemManager::SetSprite(int index, hgeSprite * sprite, HTEXTURE * tex)
{
	if (!sprite)
	{
		return false;
	}
	if (index < 0)
	{
		sprite->SetTextureRect(0, 0, 0, 0);
		return true;
	}
	spriteData * _sd = CastSprite(index);
	if (!_sd)
	{
		return false;
	}
	sprite->SetTexture(tex[_sd->tex]);
	sprite->SetTextureRect(_sd->tex_x, _sd->tex_y, 
		_sd->tex_w < 0 ? hge->Texture_GetWidth(tex[_sd->tex])-_sd->tex_x : _sd->tex_w, 
		_sd->tex_h < 0 ? hge->Texture_GetHeight(tex[_sd->tex])-_sd->tex_y : _sd->tex_h);
	return true;
}

void SpriteItemManager::FreeFrontSprite(int ID/* =-1 */)
{
	if (ID >= FRONTSPRITEMAX)
	{
		return;
	}
	if (ID < 0)
	{
		for (int i=0; i<FRONTSPRITEMAX; i++)
		{
			FreeFrontSprite(i);
		}
		return;
	}
	FreeSprite(&frontsprite[ID].sprite);
	frontsprite[ID].sprite = NULL;
}

hgeSprite * SpriteItemManager::BuildFrontSprite(int ID, int index)
{
	if (ID < 0 || ID >= FRONTSPRITEMAX)
	{
		return NULL;
	}
	if (index >= 0)
	{
		FreeFrontSprite(ID);
		CreateSprite(index, &frontsprite[ID].sprite);
	}
	return frontsprite[ID].sprite;
}

hgeSprite * SpriteItemManager::BuildFrontSpriteByName(int ID, const char * spritename)
{
	if (ID < 0 || ID >= FRONTSPRITEMAX)
	{
		return NULL;
	}
	FreeFrontSprite(ID);
	CreateSpriteByName(spritename, &frontsprite[ID].sprite);
	return frontsprite[ID].sprite;
}

void SpriteItemManager::SetFrontSpriteValue(int ID, float x, float y, int angle/* =0 */, float hscale/* =1.0f */, float vscale/* =0.0f */)
{
	if (ID < 0 || ID >= FRONTSPRITEMAX)
	{
		return;
	}
	frontsprite[ID].x = x;
	frontsprite[ID].y = y;
	frontsprite[ID].rot = ARC(angle);
	frontsprite[ID].hscale = hscale;
	frontsprite[ID].vscale = vscale;
}

hgeSprite * SpriteItemManager::CreateSprite(int index)
{
	hgeSprite * sprite;
	if (!tex)
	{
		return NULL;
	}
	if (index < 0)
	{
		return CreateSpriteByName(SI_NULL);
	}
	else
	{
		sprite = new hgeSprite(tex[res.spritedata[index].tex], res.spritedata[index].tex_x, res.spritedata[index].tex_y, res.spritedata[index].tex_w, res.spritedata[index].tex_h);
	}
	return sprite;
}

bool SpriteItemManager::CreateSprite(int index, hgeSprite ** sprite)
{
	if (!sprite)
	{
		return false;
	}
	*sprite = CreateSprite(index);
	if (*sprite)
	{
		return true;
	}
	return false;
}

bool SpriteItemManager::ChangeSprite(int index, hgeSprite * sprite)
{
	if (!sprite)
	{
		return false;
	}
	sprite->SetTexture(tex[res.spritedata[index].tex]);
	sprite->SetTextureRect(res.spritedata[index].tex_x, res.spritedata[index].tex_y, res.spritedata[index].tex_w, res.spritedata[index].tex_h);
	return true;
}

hgeSprite * SpriteItemManager::CreateSpriteByName(const char * spritename)
{
	int index = GetIndexByName(spritename);
	if (index >= 0)
	{
		return CreateSprite(index);
	}
	return NULL;
}

bool SpriteItemManager::CreateSpriteByName(const char * spritename, hgeSprite ** sprite)
{
	if (!sprite)
	{
		return false;
	}
	*sprite = CreateSpriteByName(spritename);
	if (*sprite)
	{
		return true;
	}
	return false;
}

void SpriteItemManager::FreeSprite(hgeSprite ** sprite)
{
	if (sprite && *sprite)
	{
		free(*sprite);
		*sprite = NULL;
	}
}

bool SpriteItemManager::ptFace(int index, hgeSprite * sprite)
{
	if (!sprite || !tex)
	{
		return false;
	}
	if (index < 0)
	{
		sprite->SetTextureRect(0, 0, 0, 0);
		return true;
	}
	ChangeSprite(res.playerdata[index].faceSIID, sprite);
	return true;
}
/*
bool SpriteItemManager::ptName(int index, hgeSprite * sprite, bool enemy)
{
	if (!sprite || !tex)
	{
		return false;
	}
	if (index < 0)
	{
		sprite->SetTextureRect(0, 0, 0, 0);
		return true;
	}
	spriteData * tsd = &(res.spritedata[index+(enemy?nameIndexEnemy:nameIndexPlayer)]);
	sprite->SetTexture(tex[tsd->tex]);
	sprite->SetTextureRect(tsd->tex_x, tsd->tex_y, tsd->tex_w, tsd->tex_h);
	return true;
}
*/