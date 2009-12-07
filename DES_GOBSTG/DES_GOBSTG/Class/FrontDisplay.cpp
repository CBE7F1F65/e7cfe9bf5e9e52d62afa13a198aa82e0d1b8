#include "FrontDisplay.h"
#include "SpriteItemManager.h"
#include "BResource.h"
#include "FrontDisplayName.h"
#include "processPrep.h"
#include "BossInfo.h"
#include "Fontsys.h"
#include "EffectIDDefine.h"

#define FDISP_LIFEINDI_EMPTY	0
#define FDISP_LIFEINDI_HALF		1
#define FDISP_LIFEINDI_FULL		2

FrontDisplay FrontDisplay::fdisp;

FrontDisplay::FrontDisplay()
{
	ZeroMemory(&panel, sizeof(ftPanelSet));
	ZeroMemory(&info, sizeof(ftInfoSet));
	ZeroMemory(&bignum, sizeof(ftNumSet));
	ZeroMemory(&itemnum, sizeof(ftItemNumSet));
	ZeroMemory(&spellpointnum, sizeof(ftSpellPointNumSet));
	ZeroMemory(&gameinfodisplay, sizeof(ftGameInfoDisplaySet));
	ZeroMemory(&ascii, sizeof(ftAscIISet));
	postprintlist.clear();
}

FrontDisplay::~FrontDisplay()
{
}

void FrontDisplay::BuildPostPrint(hgeFont * font, float x, float y, const char * str, int align/* =HGETEXT_CENTER|HGETEXT_MIDDLE */, float scale, float properation, float rotation, float tracking, float spacing)
{
	fdPostPrint _postprint;
	postprintlist.push_back(_postprint);
	fdPostPrint * _ppostprint = &(*(postprintlist.rbegin()));
	if (!font)
	{
		font = info.asciifont;
	}
	_ppostprint->font = font;
	_ppostprint->x = x;
	_ppostprint->y = y;
	_ppostprint->align = align;
	_ppostprint->scale = scale;
	_ppostprint->properation = properation;
	_ppostprint->rotation = rotation;
	_ppostprint->tracking = tracking;
	_ppostprint->spacing = spacing;
	if (str)
	{
		if (strlen(str) >= M_STRMAX)
		{
			char buffer[M_STRMAX];
			strncpy(buffer, str, M_STRMAX);
			strcpy(_ppostprint->str, buffer);
		}
		else
		{
			strcpy(_ppostprint->str, str);
		}
	}
	else
	{
		strcpy(_ppostprint->str, "");
	}
}

void FrontDisplay::RenderPostPrint()
{
	if (postprintlist.size())
	{
		for (list<fdPostPrint>::iterator it=postprintlist.begin(); it!=postprintlist.end(); it++)
		{
			if (it->font)
			{
				it->font->RenderEx(it->x, it->y, it->align, it->str, it->scale, it->properation, it->rotation, it->tracking, it->spacing);
			}
		}
	}
	postprintlist.clear();
}

void FrontDisplay::SetValue(LONGLONG _llval, int _ival, float _fval, bool _bval)
{
	llval = _llval;
	ival = _ival;
	fval = _fval;
	bval = _bval;
}

void FrontDisplay::SetState(BYTE type, BYTE state/* =FDISP_STATE_COUNT */)
{
	switch (type)
	{
	case FDISP_PANEL:
		panelcountup = state;
		break;
	}
}

