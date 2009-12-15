function CEPause_Init()
end

function CEPause_SetBG()
	hdssBGFLAG(0, UFGID_FGPAUSE, FG_PAUSEIN, FGMT_PAUSE);
end

function CEPause_SetSelect(selsyspauseid, select)
	
	local ystart = TotalCenterY - 48;
	local yoffset = 36;

	local tableSelectOffset =
	{
		0, 0,
		-4, -4,
		-8, 0,
		8, 8
	}
	
	for i=0, 5 do
		local flag = SEL_NULL;
		local y = ystart + yoffset * i;
		if i == 5 then
			flag = SEL_NONACTIVE;
			y = ystart - yoffset * 1.5;
		end
		hdss.Call(
			HDSS_SELBUILD,
			{
				selsyspauseid, i, SI_Pause_Start+i, TotalCenterX, y, 1, 0, flag
			},
			tableSelectOffset
		)
	end
	hdss.Call(
		HDSS_SELSETUP,
		{
			selsyspauseid, 5, select, 0, KSI_UP, KSI_DOWN, KSI_FIRE
		}
	)
end

function CEPause_CloseUsed()
	hdssBGFLAG(0, UFGID_FGPAUSE, FG_PAUSEOUT, FGMT_PAUSE);
	hdssSELCLEAR(LConst_selsys_pauseid);
	hdssSELCLEAR(LConst_selsys_pauseconfirmid);
end

function CEPause_ExitState(tostate, bPrep)
	CEPause_CloseUsed();
	local time = 0;
	if bPrep == nil then
		bPrep = false;
	end
	if not bPrep and tostate == STATE_START then
		time = -1;
	end
	hdssSETSTATE(tostate, time);
	if bPrep then
		hdssSTARTPREP();
	end
end

function CEPause_DispatchSelect(selsyspauseid, tostate)
	local complete, select = hdss.Get(HDSS_SELCOMPLETE, selsyspauseid);
	if complete then
		if select == 0 then
			CEPause_ExitState(tostate);
		end
		return select;
	end
	
	if hdss.Get(HDSS_CHECKKEY, 0, KSI_QUICK, DIKEY_DOWN) or hdss.Get(HDSS_CHECKKEY, 0, KSI_PAUSE, DIKEY_DOWN) then
		hdssSE(SE_SYSTEM_CANCEL);
		CEPause_ExitState(tostate);
	end
	return 0;
end

function CEPause_SetConfirmSelect(selsyspauseconfirmid)
	
	local ystart = TotalCenterY;
	local yoffset = 36;

	local tableSelectOffset =
	{
		0, 0,
		-4, -4,
		-8, 0,
		8, 8
	}
	
	for i=0, 2 do
		local flag = SEL_NULL;
		local y = ystart + yoffset * i;
		if i == 2 then
			flag = SEL_NONACTIVE;
			y = ystart - yoffset * 1.5;
		end
		hdss.Call(
			HDSS_SELBUILD,
			{
				selsyspauseconfirmid, i, SI_Confirm_Yes+i, TotalCenterX, y, 1, 0, flag
			},
			tableSelectOffset
		)
	end
	hdss.Call(
		HDSS_SELSETUP,
		{
			selsyspauseconfirmid, 2, 1, 0, KSI_UP, KSI_DOWN, KSI_FIRE
		}
	)
end

function CEPause_DispatchConfirmSelect(selsyspauseconfirmid)
	local complete, select = hdss.Get(HDSS_SELCOMPLETE, selsyspauseconfirmid);
	if complete then
		if select == 0 then
			return 1;
		else
			return -1;
		end
	end
	
	if hdss.Get(HDSS_CHECKKEY, 0, KSI_QUICK, DIKEY_DOWN) then
		hdssSE(SE_SYSTEM_CANCEL);
		hdssSELCLEAR(selsyspauseconfirmid);
		return -1;
	end
	return 0;
end

function ControlExecute_cPause(con)

	local dselcomplete = RESERVEBEGIN;
	local dselselect = RESERVEBEGIN + 1;
	
	if con == 0 then
		CEPause_Init();
		hdssSD(dselcomplete, 0);
		hdssSD(dselselect, 0);
		CEPause_SetBG();
	else
		local _selcomplete = hdss.Get(HDSS_D, dselcomplete);
		local _selselect = hdss.Get(HDSS_D, dselselect);
		if _selcomplete == 0 then
			CEPause_SetSelect(LConst_selsys_pauseid, _selselect);
			_selcomplete = 1;
		elseif _selcomplete == 1 then
			_selselect = CEPause_DispatchSelect(LConst_selsys_pauseid, con-0xff00);
			if _selselect > 0 then
				_selcomplete = 2;
			end
		elseif _selcomplete == 2 then
			CEPause_SetConfirmSelect(LConst_selsys_pauseconfirmid);
			_selcomplete = 3;
		elseif _selcomplete == 3 then
			local ret = CEPause_DispatchConfirmSelect(LConst_selsys_pauseconfirmid);
			if ret > 0 then
				if _selselect == 1 then
					CEPause_ExitState(STATE_START, true);
				elseif _selselect == 2 then
					CEPause_ExitState(STATE_PLAYER_SELECT);
				elseif _selselect == 3 then
					CEPause_ExitState(STATE_TITLE);
				else
					hdssSAVEREPLAY(true, true);
					CEPause_ExitState(STATE_TITLE);
				end
			elseif ret < 0 then
				_selcomplete = 0;
			end
		end
		hdssSD(dselcomplete, _selcomplete);
		hdssSD(dselselect, _selselect);
	end
		
	return true;

end