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
	ZeroMemory(&normalnum, sizeof(ftNumSet));
	ZeroMemory(&itemnum, sizeof(ftItemNumSet));
	ZeroMemory(&spellpointnum, sizeof(ftSpellPointNumSet));
	ZeroMemory(&gameinfodisplay, sizeof(ftGameInfoDisplaySet));
	ZeroMemory(&ascii, sizeof(ftAscIISet));
	ZeroMemory(&asciismall, sizeof(ftAscIISet));
	ZeroMemory(&first, sizeof(ftFirstSet));
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
			it->font->RenderEx(it->x, it->y, it->align, it->str, it->scale, it->properation, it->rotation, it->tracking, it->spacing);
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
	case FDISP_NEXTSTAGE:
		nextstagecount = state;
		break;
	case FDISP_FULLPOWER:
		fullpowercount = state;
		break;
	case FDISP_HISCORE:
		hiscorecount = state;
		break;
	case FDISP_EXTEND:
		extendcount = state;
		break;
	}
}

void FrontDisplay::RenderHeadInfo()
{
	float yoffset = 24.0f;
	float ybottomoffset = 32.0f;
	float yoffsetadd = 22.0f;
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		float px = Player::p[i].x;
		float py = Player::p[i].y;
		DWORD color = 0xffffffff;
		BYTE alpha = 0xff;
		if (Player::p[i].bCharge)
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
			if (Player::p[i].chargetimer < 16)
			{
				alpha = Player::p[i].chargetimer * 16;
			}
			Player::p[i].GetNCharge(&ncharge, &nchargemax);
			if (Player::p[i].chargetimer % 16 < 8)
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
		if (gameinfodisplay.lastlifecountdown[i])
		{
			float tyoffset = yoffset;
			yoffset += yoffsetadd;
			if (py-tyoffset < M_GAMESQUARE_TOP)
			{
				tyoffset = -ybottomoffset;
				ybottomoffset += yoffsetadd;
			}
			alpha = 0xff;
			gameinfodisplay.lastlifecountdown[i]--;
			if (gameinfodisplay.lastlifecountdown[i] < 16)
			{
				alpha = gameinfodisplay.lastlifecountdown[i] * 16;
			}
			color = (alpha<<24)+0xffffff;
			gameinfodisplay.caution->SetColor(color);
			gameinfodisplay.caution->Render(px, py-tyoffset-8);
			gameinfodisplay.lastlife->SetColor(color);
			gameinfodisplay.lastlife->Render(px, py-tyoffset);
		}
		if (gameinfodisplay.gaugefilledcountdown[i])
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
			Player::p[i].GetNCharge(&ncharge, &nchargemax);
			gameinfodisplay.gaugefilledcountdown[i]--;
			alpha = 0xff;
			if (gameinfodisplay.gaugefilledcountdown[i] < 16)
			{
				alpha = gameinfodisplay.gaugefilledcountdown[i] * 16;
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
}

void FrontDisplay::RenderPanel()
{
	if (nextstagecount)
	{
		nextstagecount--;
		RenderNextStage();
	}
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
				char buffer[M_STRITOAMAX];
				sprintf(buffer, "%d%c", Player::p[i].nComboHit, '0'+(usered?21:20));
				if (usered)
				{
					for (int j=0; j<strlen(buffer)-1; j++)
					{
						buffer[j] += 10;
					}
				}
				info.spellpointdigitfont->printf(spellpointx[i]+36, M_GAMESQUARE_TOP+16, HGETEXT_RIGHT, "%s", buffer);
				info.spellpointdigitfont->printf(spellpointx[i]+36, M_GAMESQUARE_TOP+16, HGETEXT_LEFT, "%06d", Player::p[i].nSpellPoint);

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
		if (mp.replaymode)
		{
			info.asciifont->printf(385, 450, 0, "%.2f", mp.replayFPS);
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

void FrontDisplay::RenderNextStage()
{
	/*
	if (nextstagecount)
	{
		info.stageclear->Render(M_ACTIVECLIENT_CENTER_X, 160);
		if (bval)
		{
			info.nextstage->Render(M_ACTIVECLIENT_CENTER_X, 280);
		}
		info.bossfont->SetColor(0xffffffff);
		info.bossfont->printf(M_ACTIVECLIENT_CENTER_X, 220, HGETEXT_CENTER|HGETEXT_MIDDLE, "%d", llval);
	}
	*/
}

void FrontDisplay::BossAction()
{
	BYTE flag = BossInfo::flag;
	WORD timer = bossinfo.timer;
	bool bSpell = bossinfo.isSpell();
	if(flag >= BOSSINFO_COLLAPSE)
	{
		infobody.effBossStore.Stop();
		infobody.effBossCollapse.action();
		infobody.effBossItem.action();
	}
	infobody.effBossStore.action();

	if (flag & BOSSINFO_UP)
	{
		if (timer == 1)
		{
			DWORD col1, col2;
			if(bSpell)
			{
				col1 = 0xce7f0000;
				col2 = 0xceff0000;

				SpriteItemManager::ptFace(Enemy::en[ENEMY_MAINBOSSINDEX].faceindex, info.cutin);
				info.cutin->SetColor(0x60ffffff);

				infobody.effBossUp.Stop(true);
				infobody.effBossUp.MoveTo(Enemy::en[ENEMY_MAINBOSSINDEX].x, Enemy::en[ENEMY_MAINBOSSINDEX].y, 0, true);
				infobody.effBossUp.Fire();
			}
			else
			{
				col1 = 0xcececebd;
				col2 = 0xceffffbd;
			}
			// TODO:
			infobody.iqBossBlood.valueSet(0, M_GAMESQUARE_CENTER_X_(0), 32,
				60, 30, col1,
				60, 30, col1,
				60, 34, col2,
				60, 34, col2);
		}
		if((infobody.iqBossBlood.quad.v[1].x-60) / 320.0f < Enemy::en[ENEMY_MAINBOSSINDEX].life / Enemy::en[ENEMY_MAINBOSSINDEX].maxlife)
		{
			infobody.iqBossBlood.quad.v[1].x += 2;
			infobody.iqBossBlood.quad.v[2].x += 2;
		}
		else
		{
			infobody.iqBossBlood.quad.v[1].x = Enemy::en[ENEMY_MAINBOSSINDEX].life / Enemy::en[ENEMY_MAINBOSSINDEX].maxlife * 320.0f + 60;
			infobody.iqBossBlood.quad.v[2].x = Enemy::en[ENEMY_MAINBOSSINDEX].life / Enemy::en[ENEMY_MAINBOSSINDEX].maxlife * 320.0f + 60;
		}
		//
		if(bSpell)
		{
		/*
			float _tx = en[ENEMY_MAINBOSSINDEX].x;
			float _ty = en[ENEMY_MAINBOSSINDEX].y;
			_tx += (160 - timer) * cost(timer * 400);
			_ty += (160 - timer) * sint(timer * 400);
			infobody.effBossUp.MoveTo(_tx, _ty);
			*/
			infobody.effBossUp.MoveTo(Enemy::en[ENEMY_MAINBOSSINDEX].x, Enemy::en[ENEMY_MAINBOSSINDEX].y);
			infobody.effBossUp.action();
			if(timer == 90)
			{
				SE::push(SE_BOSS_UP, Enemy::en[ENEMY_MAINBOSSINDEX].x);
				infobody.effBossUp.Stop();
			}
		}
		//
		if (timer > 128)
		{
			info.cutin->SetColor((((160-timer)*3)<<24)+0xffffff);
		}
	}
	else if(flag & BOSSINFO_COLLAPSE)
	{
		if (timer == 1)
		{
			SE::push(SE_BOSS_DEAD, Enemy::en[ENEMY_MAINBOSSINDEX].x);
			infobody.effBossCollapse.Stop(true);
			infobody.effBossCollapse.MoveTo(Enemy::en[ENEMY_MAINBOSSINDEX].x, Enemy::en[ENEMY_MAINBOSSINDEX].y, 0, true);
			infobody.effBossCollapse.Fire();
			if (bSpell)
			{
//				BGLayer::ubg[UBGID_BGMASK].flag = BG_REDOUT;
				BGLayer::ubg[UBGID_BGMASK].SetFlag(BG_REDOUT, BGMT_OUT);
			}
			mp.SetShake(1);
		}
		else if (timer == 75)
		{
			if (bSpell)
			{
				if (!BossInfo::failed)
				{
					SE::push(SE_BOSS_BONUS);
				}
			}
		}
		else if(timer == 120)
		{
			infobody.effBossCollapse.Stop();
		}
	}
	else if(flag & BOSSINFO_TIMEOVER)
	{
		if(timer == 1)
		{
			if (bSpell)
			{
//				BGLayer::ubg[UBGID_BGMASK].flag = BG_WHITEFLASH;
				BGLayer::ubg[UBGID_BGMASK].SetFlag(BG_WHITEFLASH, BGMT_FLASH);
			}
		}
	}
	else
	{
		if(Enemy::en[ENEMY_MAINBOSSINDEX].life > 0)
		{
			infobody.iqBossBlood.quad.v[1].x = Enemy::en[ENEMY_MAINBOSSINDEX].life / Enemy::en[ENEMY_MAINBOSSINDEX].maxlife * 320.0f + 60;
			infobody.iqBossBlood.quad.v[2].x = Enemy::en[ENEMY_MAINBOSSINDEX].life / Enemy::en[ENEMY_MAINBOSSINDEX].maxlife * 320.0f + 60;
		}
		else
		{
			infobody.iqBossBlood.quad.v[1].x = 60;
			infobody.iqBossBlood.quad.v[2].x = 60;
		}
	}
	if(Player::p[0].y < 100)
	{
		infobody.iqBossBlood.quad.v[0].col &= (0x7fffffff);
		infobody.iqBossBlood.quad.v[1].col &= (0x7fffffff);
		infobody.iqBossBlood.quad.v[2].col &= (0x7fffffff);
		infobody.iqBossBlood.quad.v[3].col &= (0x7fffffff);

		info.bossspellline->SetColor(0x40ffffff);
		info.spellbonustext->SetColor(0x40ffffff);
		info.spellhistorytext->SetColor(0x40ffffff);
		info.spellfailedtext->SetColor(0x40ffffff);

		info.bossfont->SetColor(0x40ffffff);
		info.bossasciifont->SetColor(0x40ffffff);
	}
	else
	{
		infobody.iqBossBlood.quad.v[0].col |= (0x80<<24);
		infobody.iqBossBlood.quad.v[1].col |= (0x80<<24);
		infobody.iqBossBlood.quad.v[2].col |= (0x80<<24);
		infobody.iqBossBlood.quad.v[3].col |= (0x80<<24);

		info.bossspellline->SetColor(0xffffffff);
		info.spellbonustext->SetColor(0xffffffff);
		info.spellhistorytext->SetColor(0xffffffff);
		info.spellfailedtext->SetColor(0xffffffff);

		info.bossfont->SetColor(0xffffffff);
		info.bossasciifont->SetColor(0xffffffff);
	}

	if(flag >= BOSSINFO_COLLAPSE)
	{
		if(timer == 1)
		{
			infobody.effBossItem.Stop(true);
			infobody.effBossItem.MoveTo(Enemy::en[ENEMY_MAINBOSSINDEX].x, Enemy::en[ENEMY_MAINBOSSINDEX].y, 0, true);
			infobody.effBossItem.Fire();
		}
		else if(timer == 90)
		{
			infobody.effBossItem.Stop();
		}
	}
}

void FrontDisplay::BossMoveItemEffect(float x, float y)
{
	infobody.effBossItem.MoveTo(x, y);
}

void FrontDisplay::RenderBossInfo()
{
	BYTE flag = BossInfo::flag;
	if (flag)
	{
		bossinfo.exist = false;
		WORD timer = bossinfo.timer;
		bool bSpell = bossinfo.isSpell();
		bool failed = BossInfo::failed;
	//	exist = false;
		infobody.effBossStore.Render();
		if(flag < BOSSINFO_COLLAPSE)
		{
			info.bossfont->SetScale(1.2f);
			info.bossfont->printf(50, 20, HGETEXT_RIGHT|HGETEXT_MIDDLE, "%d", bossinfo.remain);

			int ttime = bossinfo.limit-timer/60;
			if (ttime < 4)
				info.bossfont->SetColor(0xffff0000);
			else if (ttime < 11)
				info.bossfont->SetColor(0xffff00ff);
			else if (ttime > 99)
			{
				ttime = 99;
			}
			info.bossfont->printf(400, 20, HGETEXT_CENTER|HGETEXT_MIDDLE, "%d", ttime);

			info.bossasciifont->printf(60, 20, HGETEXT_LEFT, "%s", bossinfo.enemyename);

			if(bSpell)
			{
				float yt;
				if(Enemy::bossflag[ENEMY_MAINBOSSINDEX] & BOSS_SPELLUP)
					info.cutin->Render(312, Enemy::spelluptimer[ENEMY_MAINBOSSINDEX]*2.4f);
				if(timer < 30)
				{
					yt = 225;
				}
				else if(timer < 120)
				{
					yt = (120-timer)*2+45;
				}
				else
				{
					yt = 45;
				}

				info.bossspellline->Render(296, yt);

				int tlenth = strlen(bossinfo.spellname);
				float spellnamew = tlenth*8;
				DWORD spellnamealpha = 0xff000000;
				if(Player::p[0].y < 100)
					spellnamealpha = 0x40000000;
				bossinfo.fsspellname.SetColor(spellnamealpha+0xffffff, spellnamealpha+0xffffffff, spellnamealpha+0xff0000, spellnamealpha+0xff0000);
				bossinfo.fsspellname.Render(400-spellnamew, yt-5);

				if (flag & BOSSINFO_UP)
				{
					infobody.effBossUp.Render();
				}

				/*
				info.spellbonustext->Render(240, yt+20);
				info.spellhistorytext->Render(345, yt+20);
				if (!failed)
				{
					info.bossasciifont->printf(320, yt+16, HGETEXT_RIGHT, "%09d", bonus);
				}
				else
				{
					info.spellfailedtext->Render(280, yt+20);
				}
				info.bossasciifont->printf(410, yt+16, HGETEXT_RIGHT, "%03d/%03d", bossinfo.get, bossinfo.meet);
				*/
			}
			hge->Gfx_RenderQuad(&infobody.iqBossBlood.quad);
		}
		else if(flag & BOSSINFO_COLLAPSE)
		{
			/*
			if(bSpell && !failed)
			{
				infobody.effBossCollapse.Render();
				infobody.effBossItem.Render();
				info.getbonus->Render(M_ACTIVECLIENT_CENTER_X, 80);
				info.bossfont->SetColor((((timer*8)%0x100)<<8)+0xffff007f);
			}
			else
			{
				if (failed)
				{
					info.failed->Render(M_ACTIVECLIENT_CENTER_X, 80);
					info.bossfont->SetColor((((timer*8)%0x100)<<16)+0xff00ffff);
				}
			}
			info.bossfont->printf(M_ACTIVECLIENT_CENTER_X, 120, HGETEXT_CENTER|HGETEXT_MIDDLE, "%d", bonus);
			*/
		}
	}
}

void FrontDisplay::RenderBossTimeCircle()
{
	BYTE flag = BossInfo::flag;
	if (flag && bossinfo.isSpell())
	{
		WORD timer = bossinfo.timer;
		BYTE limit = bossinfo.limit;
		if (flag < BOSSINFO_COLLAPSE)
		{
			float scale;
			if (timer >= 88)
			{
				if (timer < 120)
				{
					scale = (timer-88) * 0.1f;
				}
				else
				{
					scale = (timer-60*limit)*0.8f / (30-15*limit);
				}
				info.timecircle->RenderEx(Enemy::en[ENEMY_MAINBOSSINDEX].x, Enemy::en[ENEMY_MAINBOSSINDEX].y, timer/15.0f, scale);
			}
		}
	}
}

void FrontDisplay::RenderEnemyX()
{
	if (BossInfo::flag)
	{
		info.enemyx->Render(Enemy::en[ENEMY_MAINBOSSINDEX].x, 472);
	}
}

void FrontDisplay::ItemInfoDisplay(infoFont * item)
{
	if(item->yellow)
		info.itemfont->SetColor(0xafffff00);
	else
		info.itemfont->SetColor(0xafffffff);
	info.itemfont->printf(item->x, item->y-10-item->timer, HGETEXT_CENTER, "%s", item->cScore);
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
	SpriteItemManager::digituiIndex = SpriteItemManager::GetIndexByName(SI_DIGITBIG_0);

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

	//info
	// TODO:
	infobody.effBossCollapse.valueSet(EFF_BI_COLLAPSE, M_RENDER_LEFT, 0, 0);
	infobody.effBossCollapse.Stop();
	infobody.effBossItem.valueSet(EFF_BI_ITEM, M_RENDER_LEFT, 0, 0);
	infobody.effBossItem.Stop();
	infobody.effBossUp.valueSet(EFF_BI_BOSSUP, M_RENDER_LEFT, 0, 0);
	infobody.effBossUp.Stop();
	infobody.effBossStore.valueSet(EFF_BI_BOSSSTORE, M_RENDER_LEFT, 0, 0);
	infobody.effBossStore.Stop();
	/************************************************************************/
	infobody.effLoading.valueSet(0, M_RENDER_NULL, 0, 0);
	infobody.effLoading.Stop();
	/************************************************************************/

	idx = SpriteItemManager::GetIndexByName(SI_FACE_01);
	info.cutin = SpriteItemManager::CreateSprite(idx);
	SpriteItemManager::faceIndexEnemy = idx;
	SpriteItemManager::faceIndexPlayer = SpriteItemManager::GetIndexByName(SI_PLAYERFACE_01);
//	info.cutin = SpriteItemManager::CreateSpriteByName(SI_FACE_01);
	info.plchat_1 = SpriteItemManager::CreateSprite(idx);
	info.plchat_2 = SpriteItemManager::CreateSprite(idx);
	info.plchat_3 = SpriteItemManager::CreateSprite(idx);
	info.enchat_1 = SpriteItemManager::CreateSprite(idx);
	info.enchat_2 = SpriteItemManager::CreateSprite(idx);
	info.enchat_3 = SpriteItemManager::CreateSprite(idx);

	idx = SpriteItemManager::GetIndexByName(SI_NAMECARD_01);
	info.namecard = SpriteItemManager::CreateSprite(idx);
	SpriteItemManager::nameIndexEnemy = idx;
	SpriteItemManager::nameIndexPlayer = SpriteItemManager::GetIndexByName(SI_PLAYERNAMECARD_01);
//	info.namecard = SpriteItemManager::CreateSpriteByName(SI_NAMECARD_01);
	info.bossspellline = SpriteItemManager::CreateSpriteByName(SI_SPELLLINE_BOSS);
	info.playerspellline = SpriteItemManager::CreateSpriteByName(SI_SPELLLINE_PLAYER);
	info.spellbonustext = SpriteItemManager::CreateSpriteByName(SI_SPELLLINE_BONUS);
	info.spellhistorytext = SpriteItemManager::CreateSpriteByName(SI_SPELLLINE_HISTORY);
	info.spellfailedtext = SpriteItemManager::CreateSpriteByName(SI_SPELLLINE_FAILED);
	info.timecircle = SpriteItemManager::CreateSpriteByName(SI_BOSS_TIMECIRCLE);
	info.enemyx = SpriteItemManager::CreateSpriteByName(SI_ENEMY_X);

	info.lifebar = SpriteItemManager::CreateSpriteByName(SI_NULL);
	info.getbonus = SpriteItemManager::CreateSpriteByName(SI_FRONTINFO_GETBONUS);
	info.failed = SpriteItemManager::CreateSpriteByName(SI_FRONTINFO_FAILED);
	info.stageclear = SpriteItemManager::CreateSpriteByName(SI_STAGE_CLEAR);
	info.nextstage = SpriteItemManager::CreateSpriteByName(SI_FRONTINFO_NEXTSTAGE);
	info.fullpower = SpriteItemManager::CreateSpriteByName(SI_FRONTINFO_FULLPOWER);
	info.hiscoreget = SpriteItemManager::CreateSpriteByName(SI_FRONTINFO_HISCOREGET);
	info.extend = SpriteItemManager::CreateSpriteByName(SI_FRONTINFO_EXTEND);
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

	idx = SpriteItemManager::GetIndexByName(SI_DIGITNORMAL_0);
	for (int i=0; i<10; i++)
	{
		normalnum.num[i] = SpriteItemManager::CreateSprite(idx+i);
	}
	normalnum.num_div = SpriteItemManager::CreateSpriteByName(SI_DIGITNORMAL_DIV);
	normalnum.num_dot = SpriteItemManager::CreateSpriteByName(SI_DIGITNORMAL_DOT);

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
	idx = SpriteItemManager::GetIndexByName(SI_ASCIISMALL_X20);
	for (int i=0; i<FDISP_ASCIISMALL_MAX; i++)
	{
		asciismall.ascii[i] = SpriteItemManager::CreateSprite(idx+i);
	}

	//first
	first.face = SpriteItemManager::CreateSpriteByName(SI_FACE_01);
	first.namecard = SpriteItemManager::CreateSpriteByName(SI_NAMECARD_01);


	//font
	info.normaldigitfont = new hgeFont();
	for (int i='0'; i<='9'; i++)
	{
		info.normaldigitfont->ChangeSprite(i, normalnum.num[i-'0']);
	}
	info.normaldigitfont->ChangeSprite('/', normalnum.num_div);
	info.normaldigitfont->ChangeSprite('.', normalnum.num_dot);
	info.normaldigitfont->ChangeSprite(' ', ascii.space);

	info.bossfont = new hgeFont();
	for (int i='0'; i<='9'; i++)
	{
		info.bossfont->ChangeSprite(i, normalnum.num[i-'0']);
	}
	info.bossfont->ChangeSprite('/', normalnum.num_div);
	info.bossfont->ChangeSprite('.', normalnum.num_dot);
	info.bossfont->ChangeSprite(' ', ascii.space);

	info.itemfont = new hgeFont();
	for (int i='0'; i<30+'0'; i++)
	{
		info.itemfont->ChangeSprite(i, itemnum.itemnum[i-'0']);
	}
	info.itemfont->SetScale(1.2f);
	
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
	info.bossasciifont = new hgeFont();
	for (int i=FDISP_ASCII_BEGIN; i<=FDISP_ASCIISMALL_END; i++)
	{
		info.bossasciifont->ChangeSprite(i, asciismall.ascii[i-FDISP_ASCII_BEGIN]);
	}

	info.normalfont = hge->Font_Load(res.resdata.widefontname, 20);
	info.smallfont = hge->Font_Load(res.resdata.widefontname, 16);

	SetState(FDISP_PANEL, 0);
	SetState(FDISP_NEXTSTAGE, 0);
	SetState(FDISP_FULLPOWER, 0);
	SetState(FDISP_HISCORE, 0);
	SetState(FDISP_EXTEND, 0);

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

	if (info.bossfont)
	{
		delete info.bossfont;
		info.bossfont = NULL;
	}
	if (info.normaldigitfont)
	{
		delete info.normaldigitfont;
		info.normaldigitfont = NULL;
	}
	if (info.asciifont)
	{
		delete info.asciifont;
		info.asciifont = NULL;
	}
	if (info.bossasciifont)
	{
		delete info.bossasciifont;
		info.bossasciifont = NULL;
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
	SpriteItemManager::FreeSprite(&info.namecard);
	SpriteItemManager::FreeSprite(&info.plchat_1);
	SpriteItemManager::FreeSprite(&info.plchat_2);
	SpriteItemManager::FreeSprite(&info.plchat_3);
	SpriteItemManager::FreeSprite(&info.enchat_1);
	SpriteItemManager::FreeSprite(&info.enchat_2);
	SpriteItemManager::FreeSprite(&info.enchat_3);
	SpriteItemManager::FreeSprite(&info.bossspellline);
	SpriteItemManager::FreeSprite(&info.playerspellline);
	SpriteItemManager::FreeSprite(&info.spellbonustext);
	SpriteItemManager::FreeSprite(&info.spellhistorytext);
	SpriteItemManager::FreeSprite(&info.spellfailedtext);
	SpriteItemManager::FreeSprite(&info.timecircle);
	SpriteItemManager::FreeSprite(&info.enemyx);
	SpriteItemManager::FreeSprite(&info.lifebar);
	SpriteItemManager::FreeSprite(&info.getbonus);
	SpriteItemManager::FreeSprite(&info.failed);
	SpriteItemManager::FreeSprite(&info.stageclear);
	SpriteItemManager::FreeSprite(&info.nextstage);
	SpriteItemManager::FreeSprite(&info.fullpower);
	SpriteItemManager::FreeSprite(&info.hiscoreget);
	SpriteItemManager::FreeSprite(&info.extend);
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

	for (int i=0; i<10; i++)
	{
		SpriteItemManager::FreeSprite(&normalnum.num[i]);
	}
	SpriteItemManager::FreeSprite(&normalnum.num_div);
	SpriteItemManager::FreeSprite(&normalnum.num_dot);

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
	for (int i=0; i<FDISP_ASCIISMALL_MAX; i++)
	{
		SpriteItemManager::FreeSprite(&asciismall.ascii[i]);
	}

	SpriteItemManager::FreeSprite(&first.face);
	SpriteItemManager::FreeSprite(&first.namecard);

}