void FrontDisplay::RenderHeadInfo(BYTE playerindex)
{
	float yoffset = 24.0f;
	float ybottomoffset = 32.0f;
	float yoffsetadd = 22.0f;
	float px = Player::p[playerindex].x;
	float py = Player::p[playerindex].y;
	DWORD color = 0xffffffff;
	BYTE alpha = 0xff;
	if (Player::p[playerindex].bCharge)
	{
		float tyoffset = yoffset;
		yoffset += yoffsetadd;
		if (py-tyoffset < M_GAMESQUARE_TOP)
		{
			tyoffset = -ybottomoffset;
			ybottomoffset += yoffsetadd;
		}
		BYTE ncharge;
		BYTE nchargemax;
		if (Player::p[playerindex].chargetimer < 16)
		{
			alpha = Player::p[playerindex].chargetimer * 16;
		}
		Player::p[playerindex].GetNCharge(&ncharge, &nchargemax);
		if (Player::p[playerindex].chargetimer % 16 < 8)
		{
			color = (alpha<<24)+0xA0ffA0;
		}
		else
		{
			color = (alpha<<24)+0xffffff;
		}
		gameinfodisplay.charge->SetColor(color);
		gameinfodisplay.charge->Render(px, py-tyoffset-10);
		info.headdigitfont->SetColor(color);
		info.headdigitfont->printf(px, py-tyoffset-6, HGETEXT_CENTER, "%d / %d", ncharge, nchargemax);
	}
	if (gameinfodisplay.lastlifecountdown[playerindex])
	{
		float tyoffset = yoffset;
		yoffset += yoffsetadd;
		if (py-tyoffset < M_GAMESQUARE_TOP)
		{
			tyoffset = -ybottomoffset;
			ybottomoffset += yoffsetadd;
		}
		alpha = 0xff;
		gameinfodisplay.lastlifecountdown[playerindex]--;
		if (gameinfodisplay.lastlifecountdown[playerindex] < 16)
		{
			alpha = gameinfodisplay.lastlifecountdown[playerindex] * 16;
		}
		color = (alpha<<24)+0xffffff;
		gameinfodisplay.caution->SetColor(color);
		gameinfodisplay.caution->Render(px, py-tyoffset-8);
		gameinfodisplay.lastlife->SetColor(color);
		gameinfodisplay.lastlife->Render(px, py-tyoffset);
	}
	if (gameinfodisplay.gaugefilledcountdown[playerindex])
	{
		float tyoffset = yoffset;
		yoffset += yoffsetadd;
		if (py-tyoffset < M_GAMESQUARE_TOP)
		{
			tyoffset = -ybottomoffset;
			ybottomoffset += yoffsetadd;
		}
		BYTE ncharge;
		BYTE nchargemax;
		Player::p[playerindex].GetNCharge(&ncharge, &nchargemax);
		gameinfodisplay.gaugefilledcountdown[playerindex]--;
		alpha = 0xff;
		if (gameinfodisplay.gaugefilledcountdown[playerindex] < 16)
		{
			alpha = gameinfodisplay.gaugefilledcountdown[playerindex] * 16;
		}
		color = (alpha<<24)+0xffffff;
		gameinfodisplay.gaugefilled->SetColor(color);
		gameinfodisplay.gaugefilled->Render(px, py-tyoffset-10);
		gameinfodisplay.gaugelevel->SetColor(color);
		gameinfodisplay.gaugelevel->Render(px-16, py-tyoffset);
		info.headdigitfont->SetColor(color);
		info.headdigitfont->printf(px+16, py-tyoffset-8, HGETEXT_CENTER, "%d", nchargemax);
	}
	if (gameinfodisplay.lilycountdown)
	{
		float tyoffset = yoffset;
		yoffset += yoffsetadd;
		if (py-tyoffset < M_GAMESQUARE_TOP)
		{
			tyoffset = -ybottomoffset;
			ybottomoffset += yoffsetadd;
		}
		alpha = 0xff;
		gameinfodisplay.lilycountdown--;
		if (gameinfodisplay.lilycountdown < 16)
		{
			alpha = gameinfodisplay.lilycountdown * 16;
		}
		color = (alpha<<24)+0xffffff;
		gameinfodisplay.caution->SetColor(color);
		gameinfodisplay.caution->Render(px, py-tyoffset-8);
		gameinfodisplay.lily->SetColor(color);
		gameinfodisplay.lily->Render(px, py-tyoffset);
	}
}

