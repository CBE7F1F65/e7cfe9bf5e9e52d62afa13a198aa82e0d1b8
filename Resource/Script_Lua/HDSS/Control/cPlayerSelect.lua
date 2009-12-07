function CEPlayerSelect_Init()
end

function _CEPlayerSelect_TranslateName(name)
	local retname = "";
	local tsubstr;
	for i=1, string.len(name), 2 do
		tsubstr = string.sub(name, i, i+1);
		if tsubstr == "©`" then
			tsubstr = "Ø­"
		end
		retname = retname..tsubstr.."\n";
	end
	return retname;
end

function CEPlayerSelect_SetBG()
	hdssBGVALUE(0, LConst_uibg_topcontentid, SI_TopContent_Girl, TotalCenterX, 64);
end

function _CEPlayerSelect_GetKeys(bleft)
	if bleft then
		return KS_UP_0, KS_DOWN_0, KS_LEFT_0, KS_RIGHT_0, KS_FIRE_0, KS_QUICK_0, KS_SLOW_0, KS_CHARGE_0;
	else
		return KS_UP_1, KS_DOWN_1, KS_LEFT_1, KS_RIGHT_1, KS_FIRE_1, KS_QUICK_1, KS_SLOW_1, KS_CHARGE_1;
		
	end
end

function _CEPlayerSelect_GetValues(bleft)
	local nowID, lastID;
	if bleft then
		nowID, lastID = hdss.Get(HDSS_CHARA, 0);
		return LConst_selsys_player1id, LConst_selsys_player2id, LConst_uibg_player1id, lastID, PUSHID_UIUSE_0
	else
		nowID, lastID = hdss.Get(HDSS_CHARA, 1);
		return LConst_selsys_player2id, LConst_selsys_player1id, LConst_uibg_player2id, lastID, PUSHID_UIUSE_1
	end
end

function _CEPlayerSelect_GetPIndex(bleft)
	if bleft then
		return 0;
	else
		return 1;
	end
end

function _CEPlayerSelect_SetInitLife(bleft, x, flag)
	local pindex = _CEPlayerSelect_GetPIndex(bleft);
	
	local y = 440;
	
	local fspindexstart = pindex * 6;
	if flag == nil or flag == 0 then
		hdssFRONTSPRITE(fspindexstart, SI_InitialLife_Content, x, y);
		for i=1, 5 do
			hdssFRONTSPRITE(fspindexstart + i, SI_InitialLife_Full, (i-5) * 16 + x, y + 16);
		end
		hdssSETPINITLIFE(pindex, 10);
	else
		local nowlife, nowinitlife = hdss.Get(HDSS_PLIFE, pindex);
		if flag < 0 then
			if nowinitlife <= 1 then
				return;
			end
			hdssSETPINITLIFE(pindex, nowinitlife-1);
			if math.mod(nowinitlife, 2) == 0 then
				hdssFRONTSPRITE(fspindexstart + nowinitlife / 2, SI_InitialLife_Half);
			else
				hdssFRONTSPRITE(fspindexstart + (nowinitlife+1) / 2, SI_InitialLife_Empty);
			end
		else
			if nowinitlife >= 10 then
				return;
			end
			hdssSETPINITLIFE(pindex, nowinitlife+1);
			if math.mod(nowinitlife, 2) == 0 then
				hdssFRONTSPRITE(fspindexstart + nowinitlife / 2 + 1, SI_InitialLife_Half);
			else
				hdssFRONTSPRITE(fspindexstart + (nowinitlife+1) / 2, SI_InitialLife_Full);
			end
		end
	end
end

