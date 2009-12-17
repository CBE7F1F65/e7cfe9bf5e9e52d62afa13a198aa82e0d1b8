function ePlayerSendEx_0(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID)
	local aimx = helper_GetCenterX(oplayerindex) + game.Random_Float(-136, 136);
	local aimy = game.Random_Float(0, 128);
	local chasetimer = game.Random_Int(45, 60);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

function ePlayerSendEx_1(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID)
	local aimx = helper_GetCenterX(oplayerindex) + game.Random_Float(-136, 136);
	local aimy = 448;
	local chasetimer = game.Random_Int(45, 60);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

--

function ePlayerSendExChase_0(playerindex, x, y, playerID, appendfloat)
	
	local rank, cardlevel, bosslevel = hdss.Get(HDSS_RANK, 1-playerindex);
	local angle;
	if x > LGlobal_GetCenterX(playerindex) then
		angle = game.Random_Int(-6500, -4500);
	else
		angle = game.Random_Int(-13500, -11500);
	end
	local speed = 1.2;
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
	hdss.Call(
		HDSS_B,
		{
			playerindex, x, y, true, angle, speed, type, 0
		}
	)
	hdssA(playerindex);
	return true;
end

function ePlayerSendExChase_1(playerindex, x, y, playerID, appendfloat)
	return true;
end