void FrontDisplay::RenderPanel()
{
	if (panelcountup)
	{
		if (panelcountup < 0xff)
		{
			int tcountup = panelcountup;
			tcountup += 0x08;
			if (tcountup > 0xff)
			{
				tcountup = 0xff;
			}
			panelcountup = tcountup;
			DWORD tcol = (panelcountup<<16)|(panelcountup<<8)|panelcountup|0xff000000;
			for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
			{
				panel.leftedge[i]->SetColor(tcol);
				panel.rightedge[i]->SetColor(tcol);
				panel.topedge[i]->SetColor(tcol);
				panel.bottomedge[i]->SetColor(tcol);
			}
		}

		if (panelcountup == 0xff)
		{
			float spellpointx[M_PL_MATCHMAXPLAYER];
			spellpointx[0] = M_GAMESQUARE_RIGHT_0-panel.spellpoint->GetWidth();
			spellpointx[1] = M_GAMESQUARE_LEFT_1;

			for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
			{
				panel.spellpoint->Render(spellpointx[i], M_GAMESQUARE_TOP);
				spriteData * _spd = SpriteItemManager::CastSprite(panel.combobarindex);
				float fcombogage = ((float)Player::p[i].nComboGage) / PLAYER_COMBOGAGEMAX;
				panel.combobar->SetTextureRect(_spd->tex_x, _spd->tex_y, _spd->tex_w*fcombogage, _spd->tex_h);
				panel.combobar->SetHotSpot(0, 0);
				panel.combobar->Render(spellpointx[i]+2, M_GAMESQUARE_TOP+30);

				bool usered = true;
				if (Player::p[i].nComboGage < PLAYER_COMBOALERT && Player::p[i].nComboGage > PLAYER_COMBORESET)
				{
					if (time % 8 < 4)
					{
						usered = false;
					}
				}
				int nComboHit = Player::p[i].nComboHit;
				char buffer[M_STRITOAMAX];
				sprintf(buffer, "%d%c", nComboHit, '0'+(usered?21:20));
				if (usered)
				{
					for (int j=0; j<strlen(buffer)-1; j++)
					{
						buffer[j] += 10;
					}
				}
				info.spellpointdigitfont->printf(spellpointx[i]+38, M_GAMESQUARE_TOP+16, HGETEXT_RIGHT, "%s", buffer);
				int nSpellPoint = Player::p[i].nSpellPoint;
				info.spellpointdigitfont->printf(spellpointx[i]+38, M_GAMESQUARE_TOP+16, HGETEXT_LEFT, "%06d", nSpellPoint);

				_spd = SpriteItemManager::CastSprite(panel.slotindex);
				float fslot = Player::p[i].fChargeMax / PLAYER_CHARGEMAX;
				panel.slot->SetTextureRect(_spd->tex_x, _spd->tex_y, _spd->tex_w*fslot, _spd->tex_h);
				panel.slot->SetHotSpot(0, _spd->tex_h);
				panel.slot->SetColor(0xff808080);
				panel.slot->Render(M_GAMESQUARE_LEFT_(i)+16, M_GAMESQUARE_BOTTOM);
				fslot = Player::p[i].fCharge / PLAYER_CHARGEMAX;
				panel.slot->SetTextureRect(_spd->tex_x, _spd->tex_y, _spd->tex_w*fslot, _spd->tex_h);
				panel.slot->SetHotSpot(0, _spd->tex_h);
				panel.slot->SetColor(0xffffffff);
				BYTE nCharge;
				Player::p[i].GetNCharge(&nCharge);
				if (nCharge > 0)
				{
					panel.slot->SetColor(0xffffff80);
				}
				panel.slot->Render(M_GAMESQUARE_LEFT_(i)+16, M_GAMESQUARE_BOTTOM);
				panel.slotback->Render(M_GAMESQUARE_LEFT_(i), M_GAMESQUARE_BOTTOM);
				float tempx;
				for (int j=0; j<PLAYER_DEFAULTINITLIFE/2; j++)
				{
					tempx = panel.lifeindi[FDISP_LIFEINDI_FULL]->GetWidth() * (j-(PLAYER_DEFAULTINITLIFE/2)/2) + M_GAMESQUARE_CENTER_X_(i);
					if (Player::p[i].nLife > j * 2 + 1)
					{
						panel.lifeindi[FDISP_LIFEINDI_FULL]->Render(tempx, M_GAMESQUARE_TOP);
					}
					else if (Player::p[i].nLife > j * 2)
					{
						panel.lifeindi[FDISP_LIFEINDI_HALF]->Render(tempx, M_GAMESQUARE_TOP);
					}
					else
					{
						panel.lifeindi[FDISP_LIFEINDI_EMPTY]->Render(tempx, M_GAMESQUARE_TOP);
					}
				}
			}
			for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
			{
				if (info.spellpointdigitfont)
				{
					info.spellpointdigitfont->printf(M_GAMESQUARE_LEFT_(i)+2, M_GAMESQUARE_BOTTOM-11, HGETEXT_LEFT, "%02d", Player::p[i].cardlevel);
					info.spellpointdigitfont->printf(M_GAMESQUARE_RIGHT_(i)-2, M_GAMESQUARE_BOTTOM-11, HGETEXT_RIGHT, "%02d", Player::p[i].bosslevel);
				}
			}

		}
		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
		{
			panel.leftedge[i]->Render(M_GAMESQUARE_LEFT_(i)-M_GAMESQUARE_EDGE/2, M_GAMESQUARE_CENTER_Y);
			panel.rightedge[i]->Render(M_GAMESQUARE_RIGHT_(i)+M_GAMESQUARE_EDGE/2, M_GAMESQUARE_CENTER_Y);
			panel.topedge[i]->Render(M_GAMESQUARE_CENTER_X_(i), M_GAMESQUARE_TOP-M_GAMESQUARE_EDGE/2);
			panel.bottomedge[i]->Render(M_GAMESQUARE_CENTER_X_(i), M_GAMESQUARE_BOTTOM+M_GAMESQUARE_EDGE/2);
		}
	}
	if(info.asciifont)
	{
		if (Process::mp.replaymode)
		{
			info.asciifont->printf(385, 450, 0, "%.2f", Process::mp.replayFPS);
		}
#ifdef __DEBUG
		info.asciifont->printf(
			520,
			390,
			0,
			"%d\n%f\n%f\n%f",
			hge->System_GetState(HGE_FRAMECOUNTER),
			hge->Timer_GetWorstFPS(35)/M_DEFAULT_RENDERSKIP,
			hge->Timer_GetFPS()/M_DEFAULT_RENDERSKIP,
			hge->Timer_GetTime()
			);
#endif
		if (Player::CheckAble() && info.asciifont)
		{
			info.asciifont->printf(M_CLIENT_CENTER_X, M_CLIENT_BOTTOM-14, HGETEXT_CENTER, "%.2ffps", hge->Timer_GetFPS(35));
			info.asciifont->printf(M_CLIENT_CENTER_X, M_CLIENT_TOP, HGETEXT_CENTER, "%02d:%02d", time/3600, (time/60)%60);
		}
#ifdef __DEBUG
		if (Player::CheckAble())
		{
			info.asciifont->printf(8, 465, 0, "%d", time);
		}
#endif // __DEBUG
	}
}

