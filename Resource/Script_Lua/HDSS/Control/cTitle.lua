function CETitle_Init()
end

function CETitle_SetBG()
	hdssBGVALUE(0, UBGID_BGMASK, SI_White, TotalCenterX, TotalCenterY, TotalW, TotalH, global.ARGB(0xFF, 0));
	hdssBGVALUE(0, LConst_uibg_backgroundid, SI_TitleScene, TotalCenterX, TotalCenterY, TotalW, TotalH);
	hdssBGFLAG(0, UBGID_BGMASK, BG_FADEOUT);
end

function CETitle_SetupSelect(selsysid)
	local tableSelectOffset =
	{
			0, 0,
			-4, -4,
			-8, 0,
			8, 8
	}
	
	local x = 480;
	local ystart = 240;
	local yoffset = 30;
	local infox = 320;
	local infoy = 440;
	
	local _siusetable =
	{
		{SI_Title_Start,	"åùëÈ§ÚÈ_ º§∑§ﬁ§π°£"},
		{SI_Title_Replay,	"•Í•◊•Ï•§§ÚËaŸp§∑§ﬁ§π°£"},
		{SI_Title_Quit,		"§§§Ì§§§Ì§»ΩK¡À§∑§ﬁ§π°£"}
	}
	for j, it in pairs(_siusetable) do
		local i = j-1;
		local y = ystart + i * yoffset;
		hdss.Call(
			HDSS_SELBUILD,
			{
				selsysid, i, it[1], x, y
			},
			tableSelectOffset,
			{
				it[2], LConst_selsys_ucol, LConst_selsys_dcol, LConst_selsys_shadow, infox - x, infoy - y, 1, 0, LConst_selsys_align, true
			}
		)
	end
	
	hdss.Call(
		HDSS_SELSETUP,
		{
			selsysid, 3, 0, 0, KSI_UP, KSI_DOWN, KSI_FIRE
		}
	)
end

function CETitle_ExitState(tostate)
	hdssSETSTATE(tostate)
end

function CETitle_DispatchSelect(selsysid)
	local complete, select = hdss.Get(HDSS_SELCOMPLETE, selsysid);
	if complete then
		if select == 0 then
			CETitle_ExitState(STATE_MATCH_SELECT);
		elseif select == 1 then
			CETitle_ExitState(STATE_REPLAY);
		elseif select == 2 then
			hdssRETURN(PQUIT);
		end
	else
		if hdss.Get(HDSS_CHECKKEY, 0, KSI_QUICK, DIKEY_DOWN) then
			hdssSE(SE_SYSTEM_CANCEL)
			if select == 2 then
				hdssRETURN(PQUIT);
			else
				hdss.Call(
					HDSS_SELSETUP,
					{
						selsysid, 3, 2, 0
					}
				)
			end
		end
	end
end

function ControlExecute_cTitle(timer)

	local selsysid = LConst_selsys_titleid;
	
	if timer == 1 then
		CETitle_Init();
		CETitle_SetBG();
		CETitle_SetupSelect(LConst_selsys_titleid);
	end
	
	CETitle_DispatchSelect(LConst_selsys_titleid);
	
	return true;

end