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
		for i=0,1 do
			local xoffset = i * 320;
			hdss.Call(
				HDSS_BGVALEX,
				{
					i, 0, SI_TitleScene
				},
				{
					xoffset, 480, -480, 320, 480, 9000, 0, 0
				},
				{
					0.008, 9000
				}
			)
			hdss.Call(
				HDSS_BGVALEX,
				{
					i, 1, SI_TitleScene
				},
				{
					xoffset, 0, -480, 320, 480, 9000, 0, 0
				},
				{
					0.008, 9000
				}
			)
			hdss.Call(
				HDSS_BGVALEX,
				{
					i, 2, SI_TitleScene
				},
				{
					xoffset, 0, -480, 480, 480, 0, 9000, 0
				},
				{
					0.008
				}
			)
			hdss.Call(
				HDSS_BGVALEX,
				{
					i, 3, SI_TitleScene
				},
				{
					xoffset+320, 0, -480, 480, 480, 0, 9000, 0
				},
				{
					0.008
				}
			)
		hdssBGCOLOR(i, 0, 0, 0, col, col);
		hdssBGCOLOR(i, 1, 0, 0, col, col);
		hdssBGCOLOR(i, 2, 0, col, col, 0);
		hdssBGCOLOR(i, 3, 0, col, col, 0);
		end
	end
	
	return true;
end