void FrontDisplay::RenderBossInfo()
{
/*
		BYTE flag = BossInfo::flag;
		if (flag)
		{
			bossinfo.exist = false;
			infobody.effBossStore.Render();
			if(flag < BOSSINFO_COLLAPSE)
			{
	//			hge->Gfx_RenderQuad(&infobody.iqBossBlood.quad);
			}
			else if(flag & BOSSINFO_COLLAPSE)
			{
			}
		}*/
	
}

void FrontDisplay::RenderEnemyX()
{
/*
		if (BossInfo::flag)
		{
			info.enemyx->Render(Enemy::en[ENEMY_MAINBOSSINDEX].x, 472);
		}*/
	
}

bool FrontDisplay::Init()
{
	Release();

	int idx = 0;

	//For SI
	SpriteItemManager::yesIndex = SpriteItemManager::GetIndexByName(SI_CONFIRM_YES);
	SpriteItemManager::noIndex = SpriteItemManager::GetIndexByName(SI_CONFIRM_NO);
	SpriteItemManager::cancelIndex = SpriteItemManager::GetIndexByName(SI_CONFIRM_CANCEL);
	SpriteItemManager::confirmIndex = SpriteItemManager::GetIndexByName(SI_CONFIRM);

	//panel
	panel.leftedge[0] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_LEFT_0);
	panel.rightedge[0] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_RIGHT_0);
	panel.topedge[0] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_TOP_0);
	panel.bottomedge[0] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_BOTTOM_0);
	panel.leftedge[1] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_LEFT_1);
	panel.rightedge[1] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_RIGHT_1);
	panel.topedge[1] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_TOP_1);
	panel.bottomedge[1] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_BOTTOM_1);

	panel.spellpoint = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_SPELLPOINT);
	panel.spellpoint->SetHotSpot(0, 0);
	panel.combobarindex = SpriteItemManager::GetIndexByName(SI_FRONTPANEL_COMBOBAR);
	panel.combobar = SpriteItemManager::CreateSprite(panel.combobarindex);
	panel.winindi = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_WININDI);
	panel.slotindex = SpriteItemManager::GetIndexByName(SI_FRONTPANEL_SLOT);
	panel.slot = SpriteItemManager::CreateSprite(panel.slotindex);
	panel.slotback = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_SLOTBACK);
	panel.slotback->SetHotSpot(0, panel.slotback->GetHeight());
	panel.lifeindi[FDISP_LIFEINDI_EMPTY] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_LIFEINDI_EMPTY);
	panel.lifeindi[FDISP_LIFEINDI_HALF] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_LIFEINDI_HALF);
	panel.lifeindi[FDISP_LIFEINDI_FULL] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_LIFEINDI_FULL);
	for (int i=0; i<FDISP_LIFEINDIMAX; i++)
	{
		panel.lifeindi[i]->SetHotSpot(panel.lifeindi[i]->GetWidth()/2, 0);
	}

	/************************************************************************/

	idx = SpriteItemManager::GetIndexByName(SI_FACE_01);
	info.cutin = SpriteItemManager::CreateSprite(idx);
