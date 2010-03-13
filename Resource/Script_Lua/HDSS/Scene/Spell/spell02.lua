function Spell_s02(playerindex, timer)
		
	if timer == POSTAT then
		
		hdssBGOFF(playerindex, LConst_gamebg_spellid_1, LConst_gamebg_spellid_2);
		
	elseif timer == QUITAT then
		
		for i=0, 1 do
			hdssBGFLAG(playerindex, LConst_gamebg_spellid_1+i, BG_FADEOUT, BGMT_FADE/2);
		end
		
	elseif timer == 1 then
		local cenx = helper_GetCenterX(playerindex);
		local col = global.ARGB(0, 0xffffff);
		for i=0, 1 do
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, LConst_gamebg_spellid_1+i, SI_Spell_02_1+i, col
				},
				{
					cenx-TotalH*0.6, TotalCenterY-TotalH*0.6, 0, TotalH*1.2, TotalH*1.2
				},
				{
					0.9, 0, (i*2-1)*9000, true, true
				}
			)
			
			hdssBGFLAG(playerindex, LConst_gamebg_spellid_1+i, BG_FADEIN, BGMT_FADE);
		end
	end
	
	return true;
end