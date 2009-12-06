function ePlayerDrain_0(playerindex, x, y, draintimer, type)
	
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, 0.625, 4);
		return true;
	end
	
	local hscale;
	if draintimer < 20 then
		hscale = draintimer * 0.125 + 0.5;
	else
		hscale = 3;
	end
	game.SetDrainSpriteInfo(playerindex, x, y, 0, hscale);
	
	local r = hscale * 32;
	
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x, y, r);
	
	return true;
end

function ePlayerDrain_1(playerindex, playerID, x, y, draintimer)
	return true;
end