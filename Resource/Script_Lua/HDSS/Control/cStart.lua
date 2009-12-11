function ControlExecute_cStart(con)
	if con == 1 then
		local col = global.ARGB(0xff, 0xffffff);
		for i=0,1 do
			local xoffset = i * 320;
			hdss.Call(
				HDSS_BGVALEX,
				{
					i, 0, SI_TitleScene
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
					i, 1, SI_TitleScene
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
					i, 2, SI_TitleScene
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
					i, 3, SI_TitleScene
				},
				{
					xoffset+320, 0, -480, 480, 480, 0, 9000, 0
				},
				{
					0.008
				}
			)
		hdssBGCOLOR(i, 0, 0, 0, col, col);
		hdssBGCOLOR(i, 1, 0, 0, col, col);
		hdssBGCOLOR(i, 2, 0, col, col, 0);
		hdssBGCOLOR(i, 3, 0, col, col, 0);
		end
		
	end

	if math.mod(con, 2) == 1 then	
		for i=0, 1 do
			hdss.Call(
				HDSS_EB,
				{
					LConst_EnemyTypeBlue, 0, hge.Random_Int(0, 16) * 10 + 80, 280, 9000, 0.1, LConst_EnemyTypeBlue, 20, 0
				}
			)
			hdss.Call(
				HDSS_EB,
				{
					LConst_EnemyTypeBlue, 1, hge.Random_Int(0, 16) * 10 + 400, 280, 9000, 0.1, LConst_EnemyTypeBlue, 20, 0
				}
			)
		end
	end

end