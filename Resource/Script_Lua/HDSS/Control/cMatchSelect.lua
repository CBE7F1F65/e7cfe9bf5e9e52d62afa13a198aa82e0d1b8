function ControlExecute_cMatchSelect(con)

	local selsysid = 0;
	local selsyssubid = 1;
	local dselcomplete = RESERVEBEGIN;
	local ybottomcenter = 440;
	if con == 1 then
		--Init
		hdss.Call(
			HDSS_SD,
			{
				dselcomplete, 0
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
	end
	
	local _selcomplete = hdss.Get(HDSS_D, dselcomplete);
	
	if _selcomplete == 0 then
		--SelectOver
		local complete, select = hdss.Get(HDSS_SELCOMPLETE, selsysid);
		if complete then
			if select == 0 then
				_selcomplete = 1;
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
	end
	
	if _selcomplete == 1 then
		
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
		_selcomplete = 2;
	end
	
	if _selcomplete == 2 then
		if hge.Input_GetKeyState(HGEK_CTRL) and hge.Input_GetKeyState(HGEK_V) then
			if true then
				_selcomplete = 3;
			end
		end
	end
	
	if _selcomplete > 2 then
		hdss.Call(
			HDSS_PRINT,
			{
				TotalCenterX, TotalCenterY, "101.100.120.120:2351"
			},
			{
				1.5
			}
		)
	end
	
	if _selcomplete == 3 then
		hdss.Call(
			HDSS_BGVALUE,
			{
				4, SI_MatchMode_Accessing, TotalCenterX, 200, 384, 30
			}
		)
		_selcomplete = 4;
	end
	
	hdss.Call(
		HDSS_SD,
		{
			dselcomplete, _selcomplete
		}
	)
		
	return true;

end