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
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, 0, 2);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local hscale = 1.25;
	local vscale = 1.25;
	if draintimer < 30 then
		hscale = (draintimer / 30) * 1.25;
	else
		draintimer = 30;
	end
	
	
--	local lastx, lasty, lastmx, lastmy, moveangle, moved = game.GetPlayerMoveInfo(playerindex, 1);

	local drainangle = hdss.Get(HDSS_D, LConst_Desc_DrainAngle+playerindex);
	local moveangle = 9000;
	local bkeyup = hdss.Get(HDSS_CHECKKEY, playerindex, KSI_UP);
	local bkeydown = hdss.Get(HDSS_CHECKKEY, playerindex, KSI_DOWN);
	local bkeyleft = hdss.Get(HDSS_CHECKKEY, playerindex, KSI_LEFT);
	local bkeyright = hdss.Get(HDSS_CHECKKEY, playerindex, KSI_RIGHT);
	if bkeyup and not bkeydown then
		if bkeyleft and not bkeyright then
			moveangle = -13500;
		elseif not bkeyleft and bkeyright then
			moveangle = -4500;
		else
			moveangle = -9000;
		end
	elseif not bkeyup and bkeydown then
		if bkeyleft and not bkeyright then
			moveangle = 13500;
		elseif not bkeyleft and bkeyright then
			moveangle = 4500;
		else
			moveangle = 9000;
		end
	else
		if bkeyleft and not bkeyright then
			moveangle = 18000;
		elseif not bkeyleft and bkeyright then
			moveangle = 0;
		else
			moveangle = drainangle-18000;
		end
	end
	
	moveangle = moveangle + 18000;
	moveangle = hdss.Get(HDSS_REGANGLE, moveangle);
	
	local baseangle = drainangle;
	if moveangle ~= drainangle then
		
		local plusval = 1500;
		drainangle = hdss.Get(HDSS_REGANGLE, drainangle);
		local bplus = true;
		if moveangle > drainangle then
			if drainangle + 18000 < moveangle then
				bplus = false;
			end
		else
			if moveangle + 18000 > drainangle then
				bplus = false;
			end
		end
		
		if bplus then
			if moveangle < drainangle then
				moveangle = moveangle + 36000;
			end
			baseangle = drainangle + plusval;
			if baseangle > moveangle then
				baseangle = moveangle;
			end
		else
			if moveangle > drainangle then
				moveangle = moveangle - 36000;
			end	
			baseangle = drainangle - plusval;
			if baseangle < moveangle then
				baseangle = moveangle;
			end
		end
		baseangle = hdss.Get(HDSS_REGANGLE, baseangle);
	end
	
	local roffset = 15;
	local cenx = x + roffset * hdss.Get(HDSS_COSA, baseangle+18000);
	local ceny = y + roffset * hdss.Get(HDSS_SINA, baseangle+18000);
	hdssSD(LConst_Desc_DrainAngle+playerindex, baseangle);
	game.SetDrainSpriteInfo(playerindex, cenx, ceny, baseangle+9000, hscale, vscale);
	
	local r = 160;
	local xadjc = 80;
	local xadjcc = 80;
	local yadjc = 80 * draintimer / 30;
	local yadjcc = -yadjc;
	
	local rl = 80;
	local rs = yadjc;
	
	local cosbaseangle = hdss.Get(HDSS_COSA, baseangle);
	local sinbaseangle = hdss.Get(HDSS_SINA, baseangle);
		
	local newxadjc = cosbaseangle * xadjc - sinbaseangle * yadjc;
	local newyadjc = sinbaseangle * xadjc + cosbaseangle * yadjc;
	local newxadjcc = cosbaseangle * xadjcc - sinbaseangle * yadjcc;
	local newyadjcc = sinbaseangle * xadjcc + cosbaseangle * yadjcc;
			
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, cenx, ceny, r);
	hdssENAZBUILD(playerindex, ENAZTYPE_RIGHTANGLED+ENAZOP_OR, cenx+newxadjcc, ceny+newyadjcc, rl, rs, baseangle - 9000);
	hdssENAZBUILD(playerindex, ENAZTYPE_RIGHTANGLED+ENAZOP_OR, cenx+newxadjc, ceny+newyadjc, rs, rl, baseangle + 18000);
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, cenx, ceny, r);
	
	return true;
end


function ePlayerDrain_03(playerindex, x, y, draintimer, type)
	
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, 0.625, 2);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local hscale;
	if draintimer < 184 then
		hscale = draintimer / 184 + 0.125;
	else
		hscale = 1.125;
	end
	game.SetDrainSpriteInfo(playerindex, x, y, 0, hscale);
	
	local r = hscale * 128;
	
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x, y, r);
	return true;
end

function ePlayerDrain_04(playerindex, x, y, draintimer, type)
	
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, 0.625, 2);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local hscale = 1;
	local vscale = 1;
	if draintimer < 50 then
		hscale = (draintimer / 50);
	else
		draintimer = 50;
	end
		
	local cenx = x;
	local ceny = y + 15;
	game.SetDrainSpriteInfo(playerindex, cenx, ceny, 0, hscale, vscale);
	
	local r = 128;
	local xadjc = 64;
	local xadjcc = 64;
	local yadjc = 64 * draintimer / 50;
	local yadjcc = -yadjc;
	
	local rl = 80;
	local rs = yadjc;
			
	local newxadjc = yadjc;
	local newyadjc = -xadjc;
	local newxadjcc = yadjcc;
	local newyadjcc = -xadjcc;
			
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, cenx, ceny, r);
	hdssENAZBUILD(playerindex, ENAZTYPE_RIGHTANGLED+ENAZOP_OR, cenx+newxadjcc, ceny+newyadjcc, rl, rs, -18000);
	hdssENAZBUILD(playerindex, ENAZTYPE_RIGHTANGLED+ENAZOP_OR, cenx+newxadjc, ceny+newyadjc, rs, rl, 9000);
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, cenx, ceny, r);
	
	return true;
