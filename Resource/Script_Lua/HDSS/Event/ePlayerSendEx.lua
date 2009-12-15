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
	local angle = 9000;
	local speed = 2.0;
	local type = 15;
	hdssA(playerindex, 
		{
			TIMERLESS, 60, ANGLESETADD, 600
		}
	);
	hdss.Call(
		HDSS_B,
		{
			playerindex, x, y, true, angle, speed, type, 2
		}
	)
	hdssA(playerindex);
	return true;
end

function ePlayerSendExChase_1(playerindex, x, y, playerID, appendfloat)
	return true;
end