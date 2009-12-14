function CEReplay_Init()
end

function CEReplay_SetBG()
	--Mask
	hdssBGVALUE(0, UBGID_BGMASK, SI_White, TotalCenterX, TotalCenterY, TotalW, TotalH, global.ARGB(0xFF, 0));
	--BG
	hdssBGVALUE(0, LConst_uibg_backgroundid, SI_ReplayScene, TotalCenterX, TotalCenterY, TotalW, TotalH);
	--Fade
	hdssBGFLAG(0, UBGID_BGMASK, BG_FADEOUT);
end

function CEReplay_CloseUsed()
end

function CEReplay_ExitState(tostate)
	CEReplay_CloseUsed();
	hdssSETSTATE(tostate);
end

function ControlExecute_cReplay(con)
	if con == 1 then
		CEReplay_Init();
		CEReplay_SetBG();
	end
end