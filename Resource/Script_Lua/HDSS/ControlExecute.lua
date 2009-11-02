function ControlExecute(name, con)

	if name == STATE_TITLE then
		if con == 1 then
			hdss.Call(HDSS_BGVALUE, 1, SI_Title_Start, 320, 240, 640, 480, global.ARGB(0xFF, 0xFFFFFF))
		end
	end
	
	return true;

end