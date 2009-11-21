#include "processPrep.h"

void Process::_Render(BYTE renderflag/* =M_RENDER_NULL */)
{
	BGLayer::RenderBG();
	if(renderflag != M_RENDER_NULL)
	{
		FrontDisplay::fdisp.RenderBossTimeCircle();
		Ghost::RenderAll();
		Enemy::RenderAll();
		PlayerBullet::RenderAll();
		Player::RenderAll();
		Effectsys::RenderAll();
		Beam::RenderAll();
		Bullet::RenderAll();
		FrontDisplay::fdisp.RenderBossInfo();
		Item::RenderAll();
		Chat::chatitem.Render();
	}
	BGLayer::RenderFG();
	SelectSystem::RenderAll();
	SpriteItemManager::RenderFrontSprite();
	FrontDisplay::fdisp.RenderPostPrint();
}

void Process::_RenderTar()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		if (rendertar[i])
		{
			if (sprendertar[i])
			{
				delete sprendertar[i];
			}
			sprendertar[i] = new hgeSprite(hge->Target_GetTexture(rendertar[i]), M_GAMESQUARE_LEFT_(i), M_GAMESQUARE_TOP, M_GAMESQUARE_WIDTH, M_GAMESQUARE_HEIGHT);
			sprendertar[i]->Render(M_GAMESQUARE_CENTER_X_(i), M_GAMESQUARE_CENTER_Y);
		}
	}
}

int Process::render()
{
	bool isingame = IsInGame();
	if (isingame)
	{
		hge->Gfx_BeginScene(rendertar[0]);
		hge->Gfx_Clear(0x00000000);
		Export::clientSetMatrix(worldx, worldy, worldz, M_RENDER_LEFT);
		_Render(M_RENDER_LEFT);
		hge->Gfx_EndScene();
		hge->Gfx_BeginScene(rendertar[1]);
		hge->Gfx_Clear(0x00000000);
		Export::clientSetMatrix(worldx, worldy, worldz, M_RENDER_RIGHT);
		_Render(M_RENDER_RIGHT);
		hge->Gfx_EndScene();
	}

	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0x00000000);
	Export::clientSetMatrix();
	if (state == STATE_INIT)
	{
		return renderInit();
	}
	//BGLayer

	if (!isingame)
	{
		_Render();
	}
	else
	{
		_RenderTar();
	}
	FrontDisplay::fdisp.PanelDisplay();

	if(isingame)
	{
		FrontDisplay::fdisp.RenderEnemyX();
	}
	hge->Gfx_EndScene();
	return PGO;
}

int Process::renderInit()
{
	if (texInit)
	{
		hgeQuad quad;
		quad.blend = BLEND_DEFAULT;
		quad.tex = texInit;
		quad.v[0].col = quad.v[1].col = quad.v[2].col = quad.v[3].col = 0xffffffff;
		quad.v[0].tx = 0;	quad.v[0].ty = 0;
		quad.v[1].tx = 1;	quad.v[1].ty = 0;
		quad.v[2].tx = 1;	quad.v[2].ty = 1;
		quad.v[3].tx = 0;	quad.v[3].ty = 1;
		quad.v[0].x = M_CLIENT_LEFT;	quad.v[0].y = M_CLIENT_TOP;	quad.v[0].z = 0;
		quad.v[1].x = M_CLIENT_RIGHT;	quad.v[1].y = M_CLIENT_TOP;	quad.v[1].z = 0;
		quad.v[2].x = M_CLIENT_RIGHT;	quad.v[2].y = M_CLIENT_BOTTOM;	quad.v[2].z = 0;
		quad.v[3].x = M_CLIENT_LEFT;	quad.v[3].y = M_CLIENT_BOTTOM;	quad.v[3].z = 0;
		hge->Gfx_RenderQuad(&quad);
	}
	return PGO;
}