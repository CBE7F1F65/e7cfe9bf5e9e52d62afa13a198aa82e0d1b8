function ControlExecute(name, con)

	if name == STATE_TITLE then
		local selsysid = 0;
		if con == 1 then
			hdss.Call(
				HDSS_BGVALUE, 
				{
					0, SI_TitleScene, TotalCenterX, TotalCenterY, TotalW, TotalH
				}
			)
			
			local tableSelectOffset =
			{
					0, 0,
					-4, -4,
					-8, 0,
					8, 8
			}
			local ucol = global.ARGB(0xFF, 0xFFFFFF);
			local dcol = global.ARGB(0xFF, 0xFF3333);
			local shadow = 0.4
			local align = HGETEXT_CENTER + HGETEXT_MIDDLE;
			
			local x = 480;
			local ystart = 240;
			local yoffset = 30;
			local infox = 320;
			local infoy = 400;
			
			local _siusetable =
			{
				{SI_Title_Start,	"åùëÈ§ÚÈ_ º§∑§ﬁ§π°£"},
				{SI_Title_Replay,	"•Í•◊•Ï•§§ÚËaŸp§∑§ﬁ§π°£"},
				{SI_Title_Quit,		"§§§Ì§§§Ì§»ΩK¡À§∑§ﬁ§π°£"}
			}
			for j=1, 3 do
				local i = j-1;
				local y = ystart + i * yoffset;
				hdss.Call(
					HDSS_SELBUILD,
					{
						selsysid, i, _siusetable[j][1], x, y
					},
					tableSelectOffset,
					{
						_siusetable[j][2], ucol, dcol, shadow, infox - x, infoy - y, 1, 0, align, true
					}
				)
			end
			
			hdss.Call(
				HDSS_SELSET,
				{
					selsysid, 3, 0, KS_UP, KS_DOWN, KS_FIRE, KS_SPECIAL
				}
			)
		end
		local complete, select = hdss.Get(HDSS_SELCOMPLETE, selsysid);
		if complete then
			hdss.Call(
				HDSS_SETTIME,
				{
					0
				}
			)
		end
	end
	
	return true;

end