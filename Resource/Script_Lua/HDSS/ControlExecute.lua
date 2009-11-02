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
				HDSS_BGVALUE,
				{
					1, SI_Title_Start, 480, 240, -1, -1
				}
			)
			hdss.Call(
				HDSS_BGVALUE,
				{
					2, SI_Title_Replay, 480, 270, -1, -1
				}
			)
			hdss.Call(
				HDSS_BGVALUE,
				{
					3, SI_Title_Quit, 480, 300, -1, -1
				}
			)
		end
	end
	
	return true;

end