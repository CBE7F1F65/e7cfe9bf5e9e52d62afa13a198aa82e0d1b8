function ControlExecute_cStart(con)
	if con == 1 then
		local col = global.ARGB(0xff, 0xffffff);
		for i=0,1 do
			local xoffset = i * 320;
			hdss.Call(
				HDSS_BGVALEX,
				{
					i*UBGID_RIGHTIDBEGIN, SI_TitleScene
				},
				{
					xoffset, 480, -480, 320, 480, 9000, 0, 0
				},
				{
					0.008, 9000
				}
			)
			hdss.Call(
				HDSS_BGVALEX,
				{
					i*UBGID_RIGHTIDBEGIN+1, SI_TitleScene
				},
				{
					xoffset, 0, -480, 320, 480, 9000, 0, 0
				},
				{
					0.008, 9000
				}
			)
			hdss.Call(
				HDSS_BGVALEX,
				{
					i*UBGID_RIGHTIDBEGIN+2, SI_TitleScene
				},
				{
					xoffset, 0, -480, 480, 480, 0, 9000, 0
				},
				{
					0.008
				}
			)
			hdss.Call(
				HDSS_BGVALEX,
				{
					i*UBGID_RIGHTIDBEGIN+3, SI_TitleScene
				},
				{
					xoffset+320, 0, -480, 480, 480, 0, 9000, 0
				},
				{
					0.008
				}
			)
		hdssBGCOLOR(i*UBGID_RIGHTIDBEGIN, 0, 0, col, col);
		hdssBGCOLOR(i*UBGID_RIGHTIDBEGIN+1, 0, 0, col, col);
		hdssBGCOLOR(i*UBGID_RIGHTIDBEGIN+2, 0, col, col, 0);
		hdssBGCOLOR(i*UBGID_RIGHTIDBEGIN+3, 0, col, col, 0);
		end
		
--		hdssBGVALUE(0, SI_BG_01_1, TotalCenterX, TotalCenterY, TotalW, TotalH)
	end
		
end