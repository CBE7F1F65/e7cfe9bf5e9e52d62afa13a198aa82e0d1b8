function ControlExecute_cMatchSelect(con)

	local selsysid = 0;
	if con == 1 then
		hdss.Call(
			HDSS_BGVALUE, 
			{
				0, SI_SelectScene, TotalCenterX, TotalCenterY, TotalW, TotalH
			}
		)
	end
		
	return true;

end