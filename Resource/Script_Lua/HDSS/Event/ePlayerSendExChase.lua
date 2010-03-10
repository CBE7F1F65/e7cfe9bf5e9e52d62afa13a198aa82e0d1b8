function ePlayerSendExChase_00(playerindex, x, y, playerID, appendfloat)
	
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

function ePlayerSendExChase_01(playerindex, x, y, playerID, appendfloat, angleoffset)
	
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
	hdssEFFSETUP(playerindex, LConst_effid_sendex_01, x, y, 64, angleoffset, 0.01);
	return true;
end

function ePlayerSendExChase_02(playerindex, x, y, playerID, appendfloat)
	local rank, cardlevel, bosslevel = hdss.Get(HDSS_RANK, 1-playerindex);
	local angle = hdssAMAP(playerindex, x, y);
	hdssEB(CC_SendExChaseEnemyEID_02, 1-playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssENSAIM(1-playerindex, rank, 0, 0, angle);
	return true;
end

function ePlayerSendExChase_03(playerindex, x, y, playerID, appendfloat)
	return true;
end

function ePlayerSendExChase_04(playerindex, x, y, playerID, appendfloat)
	return true;
end

function ePlayerSendExChase_05(playerindex, x, y, playerID, appendfloat)
	return true;
end

function ePlayerSendExChase_06(playerindex, x, y, playerID, appendfloat)
	return true;
end

function ePlayerSendExChase_07(playerindex, x, y, playerID, appendfloat)
	return true;
end

function ePlayerSendExChase_08(playerindex, x, y, playerID, appendfloat)
	return true;
end

function ePlayerSendExChase_09(playerindex, x, y, playerID, appendfloat)
	return true;
end

function ePlayerSendExChase_10(playerindex, x, y, playerID, appendfloat)
	return true;
end

function ePlayerSendExChase_11(playerindex, x, y, playerID, appendfloat)
	return true;
end

function ePlayerSendExChase_12(playerindex, x, y, playerID, appendfloat)
	return true;
end

function ePlayerSendExChase_13(playerindex, x, y, playerID, appendfloat)
	return true;
end

function ePlayerSendExChase_14(playerindex, x, y, playerID, appendfloat)
	return true;
end

function ePlayerSendExChase_15(playerindex, x, y, playerID, appendfloat)
	return true;
end

function ePlayerSendExChase_16(playerindex, x, y, playerID, appendfloat)
	return true;
end

function ePlayerSendExChase_17(playerindex, x, y, playerID, appendfloat)
	return true;
end

function ePlayerSendExChase_18(playerindex, x, y, playerID, appendfloat)
	return true;
end

function ePlayerSendExChase_19(playerindex, x, y, playerID, appendfloat)
	return true;
end

function ePlayerSendExChase_20(playerindex, x, y, playerID, appendfloat)
	return true;
end

function ePlayerSendExChase_21(playerindex, x, y, playerID, appendfloat)
	return true;
end

function ePlayerSendExChase_22(playerindex, x, y, playerID, appendfloat)
	local rank, cardlevel, bosslevel = hdss.Get(HDSS_RANK, 1-playerindex);
	local speed = rank * 0.1 + 1.2;
	local angle = hdssAMAP(playerindex, x, y);
	hdssB(playerindex, x, y, angle, speed, CC_Bullet_BigStar, 5, 9);
	hdssA(playerindex,
		{
			TIMEREQUAL, 9, ANGLESET, angle
		}
	)
	hdssBC(playerindex, 5, 9000, 6, x, y, speed, CC_Bullet_Star, 10);
	hdssA(playerindex);
	return true;
end