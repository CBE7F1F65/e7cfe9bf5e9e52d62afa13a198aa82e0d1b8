function ControlExecute_cMatchSelect(con)

	local selsysid = 0;
	local selsyssubid = 1;
	local dselcomplete = RESERVEBEGIN;
	local dipx = RESERVEBEGIN + 1;
	local dipport = RESERVEBEGIN + 2;
	local dlatency = RESERVEBEGIN + 3;
	
	local ybottomcenter = 440;
	if con == 1 then
		--Init
		hdss.Call(
			HDSS_SD,
			{
				dselcomplete, 0
			}
		)
		hdss.Call(
			HDSS_SDf,
			{
				dipx, 0
			}
		)
		hdss.Call(
			HDSS_SD,
			{
				dipport, 0
			}
		)
		hdss.Call(
			HDSS_SD,
			{
				dlatency, 0
			}
		)
		--Mask
		hdss.Call(
			HDSS_BGVALUE,
			{
				BGMASK, SI_Null, TotalCenterX, TotalCenterY, TotalW, TotalH, global.ARGB(0xFF, 0)
			}
		)
		--BG
		hdss.Call(
			HDSS_BGVALUE, 
			{
				0, SI_SelectScene, TotalCenterX, TotalCenterY, TotalW, TotalH
			}
		)
		--TopContent
		hdss.Call(
			HDSS_BGVALUE, 
			{
				1, SI_TopContent_MatchMode, TotalCenterX, 96
			}
		)
		--Fade
		hdss.Call(
			HDSS_BGFLAG,
			{
				BGMASK, BG_FADEOUT
			}
		)
		
	end
	
	local _selcomplete = hdss.Get(HDSS_D, dselcomplete);
	local _ipx = hdss.Get(HDSS_D, dipx);
	local _ipport = hdss.Get(HDSS_D, dipport);
	local _latency = hdss.Get(HDSS_D, dlatency);
	
	if _selcomplete == 0 then
		--Close
		hdss.Call(
			HDSS_BGOFF,
			{
				2
			}
		)
		hdss.Call(
			HDSS_BGOFF,
			{
				4
			}
		)
		--Clear
		hdss.Call(
			HDSS_SELCLEAR,
			{
				selsysid
			}
		)
		hdss.Call(
			HDSS_SELCLEAR,
			{
				selsyssubid
			}
		)
		
		--Select
		local x = TotalCenterX;
		local yoffset = 64;
		local ystart = TotalCenterY - yoffset;
		
		local _siusetable =
		{
			SI_MatchSelect_P2P,
			SI_MatchSelect_P2C,
			SI_MatchSelect_C2P
		}
		for j, it in pairs(_siusetable) do
			local i = j-1;
			local y = ystart + i * yoffset;
			hdss.Call(
				HDSS_SELBUILD,
				{
					selsysid, i, it, x, y
				},
				{
					0, 0,
					-4, -4,
					0, ybottomcenter - y,
					8, 8
				}
			)
		end
		
		hdss.Call(
			HDSS_SELSET,
			{
				selsysid, 3, 0, KS_UP, KS_DOWN, KS_FIRE
			}
		)
		_selcomplete = 1;
		
	elseif _selcomplete == 1 then
		--SelectOver
		local complete, select = hdss.Get(HDSS_SELCOMPLETE, selsysid);
		if complete then
			if select == 0 then
				_selcomplete = 2;
			elseif select == 1 then
				hdss.Call(
					HDSS_SETSTATE,
					{
						STATE_PLAYER_SELECT
					}
				)
			elseif select == 2 then
				hdss.Call(
					HDSS_SETSTATE,
					{
						STATE_PLAYER_SELECT
					}
				)
			end
		end
	
	elseif _selcomplete == 2 then
		
		hdss.Call(
			HDSS_BGVALUE, 
			{
				2, SI_MatchSelect_P2P, TotalCenterX, ybottomcenter
			}
		)
		
		hdss.Call(
			HDSS_BGVALUE, 
			{
				4, SI_MatchMode_Waiting, TotalCenterX, 200, 384, 60
			}
		)
		_selcomplete = 3;
	
	elseif _selcomplete == 3 then
		if hge.Input_GetDIKey(KS_QUICK, DIKEY_DOWN) then
			hdss.Call(
				HDSS_SE,
				{
					SE_SYSTEM_CANCEL
				}
			)
			_selcomplete = 0;
		elseif hge.Input_GetKeyState(HGEK_CTRL) and hge.Input_GetKeyState(HGEK_V) then
			local strclipboard = global.GetClipBoard();
			
			local ipd0, ipd1, ipd2, ipd3, ipport;
			local stristart = 1;
			local striend = 1;
			stristart, striend = string.find(strclipboard, "%d+", stristart);
			if stristart ~= nil then
				ipd0 = string.sub(strclipboard, stristart, striend);
				stristart = striend + 1;
				stristart, striend = string.find(strclipboard, "%d+", stristart);
				if stristart ~= nil then
					ipd1 = string.sub(strclipboard, stristart, striend);
					stristart = striend + 1;
					stristart, striend = string.find(strclipboard, "%d+", stristart);
					if stristart ~= nil then
						ipd2 = string.sub(strclipboard, stristart, striend);
						stristart = striend + 1;
						stristart, striend = string.find(strclipboard, "%d+", stristart);
						if stristart ~= nil then
							ipd3 = string.sub(strclipboard, stristart, striend);
							stristart = striend + 1;
							stristart, striend = string.find(strclipboard, "%d+", stristart);
							if stristart ~= nil then
								ipport = string.sub(strclipboard, stristart, striend);
							end
								
							if ipport == nil then
								ipport = M_DEFAULTIPPORT;
							end
							ipd0 = tonumber(ipd0);
							ipd1 = tonumber(ipd1);
							ipd2 = tonumber(ipd2);
							ipd3 = tonumber(ipd3);
							ipport = tonumber(ipport);
						
							if ipd0 >= 1 and ipd0 <= 0xFF and
								ipd1 >= 0 and ipd1 <= 0xFF and
								ipd2 >= 0 and ipd2 <= 0xFF and
								ipd3 >= 0 and ipd3 <= 0xFF then
								
								if ipport >= 0 and ipport <= 0xFFFF then
									_ipx = global.ARGB(ipd0, ipd1, ipd2, ipd3);
									_ipport = ipport;
									game.SetLastIP(_ipx, _ipport);
									_selcomplete = 4;
								end
									
							end
						end
					end
				end
			end
			
		elseif hge.Input_GetDIKey(KS_ENTER, DIKEY_DOWN) then
			_ipx, _ipport = game.GetLastIP();
			local ipd0, ipd1, ipd2, ipd3 = global.GetARGB(_ipx);
			if ipd0 ~= 0 then
				_selcomplete = 4;
			end
		end
		
	elseif _selcomplete == 4 then
		hdss.Call(
			HDSS_BGVALUE,
			{
				4, SI_MatchMode_Accessing, TotalCenterX, 200, 384, 30
			}
		)
		hdss.Call(
			HDSS_SE,
			{
				SE_SYSTEM_OK
			}
		)
		_selcomplete = 5;
	
	elseif _selcomplete == 5 then
		_latency = game.AccessIP();
		if _latency > 0 then
			_selcomplete = 6;
		end
	
	elseif _selcomplete == 6 then
		hdss.Call(
			HDSS_BGVALUE, 
			{
				4, SI_MatchMode_Latency, TotalCenterX, 200, 384, 30
			}
		)
		hdss.Call(
			HDSS_SELCLEAR,
			{
				selsyssubid
			}
		)
		local x = TotalCenterX;
		local ystart = 320;
		local yoffset = 20;
		for i=0, 8 do
			hdss.Call(
				HDSS_SELBUILD,
				{
					selsyssubid, i, -1, x, ystart + i * yoffset
				},
				{
					0, 0,
					-4, -4,
					-8, 0,
					8, 8
				},
				{
					string.format("Latency:%d", i+1)
				}
			)
		end
		hdss.Call(
			HDSS_SELSET,
			{
				selsyssubid, 9, _latency-1, KS_UP, KS_DOWN, KS_FIRE
			},
			{
				1, ystart, yoffset, _latency-1
			}
		)
		hdss.Call(
			HDSS_SE,
			{
				SE_SYSTEM_OK
			}
		)
		_selcomplete = 7;
	
	elseif _selcomplete == 7 then
		if hge.Input_GetDIKey(KS_QUICK, DIKEY_DOWN) then
			hdss.Call(
				HDSS_SELCLEAR,
				{
					selsyssubid
				}
			)
			_selcomplete = 2;
		hdss.Call(
			HDSS_SE,
			{
				SE_SYSTEM_CANCEL
			}
		)
		end
		
		--SelectOver
		local complete, select = hdss.Get(HDSS_SELCOMPLETE, selsyssubid);
		if complete then
			_latency = select + 1;
			hdss.Call(
				HDSS_SETSTATE,
				{
					STATE_PLAYER_SELECT
				}
			)
		end
	end
	
	-- IP
	if _selcomplete > 3 then
		local ipd0, ipd1, ipd2, ipd3 = global.GetARGB(_ipx);
		local strip = string.format("%d.%d.%d.%d:%d", ipd0, ipd1, ipd2, ipd3, _ipport);
		hdss.Call(
			HDSS_PRINT,
			{
				TotalCenterX, TotalCenterY, strip
			},
			{
				1.5
			}
		)
	end
	hdss.Call(
		HDSS_SD,
		{
			dselcomplete, _selcomplete
		}
	)
	hdss.Call(
		HDSS_SDf,
		{
			dipx, _ipx
		}
	)
	hdss.Call(
		HDSS_SD,
		{
			dipport, _ipport
		}
	)
	hdss.Call(
		HDSS_SD,
		{
			dlatency, _latency
		}
	)
		
	return true;

end