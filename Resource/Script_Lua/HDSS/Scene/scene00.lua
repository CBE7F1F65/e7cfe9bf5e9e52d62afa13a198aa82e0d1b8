function Scene_s00(playerindex, timer)
	
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
		local xoffset = playerindex * 320;
		hdss.Call(
			HDSS_BGVALEX,
			{
				playerindex, 0, SI_Scene_01_1
			},
			{
				xoffset-360, 480, 0, 720, 960, -13500, 0, 0
			}
		)
		hdssBGCOLOR(playerindex, 0, col, col, 0, 0);
	end
	
	return true;
end