function ControlExecute_cMatchSelect(con)

	local selsysid = 0;
	if con == 1 then
		hdss.Call(
			HDSS_BGVALUE,
			{
				BGMASK, SI_Null, TotalCenterX, TotalCenterY, TotalW, TotalH, global.ARGB(0xFF, 0)
			}
		)
		hdss.Call(
			HDSS_BGVALUE, 
			{
				0, SI_SelectScene, TotalCenterX, TotalCenterY, TotalW, TotalH
			}
		)
		hdss.Call(
			HDSS_BGVALUE, 
			{
				1, SI_TopContent_MatchMode, TotalCenterX, 96
			}
		)
		hdss.Call(
			HDSS_BGFLAG,
			{
				BGMASK, BG_FADEOUT
			}
		)
		
		local x = TotalCenterX;
		local yoffset = 64;
		local ystart = TotalCenterY - yoffset;
		local yenter = 440;
		
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
					0, yenter - y,
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
	
	local complete, select = hdss.Get(HDSS_SELCOMPLETE, selsysid);
		
	return true;

end