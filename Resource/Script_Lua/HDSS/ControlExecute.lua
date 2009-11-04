function ControlExecute(name, con)

	if name == STATE_TITLE then
		if con == 1 then
			hdss.Call(
				HDSS_BGVALUE, 
				{
					0, SI_TitleScene, TotalCenterX, TotalCenterY, TotalW, TotalH
				}
			)
			hdss.Call(
				HDSS_SELBUILD,
				{
					0, 0, SI_Title_Start, 480, 240
				},
				{
					0, 0,
					-4, -4,
					-8, 0,
					8, 8
				}
			)
			hdss.Call(
				HDSS_SELBUILD,
				{
					0, 1, SI_Title_Replay, 480, 270
				},
				{
					0, 0,
					-4, -4,
					-8, 0,
					8, 8
				}
			)
			hdss.Call(
				HDSS_SELBUILD,
				{
					0, 2, SI_Title_Quit, 480, 300
				},
				{
					0, 0,
					-4, -4,
					-8, 0,
					8, 8
				}
			)
			hdss.Call(
				HDSS_SELSET,
				{
					0, 3, 0, KS_UP, KS_DOWN, KS_FIRE, KS_SPECIAL
				},
				{
					0, 0, 0
				}
			)
		end
	end
	
	return true;

end