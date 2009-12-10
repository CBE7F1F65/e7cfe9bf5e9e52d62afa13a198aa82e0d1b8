function CESceneSelect_Init()
end

function CESceneSelect_SetBG()
	hdssBGVALUE(0, LConst_uibg_topcontentid, SI_TopContent_Scene, TotalCenterX, 64);
end

function CESceneSelect_SetSelect(selsyssceneid)
	local scenecount = game.GetSceneContentTable();
	
	local ystart = 120;
	local yoffset = 24;

	local tableSelectOffset =
	{
		0, 0,
		-4, -4,
		-8, 0,
		8, 8
	}
	
	hdss.Call(
		HDSS_SELBUILD,
		{
			selsyssceneid, 0, -1, TotalCenterX, ystart
		},
		tableSelectOffset,
		{
			"ÒŽ¶¨¤ÎˆöËù", LConst_selsys_ucol, LConst_selsys_dcol
		}
	)
	hdss.Call(
		HDSS_SELBUILD,
		{
			selsyssceneid, 1, -1, TotalCenterX, ystart + yoffset
		},
		tableSelectOffset,
		{
			"¤É¤Ã¤«", LConst_selsys_ucol, LConst_selsys_dcol
		}
	)

	for i=0, scenecount-1 do
		
		local j = i+1;
		local ucol = global.HSVA(j/(scenecount+2), 1, 1, 1);
		local dcol = global.HSVA((j+1)/(scenecount+2), 1, 1, 1);
		local scenename = game.GetSceneContentTable(i);
		
		hdss.Call(
			HDSS_SELBUILD,
			{
				selsyssceneid, i+2, -1, TotalCenterX, ystart + (i+2) * yoffset
			},
			tableSelectOffset,
			{
				scenename, ucol, dcol
			}
		)
	end
	hdss.Call(
		HDSS_SELSETUP,
		{
			selsyssceneid, scenecount+2, 0, 0, KSI_UP, KSI_DOWN, KSI_FIRE
		},
		{
			12, ystart, yoffset
		},
		{
			SI_Select_Frame, TotalCenterX, ystart
		}
	)
end

function CESceneSelect_CloseUsed()
	hdssBGOFF(0, LConst_uibg_player1id, LConst_uibg_player2id);
	for i=0, 11 do
		hdssFREEFRONTSPRITE(i);
	end
	hdssSELCLEAR(LConst_selsys_sceneid);
end

function CESceneSelect_ExitState(tostate)
	CESceneSelect_CloseUsed();
	hdssSETSTATE(tostate);
	if tostate == STATE_START then
		hdssSTARTPREP();
	end
end

function CESceneSelect_DispatchSelect(selsyssceneid)
	local complete, select = hdss.Get(HDSS_SELCOMPLETE, selsyssceneid);
	if complete then
		CESceneSelect_ExitState(STATE_START);
	end

	if hdssCHECKKEY(0, KSI_QUICK, DIKEY_DOWN) then
		hdssSE(SE_SYSTEM_CANCEL);
		CESceneSelect_ExitState(STATE_PLAYER_SELECT);
	end
end

function ControlExecute_cSceneSelect(con)

	if con == 1 then
		CESceneSelect_Init();
		CESceneSelect_SetBG();
		CESceneSelect_SetSelect(LConst_selsys_sceneid);
	end
	
	CESceneSelect_DispatchSelect(LConst_selsys_sceneid);
		
	return true;

end