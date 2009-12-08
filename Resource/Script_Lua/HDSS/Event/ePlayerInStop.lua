function ePlayerInStop(playerindex, bSpell, spellPlayerID, oplayerID, stoptimer, stopmaxtime, spellClass, spellLevel)

	local x;
	if playerindex == 0 then
		x = CenterBossX_0;
	else
		x = CenterBossX_1;
	end
	
	if bSpell then
		if stoptimer == 1 then
			hdssSEOFF();
			hdssSE(SE_PLAYER_SPELLCUTIN);
		end
		
		if stoptimer < stopmaxtime-1 then
			local vscale = 1.0;
			local alpha = 0xff;
			if stoptimer < stopmaxtime/4 then
				local intervalue = stoptimer / (stopmaxtime/4);
				vscale = hdssINTER(4.0, 1.0, intervalue);
				alpha = hdssINTER(0, 0xff, intervalue);
			end
			
			local siid = SI_PlayerSpellCutIn_01_LL + spellPlayerID*4;
			if playerindex == 1 then
				siid = siid + 2;
			end
			local col = global.ARGB(alpha, 0xffffff);
			
			x = x - 16;
			hdssFRONTSPRITE(LConst_game_FrontSprite_SpellCutInLeftID, siid, x, CenterBossY, 0, 1, vscale, col);
			siid = siid + 1;
			x = x + 144;
			hdssFRONTSPRITE(LConst_game_FrontSprite_SpellCutInRightID, siid, x, CenterBossY, 0, 1, vscale, col);
		else
			hdssFREEFRONTSPRITE(LConst_game_FrontSprite_SpellCutInLeftID);
			hdssFREEFRONTSPRITE(LConst_game_FrontSprite_SpellCutInRightID);
		end
	else
		if stoptimer < stopmaxtime-1 then
			local col = global.ARGB(0xff, 0xfffff);
			if math.mod(stoptimer, 8) < 4 then
				col = global.ARGB(0xff, 0xff8080);
			end
			hdssFRONTSPRITE(LConst_game_FrontSprite_WarningID, SI_GameInfo_Warning, x, CenterY-40, 0, 1, 0, col);
			hdssFRONTSPRITE(LConst_game_FrontSprite_SpellClassID, SI_GameInfo_ClassFairy+spellClass-2, x, CenterY, 0, 1, 0, col);
		else
			hdssFREEFRONTSPRITE(LConst_game_FrontSprite_WarningID);
			hdssFADEOUTFRONTSPRITE(LConst_game_FrontSprite_SpellClassID, 32);
		end
	end
end