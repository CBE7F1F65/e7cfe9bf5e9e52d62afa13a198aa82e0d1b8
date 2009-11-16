function ControlExecute(name, con)

	if name == STATE_TITLE then
		return ControlExecute_cTitle(con);
	end
	
	if name == STATE_MATCH_SELECT then
		return ControlExecute_cMatchSelect(con);
	end
	
	if name == STATE_PLAYER_SELECT then
		return ControlExecute_cPlayerSelect(con);
	end
	
	return true;

end