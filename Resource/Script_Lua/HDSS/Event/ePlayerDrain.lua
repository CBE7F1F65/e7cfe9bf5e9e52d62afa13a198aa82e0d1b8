function ePlayerDrain_00(playerindex, x, y, draintimer, type)
	
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, 0.625, 2);
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

function ePlayerDrain_01(playerindex, x, y, draintimer, type)

	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, 0.625, 2);
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
	
	local rl = TotalH/2;
	local rs = 146 / 7 * vscale;
	
	hdssENAZBUILD(playerindex, ENAZTYPE_ELLIPSE+ENAZOP_AND, x, ceny, rs, rl);
	
	return true;
end


function ePlayerDrain_02(playerindex, x, y, draintimer, type)

	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, 0.625, 2);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	if draintimer > 60 then
		draintimer = 60;
	elseif draintimer < 30 then
		draintimer = 30;
	end
	local hscale = (draintimer / 100) + 0.4;
	game.SetDrainSpriteInfo(playerindex, x, y, 0, hscale);
	
	--rinter=57.2311
	--interbaseangle=-6800
	--
	--c=141.0685
	--
	
	local rl = 114.126782 * hscale / 2;
	local rs = 82.9179607 * hscale / 2;
	local cenpos	=	
	{
		{21.7963,	-52.918},
		{57.0634,	4.3769},
		{13.4708,	55.6231},
		{-48.738,	30},
		{-43.5926,	-37.082}
	}

	for i=0, 4 do
		hdssENAZBUILD(playerindex, ENAZTYPE_RIGHTANGLED+ENAZOP_OR, x+cenpos[i+1][1], y+cenpos[i+1][2], rl, rs, 7200*i+1800);
	end
	
	local r = 120 * hscale;
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x, y, r);
	
	return true;
end


function ePlayerDrain_03(playerindex, x, y, draintimer, type)
	return true;
end

function ePlayerDrain_04(playerindex, x, y, draintimer, type)
	return true;
end

function ePlayerDrain_05(playerindex, x, y, draintimer, type)
	return true;
end

function ePlayerDrain_06(playerindex, x, y, draintimer, type)
	return true;
end

function ePlayerDrain_07(playerindex, x, y, draintimer, type)
	return true;
end

function ePlayerDrain_08(playerindex, x, y, draintimer, type)
	return true;
end

function ePlayerDrain_09(playerindex, x, y, draintimer, type)
	return true;
end

function ePlayerDrain_10(playerindex, x, y, draintimer, type)
	return true;
end

function ePlayerDrain_11(playerindex, x, y, draintimer, type)
	return true;
end

function ePlayerDrain_12(playerindex, x, y, draintimer, type)
	return true;
end

function ePlayerDrain_13(playerindex, x, y, draintimer, type)
	return true;
end

function ePlayerDrain_14(playerindex, x, y, draintimer, type)
	return true;
end

function ePlayerDrain_15(playerindex, x, y, draintimer, type)
	return true;
end

function ePlayerDrain_16(playerindex, x, y, draintimer, type)
	return true;
end

function ePlayerDrain_17(playerindex, x, y, draintimer, type)
	return true;
end

function ePlayerDrain_18(playerindex, x, y, draintimer, type)
	return true;
end

function ePlayerDrain_19(playerindex, x, y, draintimer, type)
	return true;
end

function ePlayerDrain_20(playerindex, x, y, draintimer, type)
	return true;
end

function ePlayerDrain_21(playerindex, x, y, draintimer, type)
	return true;
end

function ePlayerDrain_22(playerindex, x, y, draintimer, type)
	return true;
end