//	info.cutin = SpriteItemManager::CreateSpriteByName(SI_FACE_01);
	info.plchat_1 = SpriteItemManager::CreateSprite(idx);
	info.plchat_2 = SpriteItemManager::CreateSprite(idx);
	info.plchat_3 = SpriteItemManager::CreateSprite(idx);
	info.enchat_1 = SpriteItemManager::CreateSprite(idx);
	info.enchat_2 = SpriteItemManager::CreateSprite(idx);
	info.enchat_3 = SpriteItemManager::CreateSprite(idx);

	info.timecircle = SpriteItemManager::CreateSpriteByName(SI_BOSS_TIMECIRCLE);
	info.enemyx = SpriteItemManager::CreateSpriteByName(SI_ENEMY_X);

	info.lifebar = SpriteItemManager::CreateSpriteByName(SI_WHITE);
	info.textbox = SpriteItemManager::CreateSpriteByName(SI_FRONT_TEXT);
	info.demo = SpriteItemManager::CreateSpriteByName(SI_FRONTINFO_DEMO);
	info.loading = SpriteItemManager::CreateSpriteByName(SI_LOADING_WORD);

	//num
	idx = SpriteItemManager::GetIndexByName(SI_ASCIIBIG_0);
	for (int i=0; i<10; i++)
	{
		bignum.num[i] = SpriteItemManager::CreateSprite(idx+i);
	}
	bignum.num_add = SpriteItemManager::CreateSpriteByName(SI_ASCIIBIG_X2B);
	bignum.num_sub = SpriteItemManager::CreateSpriteByName(SI_ASCIIBIG_X2D);
	bignum.num_mul = SpriteItemManager::CreateSpriteByName(SI_ASCIIBIG_X2A);
	bignum.num_div = SpriteItemManager::CreateSpriteByName(SI_ASCIIBIG_X2F);
	bignum.num_mod = SpriteItemManager::CreateSpriteByName(SI_ASCIIBIG_X25);
	bignum.num_dot = SpriteItemManager::CreateSpriteByName(SI_ASCIIBIG_X2E);

	idx = SpriteItemManager::GetIndexByName(SI_DIGITCHARACTER_0);
	for (int i=0; i<30; i++)
	{
		itemnum.itemnum[i] = SpriteItemManager::CreateSprite(idx+i);
	}
	itemnum.bonus = SpriteItemManager::CreateSpriteByName(SI_DIGITCHARACTER_BONUS);

	idx = SpriteItemManager::GetIndexByName(SI_SPELLPOINTDIGITCHARACTER_0);
	for (int i=0; i<22; i++)
	{
		spellpointnum.spellpointnum[i] = SpriteItemManager::CreateSprite(idx+i);
	}

	idx = SpriteItemManager::GetIndexByName(SI_GAMEINFO_0);
	for (int i=0; i<10; i++)
	{
		gameinfodisplay.gameinfodisplay[i] = SpriteItemManager::CreateSprite(idx+i);
	}
	gameinfodisplay.slash = SpriteItemManager::CreateSpriteByName(SI_GAMEINFO_SLASH);
	gameinfodisplay.colon = SpriteItemManager::CreateSpriteByName(SI_GAMEINFO_COLON);
	gameinfodisplay.space = SpriteItemManager::CreateSpriteByName(SI_GAMEINFO_SPACE);
	gameinfodisplay.charge = SpriteItemManager::CreateSpriteByName(SI_GAMEINFO_CHARGE);
	gameinfodisplay.chargemax = SpriteItemManager::CreateSpriteByName(SI_GAMEINFO_CHARGEMAX);
	gameinfodisplay.gaugefilled = SpriteItemManager::CreateSpriteByName(SI_GAMEINFO_GAUGEFILLED);
	gameinfodisplay.gaugelevel = SpriteItemManager::CreateSpriteByName(SI_GAMEINFO_GAUGELEVEL);
	gameinfodisplay.caution = SpriteItemManager::CreateSpriteByName(SI_GAMEINFO_CAUTION);
	gameinfodisplay.lastlife = SpriteItemManager::CreateSpriteByName(SI_GAMEINFO_LASTLIFE);
	gameinfodisplay.lily = SpriteItemManager::CreateSpriteByName(SI_GAMEINFO_LILY);
	gameinfodisplay.spellline = SpriteItemManager::CreateSpriteByName(SI_GAMEINFO_SPELLLINE);

	//ascii

	idx = SpriteItemManager::GetIndexByName(SI_ASCIIBIG_X20);
	for (int i=0; i<FDISP_ASCII_MAX; i++)
	{
		ascii.ascii[i] = SpriteItemManager::CreateSprite(idx+i);
	}

	//font

	info.itemfont = new hgeFont();
	for (int i='0'; i<30+'0'; i++)
	{
		info.itemfont->ChangeSprite(i, itemnum.itemnum[i-'0']);
	}
	info.itemfont->ChangeSprite('b', itemnum.bonus);
	
	info.spellpointdigitfont = new hgeFont();
	for (int i='0'; i<22+'0'; i++)
	{
		info.spellpointdigitfont->ChangeSprite(i, spellpointnum.spellpointnum[i-'0']);
	}

	info.headdigitfont = new hgeFont();
	for (int i='0'; i<10+'0'; i++)
	{
		info.headdigitfont->ChangeSprite(i, gameinfodisplay.gameinfodisplay[i-'0']);
	}
	info.headdigitfont->ChangeSprite('/', gameinfodisplay.slash);
	info.headdigitfont->ChangeSprite(':', gameinfodisplay.colon);
	info.headdigitfont->ChangeSprite(' ', gameinfodisplay.space);

	info.asciifont = new hgeFont();
	for (int i=FDISP_ASCII_BEGIN; i<=FDISP_ASCII_END; i++)
	{
		info.asciifont->ChangeSprite(i, ascii.ascii[i-FDISP_ASCII_BEGIN]);
	}

	info.normalfont = hge->Font_Load(BResource::res.resdata.widefontname, 20);
	info.smallfont = hge->Font_Load(BResource::res.resdata.widefontname, 16);

	SetState(FDISP_PANEL, 0);

	return true;
}

