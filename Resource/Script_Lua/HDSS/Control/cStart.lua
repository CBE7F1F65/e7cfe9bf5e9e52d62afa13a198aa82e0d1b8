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
		
	end

	if math.mod(con, 160) == 1 then	
		for i=0, 1 do
			hdss.Call(
				HDSS_EB,
				{
					2, 0, 0xff, hge.Random_Int(0, 16) * 10 + 80, 280, 9000, 0.1, 0, 20, 0
				}
			)
			hdss.Call(
				HDSS_EB,
				{
					2, 1, 0xff, hge.Random_Int(0, 16) * 10 + 400, 280, 9000, 0.1, 0, 20, 0
				}
			)
		end
	end

end