function ePlayerDrain_0(playerindex, x, y, draintimer, type, aimx, aimy)
	local hscale;
	if draintimer < 20 then
		hscale = draintimer * 0.125 + 0.5;
	else
		hscale = 3;
	end
	if type ~= nil and aimx ~= nil and aimy ~= nil then
		local r = hscale * 32;
		if hdssCOLLISION_CIRCLE(x, y, aimx, aimy, r, true) then
			game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, 0.625, 4);
		end
	else
		game.SetDrainSpriteInfo(playerindex, x, y, 0, hscale);
	end
	return true;
end

function ePlayerDrain_1(playerindex, playerID, x, y, draintimer)
	return true;
end