function ePlayerSendEx_0(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID)
	local aimx = helper_GetCenterX(oplayerindex) + RANDTF(-136, 136);
	local aimy = RANDTF(16, 144);
	local chasetimer = RANDT(45, 60);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

function ePlayerSendEx_1(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID)
	local aimx = helper_GetCenterX(oplayerindex) + RANDTF(-136, 136);
	local aimy = CenterH + 16;
	local chasetimer = RANDT(45, 60);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

--

function ePlayerSendExChase_0(playerindex, x, y, playerID, appendfloat)
	
	local rank, cardlevel, bosslevel = hdss.Get(HDSS_RANK, 1-playerindex);
	local angle;
	angle = RANDT(-5500, -2500);
	if RANDT(0, 1) == 1 then
		angle = -18000 - angle;
	end
	local speed = 1.4;
	local type = CC_BulletEx_Reimu;
	local startacctime = 24;
	local stopacctime = cardlevel * 6 + 32;
	local acc = 6;
	local afterstopadd = (stopacctime - startacctime) * acc
	hdssA(playerindex, 
		{
			TIMERLESS, stopacctime, YSETACCADD, startacctime, acc,
			TIMERGREAT, stopacctime, YSETADD, afterstopadd,
			EVERY, BOUNCELR, 0 ,16,
		}
	);
	hdssB(playerindex, x, y, angle, speed, type, 0);
	hdssA(playerindex);
	return true;
end

function ePlayerSendExChase_1(playerindex, x, y, playerID, appendfloat, angleoffset)
	
	if angleoffset == nil then
		angleoffset = 0;
	end
	local rank, cardlevel, bosslevel = hdss.Get(HDSS_RANK, 1-playerindex);
	local speed = 18;
	hdss.Call(
		HDSS_BEB,
		{
			playerindex, x, y, -9000+angleoffset, speed, CC_Bullet_ShuttleBeam, 5, 720, BEAMFLAG_DELAY
		}
	)
	hdssEFFSETUP(playerindex, 83, x, y, 64, angleoffset, 0.01);
	return true;
end