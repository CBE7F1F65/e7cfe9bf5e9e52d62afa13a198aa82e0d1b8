function Scene_s00(playerindex, timer)
	
	local cenx = LGlobal_GetCenterX(playerindex);
	
	if timer == POSTAT then
		
		hdssBGOFF(playerindex, 0);
		hdssBGOFF(playerindex, 1);
		hdssBGOFF(playerindex, 2);
		hdssBGOFF(playerindex, 3);
		
	elseif timer == QUITAT then
		
		hdssBGFLAG(playerindex, 0, BG_FADEOUT, BGMT_FADE/2);
		hdssBGFLAG(playerindex, 1, BG_FADEOUT, BGMT_FADE/2);
		hdssBGFLAG(playerindex, 2, BG_FADEOUT, BGMT_FADE/2);
		hdssBGFLAG(playerindex, 3, BG_FADEOUT, BGMT_FADE/2);
		
	elseif timer == 1 then
		local col = global.ARGB(0xff, 0xffffff);
		hdss.Call(
			HDSS_BGVALEX,
			{
				playerindex, 0, SI_Scene_01_1
			},
			{
				cenx-3200, 1920, -1440, 6400, 6400, -13500, 0, 0
			},
			{
				-0.008, 0, 9000
			}
		)
		hdssBGCOLOR(playerindex, 0, col, col, 0, 0);
		
		
		local coltop = global.ARGB(0xff, 0xb4e5f9);
		hdssBGVALUE(playerindex, 1, SI_White, cenx, CenterY-20, CenterW, CenterH-40, col);
		hdssBGCOLOR(playerindex, 1, coltop, coltop, 0, 0, BLEND_ALPHAADD);
	
	elseif math.mod(timer, 32) == 0 then
		local turn = timer / 32;
		local loopturn = math.mod(turn, 4);
		for i=0, 1 do
			local bgindex = 12-loopturn + 2 + i * 4;
			local scale = 1.25;
			local posoffset = -i * 40;
			local paral = RANDT(-60, 60);
			local edgeoffset = 200;
			if loopturn == 0 then
				edgeoffset = 160;
				paral = (i*2-1) * RANDT(-45, -60);
			end
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, bgindex, SI_Scene_01_4, global.ARGB(0xff, 0xA0A0A0)
				},
				{
					cenx - loopturn * 12 + (i*2-1) * edgeoffset, -640+posoffset, -480+posoffset, 16*scale, 512*scale, 0, 0, 0, paral
				},
				{
					5.12, 5.12, 9000, true
				}
			)
			hdssBGFLAG(playerindex, bgindex, BG_LIGHTUPNORMAL, 128);
			edgeoffset = edgeoffset + 240
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, bgindex-8, RANDT(0, 1)+SI_Scene_01_2, global.ARGB(0xff, 0xA0A0A0)
				},
				{
					cenx - loopturn * 12 + (i*2-1) * edgeoffset, RANDT(-360, -200)+posoffset, -480+posoffset, 256*scale, 256*scale, 0, 0, i*18000, paral
				},
				{
					5.12, 5.12, 9000, true
				}
			)
			hdssBGFLAG(playerindex, bgindex-8, BG_LIGHTUPNORMAL, 128);
		end
	end
	
	return true;
end