end

function ePlayerDrain_05(playerindex, x, y, draintimer, type)
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, 0.3125, 2);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local cenx = x;
	local ceny = y-16;
	game.SetDrainSpriteInfo(playerindex, cenx, ceny);

	local rs = 48;
	local rl = 80;

	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, cenx, ceny, 128);
	hdssENAZBUILD(playerindex, ENAZTYPE_RIGHTANGLED+ENAZOP_OR, cenx-64, ceny, rs, rl, -15193);
	hdssENAZBUILD(playerindex, ENAZTYPE_RIGHTANGLED+ENAZOP_OR, cenx+64, ceny, rl, rs, 6193);
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, cenx, ceny, 128);
	
	return true;
end

function ePlayerDrain_06(playerindex, x, y, draintimer, type)
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, 0.625, 2);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local hscale = 1;
	
	local drainangle = hdss.Get(HDSS_D, LConst_Desc_DrainAngle+playerindex)+9000;
	local moveangle = 0;
	if draintimer == 1 then
		drainangle = 0;
	end
	local bkeyleft = hdss.Get(HDSS_CHECKKEY, playerindex, KSI_LEFT);
	local bkeyright = hdss.Get(HDSS_CHECKKEY, playerindex, KSI_RIGHT);
	if bkeyleft and not bkeyright then
		moveangle = -3000;
	elseif not bkeyleft and bkeyright then
		moveangle = 3000;
	end
		
	moveangle = hdss.Get(HDSS_REGANGLE, moveangle);
	local baseangle = drainangle;
	if moveangle ~= drainangle then
		
		local plusval = 150;
		drainangle = hdss.Get(HDSS_REGANGLE, drainangle);
		local bplus = true;
		if moveangle > drainangle then
			if drainangle + 18000 < moveangle then
				bplus = false;
			end
		else
			if moveangle + 18000 > drainangle then
				bplus = false;
			end
		end
		
		if bplus then
			if moveangle < drainangle then
				moveangle = moveangle + 36000;
			end
			baseangle = drainangle + plusval;
			if baseangle > moveangle then
				baseangle = moveangle;
			end
		else
			if moveangle > drainangle then
				moveangle = moveangle - 36000;
			end	
			baseangle = drainangle - plusval;
			if baseangle < moveangle then
				baseangle = moveangle;
			end
		end
		baseangle = hdss.Get(HDSS_REGANGLE, baseangle);
	end
	hdssSD(LConst_Desc_DrainAngle+playerindex, baseangle-9000);
	
	
	game.SetDrainSpriteInfo(playerindex, x, y, baseangle, hscale);
		
	local r = 128 * hscale;
	local rl = r * 0.95105651629515357211643933337938 / 2;
	local rs = r * 0.69098300562505257589770658281718 / 2;
	local rc = r * 0.47692506126500779613470272746983;
--	local l = r * 1.1755705045849462583374119092781;
	local alphaangle = -6761.3822440803248593179302045761;
--	local alphaanglearc = -1.1800838214508454916725787783211;
	
	local cenangle = baseangle + alphaangle;
		
	local cenpos	=	
	{
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0}
	}

	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x, y, r);
	for i=0, 4 do
		cenpos[i+1][1] = hdss.Get(HDSS_COSA, cenangle+i*7200) * rc;
		cenpos[i+1][2] = hdss.Get(HDSS_SINA, cenangle+i*7200) * rc;
		hdssENAZBUILD(playerindex, ENAZTYPE_RIGHTANGLED+ENAZOP_OR, x+cenpos[i+1][1], y+cenpos[i+1][2], rl, rs, 7200*i+1800+baseangle);
	end
	
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x, y, r);
	return true;
end

function ePlayerDrain_07(playerindex, x, y, draintimer, type)
	
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, 0.625, 2);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local hscale;
	if draintimer < 3 then
		hscale = draintimer * 0.25 + 0.75;
	else
		hscale = 1.5;
	end
	game.SetDrainSpriteInfo(playerindex, x, y, 0, hscale);
	
	local r = hscale * 32;
	
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x, y, r);
	
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
	
	local r = 128 * hscale;
	local rl = r * 0.95105651629515357211643933337938 / 2;
	local rs = r * 0.69098300562505257589770658281718 / 2;
	local rc = r * 0.47692506126500779613470272746983;
--	local l = r * 1.1755705045849462583374119092781;
	local alphaangle = -6761.3822440803248593179302045761;
--	local alphaanglearc = -1.1800838214508454916725787783211;
	
	local cenangle = alphaangle;
		
	local cenpos	=	
	{
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0}
	}

	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x, y, r);
	for i=0, 4 do
		cenpos[i+1][1] = hdss.Get(HDSS_COSA, cenangle+i*7200) * rc;
		cenpos[i+1][2] = hdss.Get(HDSS_SINA, cenangle+i*7200) * rc;
		hdssENAZBUILD(playerindex, ENAZTYPE_RIGHTANGLED+ENAZOP_OR, x+cenpos[i+1][1], y+cenpos[i+1][2], rl, rs, 7200*i+1800);
	end
	
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x, y, r);
	
	return true;
end