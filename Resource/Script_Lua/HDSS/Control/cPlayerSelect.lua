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
	hdssBGVALUE(LConst_uibg_topcontentid, SI_TopContent_Girl, TotalCenterX, 64);
end

function CEPlayerSelect_SetSelect(selsysplayerid, x, minuskey, pluskey, okkey, initid)
	local playercontenttable, playercount = game.GetPlayerContentTable();
	for j, it in pairs(playercontenttable) do
		local i = j-1;
		local ucol = global.HSVA(j/(playercount+2), 1, 1, 1);
		local dcol = global.HSVA((j+1)/(playercount+2), 1, 1, 1);
		
		local strname = _CEPlayerSelect_TranslateName(it.name);
		
		hdss.Call(
			HDSS_SELBUILD,
			{
				selsysplayerid, i, it.siid, x + i * TotalW / 4, TotalCenterY, 0.75
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
end

function CEPlayerSelect_CloseUsed()
	hdssBGOFF(LConst_uibg_player1id, LConst_uibg_player2id);
	hdssSELCLEAR(LConst_selsys_player1id, LConst_selsys_player2id);
end

function CEPlayerSelect_ExitState(tostate)
	CEPlayerSelect_CloseUsed();
	hdssSETSTATE(tostate);
end

function CEPlayerSelect_DispatchSelect(bleft, x)
	local selsysplayerid, selsysplayerotherid, uibgid, quickkey, slowkey, leftkey, rightkey, chargekey;
	if bleft then
		uibgid = LConst_uibg_player1id;
		quickkey = KS_QUICK_0;
		slowkey = KS_SLOW_0;
		leftkey = KS_LEFT_0;
		rightkey = KS_RIGHT_0;
		chargekey = KS_CHARGE_0;
		selsysplayerid = LConst_selsys_player1id;
		selsysplayerotherid = LConst_selsys_player2id;
	else
		uibgid = LConst_uibg_player2id;
		quickkey = KS_QUICK_1;
		slowkey = KS_SLOW_1;
		leftkey = KS_LEFT_1;
		rightkey = KS_RIGHT_1;
		chargekey = KS_CHARGE_1;
		selsysplayerid = LConst_selsys_player2id;
		selsysplayerotherid = LConst_selsys_player1id;
	end
	
	local ret = 0;
	local complete, select = hdss.Get(HDSS_SELCOMPLETE, selsysplayerid);
	if complete then
		local playercontenttable, playercount = game.GetPlayerContentTable();
		hdssBGVALUE(uibgid, playercontenttable[select+1].siid, x, TotalCenterY);
		ret = 1;
	elseif hge.Input_GetDIKey(chargekey) then
		hdssSELSET(selsysplayerid);
	elseif hge.Input_GetDIKey(slowkey, DIKEY_DOWN) then
		if hge.Input_GetDIKey(leftkey, DIKEY_DOWN) then
		elseif hge.Input_GetDIKey(rightkey, DIKEY_DOWN) then
		end
	elseif hge.Input_GetDIKey(quickkey, DIKEY_DOWN) then
		local othercomplete = hdss.Get(HDSS_SELCOMPLETE, selsysplayerotherid);
		if not othercomplete then
			CEPlayerSelect_ExitState(STATE_MATCH_SELECT);
			ret = -1;
		end
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
	
	if _sel1complete == 0 then
		CEPlayerSelect_SetSelect(LConst_selsys_player1id, TotalW / 5, KS_LEFT_0, KS_RIGHT_0, KS_FIRE_0, 0);
		_sel1complete = 1;
	elseif _sel1complete == 1 then
		local ret = CEPlayerSelect_DispatchSelect(true, TotalW / 5);
		if ret > 0 then
			_sel1complete = 2;
		end
	end
	if _sel2complete == 0 then
		CEPlayerSelect_SetSelect(LConst_selsys_player2id, TotalW / 5 * 4, KS_LEFT_1, KS_RIGHT_1, KS_FIRE_1, 1);
		_sel2complete = 1;
	elseif _sel2complete == 1 then
		local ret = CEPlayerSelect_DispatchSelect(false, TotalW / 5 * 4);
		if ret > 0 then
			_sel2complete = 2;
		end
	end
		
	hdssSD(dsel1complete, _sel1complete);
	hdssSD(dsel2complete, _sel2complete);
	
	return true;

end