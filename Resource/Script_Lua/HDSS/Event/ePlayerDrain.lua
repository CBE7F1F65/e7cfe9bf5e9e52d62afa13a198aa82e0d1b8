function ePlayerDrain_0(playerindex, x, y, draintimer, type)
	
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, 0.625, 4);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
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

function ePlayerDrain_1(playerindex, x, y, draintimer, type)

	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, 0.625, 4);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	if draintimer > 100 then
		draintimer = 100;
	elseif draintimer < 30 then
		draintimer = 30;
	end
	local hscale = (draintimer / 100) * 1.75;
	local vscale = 1.75;
	local ceny = y-TotalH/2+16;
	game.SetDrainSpriteInfo(playerindex, x, ceny, 0, hscale, vscale);
	
	local rl = 448;
	local rs = 146 / 7 * vscale;
	
	hdssENAZBUILD(playerindex, ENAZTYPE_ELLIPSE+ENAZOP_AND, x, ceny, rs, rl);
	
	return true;
end