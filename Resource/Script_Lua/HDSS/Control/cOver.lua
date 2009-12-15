function CEOver_Init()
end

function CEOver_SetBG()
end

function CEOver_SetSelect(selsysoverid, select)
	
	local ystart = TotalCenterY - 36;
	local yoffset = 36;

	local tableSelectOffset =
	{
		0, 0,
		-4, -4,
		-8, 0,
		8, 8
	}
	
	for i=0, 4 do
		local flag = SEL_NULL;
		local y = ystart + yoffset * i;
		if i == 4 then
			flag = SEL_NONACTIVE;
			y = ystart - yoffset * 1.5;
		end
		hdss.Call(
			HDSS_SELBUILD,
			{
				selsysoverid, i, SI_Pause_ResetGame+i, TotalCenterX, y, 1, 0, flag
			},
			tableSelectOffset
		)
	end
	hdss.Call(
		HDSS_SELSETUP,
		{
			selsysoverid, 4, 1, 0, KSI_UP, KSI_DOWN, KSI_FIRE
		}
	)
end

function CEOver_CloseUsed()
	hdssSELCLEAR(LConst_selsys_overid);
end

function CEOver_ExitState(tostate)
	CEOver_CloseUsed();
	hdssSETSTATE(tostate);
	if tostate == STATE_START then
		hdssSTARTPREP();
	end
end

function CEOver_DispatchSelect(selsysoverid, tostate)
	local complete, select = hdss.Get(HDSS_SELCOMPLETE, selsysoverid);
	if complete then
		return select;
	end
	return -1;
end

function ControlExecute_cOver(con)

	local dselcomplete = RESERVEBEGIN;
	local dselselect = RESERVEBEGIN + 1;
	
	if con == 1 then
		CEOver_Init();
		hdssSD(dselcomplete, 0);
		CEOver_SetBG();
	else
		local _selcomplete = hdss.Get(HDSS_D, dselcomplete);
		if _selcomplete == 0 then
			CEOver_SetSelect(LConst_selsys_overid, _selselect);
			_selcomplete = 1;
		elseif _selcomplete == 1 then
			local ret = CEOver_DispatchSelect(LConst_selsys_overid, con-0xff00);
			if ret >= 0 then
				if ret == 0 then
					CEOver_ExitState(STATE_START);
				elseif ret == 1 then
					CEOver_ExitState(STATE_PLAYER_SELECT);
				elseif ret == 2 then
					CEOver_ExitState(STATE_TITLE);
				else
					hdssSAVEREPLAY();
					CEOver_ExitState(STATE_TITLE);
				end
			end
		end
		hdssSD(dselcomplete, _selcomplete);
	end
		
	return true;

end