function CEPlayerSelect_SetSelect(bleft, x)
	local selsysplayerid, selsysotherplayerid, uibgid, initid, pushkeyid = _CEPlayerSelect_GetValues(bleft);
	local minuskey, pluskey, leftkey, rightkey, okkey, quickkey, slowkey, chargekey = _CEPlayerSelect_GetKeys(bleft);
	
	hdssBGOFF(0, uibgid);
	_CEPlayerSelect_SetInitLife(bleft, x);
	
	local playercount = game.GetPlayerContentTable();
	for i=0, playercount-1 do
		local j = i+1;
		local ucol = global.HSVA(j/(playercount+2), 1, 1, 1);
		local dcol = global.HSVA((j+1)/(playercount+2), 1, 1, 1);
		
		local siid, name = game.GetPlayerContentTable(i);
		local strname = _CEPlayerSelect_TranslateName(name);
		
		hdss.Call(
			HDSS_SELBUILD,
			{
				selsysplayerid, i, siid, x + i * TotalW / 4, TotalCenterY, 0.75
			},
			{
				0, 0,
				-4, -4,
				0, 0,
				8, 8
			},
			{
				strname, ucol, dcol, LConst_selsys_shadow, (TotalCenterX-x)/2, -80, 1.2
			}
		)
	end
	hdss.Call(
		HDSS_SELSETUP,
		{
			selsysplayerid, playercount, initid, minuskey, pluskey, okkey
		},
		{
			1, x, TotalW / 4, initid, 0
		}
	)
	hdssSETPUSHEVENT(pushkeyid, chargekey, PUSHKEY_KEYNULL, PUSHKEY_KEYNULL, PUSHKEY_KEYNULL, 8, 0);
end

function CEPlayerSelect_CloseUsed(bcloseall)
	if bcloseall == nil or bcloseall then
		hdssBGOFF(0, LConst_uibg_player1id, LConst_uibg_player2id);
		for i=0, 11 do
			hdssFREEFRONTSPRITE(i);
		end
	end
	hdssSELCLEAR(LConst_selsys_player1id, LConst_selsys_player2id);
end

function CEPlayerSelect_ExitState(tostate, bcloseall)
	CEPlayerSelect_CloseUsed(bcloseall);
	hdssSETSTATE(tostate);
end

function CEPlayerSelect_DispatchSelect(bleft, x, bothercomplete)
	local selsysplayerid, selsysotherplayerid, uibgid, initid, pushkeyid = _CEPlayerSelect_GetValues(bleft);
	local upkey, downkey, leftkey, rightkey, okkey, quickkey, slowkey, chargekey = _CEPlayerSelect_GetKeys(bleft);
	
	hdssUPDATEPUSHEVENT(pushkeyid);
	
	local ret = 0;
	local complete, select = hdss.Get(HDSS_SELCOMPLETE, selsysplayerid);
	
	if complete then
		
		local siid = game.GetPlayerContentTable(select);
		hdssBGVALUE(0, uibgid, siid, x, TotalCenterY, -0.75, -0.75, global.ARGB(0xff, 0));
		local pindex = _CEPlayerSelect_GetPIndex(bleft);
		hdssSETCHARA(pindex, select);		
		ret = 1;
		
	elseif hge.Input_GetDIKey(chargekey, DIKEY_DOWN) then
		
		hdssSELSET(selsysplayerid);
		
	elseif hge.Input_GetDIKey(slowkey) then
		
		if hge.Input_GetDIKey(leftkey, DIKEY_DOWN) then
			_CEPlayerSelect_SetInitLife(bleft, x, -1);
		elseif hge.Input_GetDIKey(rightkey, DIKEY_DOWN) then
			_CEPlayerSelect_SetInitLife(bleft, x, 1);
		end
		
	elseif hge.Input_GetDIKey(quickkey, DIKEY_DOWN) then
		
		if not bothercomplete then
			hdssSE(SE_SYSTEM_CANCEL);
			CEPlayerSelect_ExitState(STATE_MATCH_SELECT);
			ret = -1;
		end
		
	end
	return ret;
end

