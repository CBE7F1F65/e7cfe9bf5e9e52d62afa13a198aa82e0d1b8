function ControlExecute_cTitle(con)

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
				0, SI_TitleScene, TotalCenterX, TotalCenterY, TotalW, TotalH
			}
		)
		hdss.Call(
			HDSS_BGFLAG,
			{
				BGMASK, BG_FADEOUT
			}
		)
		
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
			HDSS_SELSET,
			{
				selsysid, 3, 0, KS_UP, KS_DOWN, KS_FIRE
			}
		)
	end
	
	local complete, select = hdss.Get(HDSS_SELCOMPLETE, selsysid);
	if complete then
		if select == 0 then
			hdss.Call(
				HDSS_SETSTATE,
				{
					STATE_MATCH_SELECT
				}
			)
		elseif select == 1 then
			hdss.Call(
				HDSS_SETSTATE,
				{
					STATE_REPLAY
				}
			)
		elseif select == 2 then
			hdss.Call(
				HDSS_RETURN,
				{
					PQUIT
				}
			)
		end
	else
		if hge.Input_GetDIKey(KS_QUICK, DIKEY_DOWN) then
			hdss.Call(
				HDSS_SE,
				{
					SE_SYSTEM_CANCEL
				}
			)
			if select == 2 then
				hdss.Call(
					HDSS_RETURN,
					{
						PQUIT
					}
				)
			else
				hdss.Call(
					HDSS_SELSET,
					{
						selsysid, 3, 2
					}
				)
			end
		end
	end
	
	return true;

end