void FrontDisplay::Release()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		SpriteItemManager::FreeSprite(&panel.leftedge[i]);
		SpriteItemManager::FreeSprite(&panel.rightedge[i]);
		SpriteItemManager::FreeSprite(&panel.topedge[i]);
		SpriteItemManager::FreeSprite(&panel.bottomedge[i]);
	}
	SpriteItemManager::FreeSprite(&panel.spellpoint);
	SpriteItemManager::FreeSprite(&panel.combobar);
	SpriteItemManager::FreeSprite(&panel.winindi);
	SpriteItemManager::FreeSprite(&panel.slot);
	SpriteItemManager::FreeSprite(&panel.slotback);
	for (int i=0; i<FDISP_LIFEINDIMAX; i++)
	{
		SpriteItemManager::FreeSprite(&panel.lifeindi[i]);
	}

	if (info.asciifont)
	{
		delete info.asciifont;
		info.asciifont = NULL;
	}
	if (info.itemfont)
	{
		delete info.itemfont;
		info.itemfont = NULL;
	}
	if (info.spellpointdigitfont)
	{
		delete info.spellpointdigitfont;
		info.spellpointdigitfont = NULL;
	}
	if (info.headdigitfont)
	{
		delete info.headdigitfont;
		info.headdigitfont = NULL;
	}
	if (info.normalfont)
	{
		hge->Font_Free(info.normalfont);
		info.normalfont = NULL;
	}
	if (info.smallfont)
	{
		hge->Font_Free(info.smallfont);
		info.smallfont = NULL;
	}
	SpriteItemManager::FreeSprite(&info.cutin);
	SpriteItemManager::FreeSprite(&info.plchat_1);
	SpriteItemManager::FreeSprite(&info.plchat_2);
	SpriteItemManager::FreeSprite(&info.plchat_3);
	SpriteItemManager::FreeSprite(&info.enchat_1);
	SpriteItemManager::FreeSprite(&info.enchat_2);
	SpriteItemManager::FreeSprite(&info.enchat_3);
	SpriteItemManager::FreeSprite(&info.timecircle);
	SpriteItemManager::FreeSprite(&info.enemyx);
	SpriteItemManager::FreeSprite(&info.lifebar);
	SpriteItemManager::FreeSprite(&info.textbox);
	SpriteItemManager::FreeSprite(&info.demo);
	SpriteItemManager::FreeSprite(&info.loading);

	for (int i=0; i<10; i++)
	{
		SpriteItemManager::FreeSprite(&bignum.num[i]);
	}
	SpriteItemManager::FreeSprite(&bignum.num_add);
	SpriteItemManager::FreeSprite(&bignum.num_sub);
	SpriteItemManager::FreeSprite(&bignum.num_mul);
	SpriteItemManager::FreeSprite(&bignum.num_div);
	SpriteItemManager::FreeSprite(&bignum.num_mod);
	SpriteItemManager::FreeSprite(&bignum.num_dot);

	for (int i=0; i<31; i++)
	{
		SpriteItemManager::FreeSprite(&itemnum.itemnum[i]);
	}

	for (int i=0; i<22; i++)
	{
		SpriteItemManager::FreeSprite(&spellpointnum.spellpointnum[i]);
	}

	for (int i=0; i<21; i++)
	{
		SpriteItemManager::FreeSprite(&gameinfodisplay.gameinfodisplay[i]);
	}

	for (int i=0; i<FDISP_ASCII_MAX; i++)
	{
		SpriteItemManager::FreeSprite(&ascii.ascii[i]);
	}
}