function _CEPlayerSelect_SyncInput(bleftcomplete, brightcomplete)
	if hge.Input_GetDIKey(KS_LEFT_0) then
		hge.Input_SetDIKey(KS_UP_0);
	end
	if hge.Input_GetDIKey(KS_RIGHT_0) then
		hge.Input_SetDIKey(KS_DOWN_0);
	end
	if hge.Input_GetDIKey(KS_LEFT_1) then
		hge.Input_SetDIKey(KS_UP_1);
	end
	if hge.Input_GetDIKey(KS_RIGHT_1) then
		hge.Input_SetDIKey(KS_DOWN_1);
	end
	if hge.Input_GetDIKey(KS_SLOW_0) then
		hge.Input_SetDIKey(KS_UP_0, false);
		hge.Input_SetDIKey(KS_DOWN_0, false);
	end
	if hge.Input_GetDIKey(KS_SLOW_1) then
		hge.Input_SetDIKey(KS_UP_1, false);
		hge.Input_SetDIKey(KS_DOWN_1, false);
	end
	
	local matchmode = game.GetMatchMode();
	if matchmode == MatchMode_P2C and bleftcomplete or
		matchmode == MatchMode_C2P and not brightcomplete then
		if hge.Input_GetDIKey(KS_UP_0) then
			hge.Input_SetDIKey(KS_UP_1);
		end
		if hge.Input_GetDIKey(KS_DOWN_0) then
			hge.Input_SetDIKey(KS_DOWN_1);
		end
		if hge.Input_GetDIKey(KS_LEFT_0) then
			hge.Input_SetDIKey(KS_LEFT_1);
		end
		if hge.Input_GetDIKey(KS_RIGHT_0) then
			hge.Input_SetDIKey(KS_RIGHT_1);
		end
		if hge.Input_GetDIKey(KS_FIRE_0) then
			hge.Input_SetDIKey(KS_FIRE_1);
		end
		if hge.Input_GetDIKey(KS_SLOW_0) then
			hge.Input_SetDIKey(KS_SLOW_1);
		end
		if hge.Input_GetDIKey(KS_CHARGE_0) then
			hge.Input_SetDIKey(KS_CHARGE_1);
		end
		if matchmode == MatchMode_C2P then
			hge.Input_SetDIKey(KS_UP_0, false);
			hge.Input_SetDIKey(KS_DOWN_0, false);
			hge.Input_SetDIKey(KS_LEFT_0, false);
			hge.Input_SetDIKey(KS_RIGHT_0, false);
			hge.Input_SetDIKey(KS_FIRE_0, false);
			hge.Input_SetDIKey(KS_SLOW_0, false);
			hge.Input_SetDIKey(KS_CHARGE_0, false);
		end
	elseif matchmode == MatchMode_C2P then
		if hge.Input_GetDIKey(KS_QUICK_0) then
			hge.Input_SetDIKey(KS_QUICK_1);
		end
	end
end

function CEPlayerSelect_DispatchAfterSelect(quickkey)
	local ret = 0;
	if hge.Input_GetDIKey(quickkey, DIKEY_DOWN) then
		ret = -1;
	end
	return ret;
end

function ControlExecute_cPlayerSelect(con)
	
	local dsel1complete = RESERVEBEGIN;
	local dsel2complete = RESERVEBEGIN + 1;
	
	if con == 1 then
		CEPlayerSelect_Init();
		hdssSD(dsel1complete, 0);
		hdssSD(dsel2complete, 0);
		CEPlayerSelect_SetBG()
	end
	
	local _sel1complete = hdss.Get(HDSS_D, dsel1complete);
	local _sel2complete = hdss.Get(HDSS_D, dsel2complete);
	
	if _sel1complete == 0 and _sel2complete == 0 then
		CEPlayerSelect_CloseUsed();
	end
	
	_CEPlayerSelect_SyncInput(_sel1complete == 3, _sel2complete == 3);
	
	if _sel1complete == 0 then
		CEPlayerSelect_SetSelect(true, TotalW / 5);
		_sel1complete = 1;
	elseif _sel1complete == 1 then
		local ret = CEPlayerSelect_DispatchSelect(true, TotalW / 5, _sel2complete==3);
		if ret > 0 then
			_sel1complete = 2;
		end
	elseif _sel1complete == 2 then
		_sel1complete = 3;
	elseif _sel1complete == 3 then
		local ret = CEPlayerSelect_DispatchAfterSelect(KS_QUICK_0);
		if ret < 0 then
			_sel1complete = 0;
		end
	end
	if _sel2complete == 0 then
		CEPlayerSelect_SetSelect(false, TotalW / 5 * 4);
		_sel2complete = 1;
	elseif _sel2complete == 1 then
		local ret = CEPlayerSelect_DispatchSelect(false, TotalW / 5 * 4, _sel1complete==3);
		if ret > 0 then
			_sel2complete = 2;
		end
	elseif _sel2complete == 2 then
		_sel2complete = 3;
	elseif _sel2complete == 3 then
		local ret = CEPlayerSelect_DispatchAfterSelect(KS_QUICK_1);
		if ret < 0 then
			_sel2complete = 0;
		end
	end
	
	if _sel1complete == 3 and _sel2complete == 3 then
		CEPlayerSelect_ExitState(STATE_SCENE_SELECT, false);
	end
		
	hdssSD(dsel1complete, _sel1complete);
	hdssSD(dsel2complete, _sel2complete);
	
	return true;

end