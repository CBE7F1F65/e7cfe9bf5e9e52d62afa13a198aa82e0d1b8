function _eSendBulletSpeedRestrict(speed, rank)
	speed = speed + game.Random_Float(-0.1, 0.1);
	if speed < 0.8 then
		speed = 0.8;
	elseif speed > 3.0 + rank * 0.1 then
		speed = 3.0 + rank * 0.1;
	end
	return speed;
end

function _eSendBulletSpeed(rank, bSmall)
	return 1.3 + rank * 0.11;
end

function _eSendBigBulletAngle()
	return game.Random_Int(8250, 9750);
end

function eSendRedBullet(playerindex, x, y, sendtime, speed, setID, bSmall)
	local rank = hdss.Get(HDSS_RANK);
	local angle;
	if bSmall then
		angle = game.Random_Int(7500, 10500);
	else
		angle = _eSendBigBulletAngle();
	end
	if speed < 0 then
		speed = _eSendBulletSpeed(rank);
	elseif not bSmall then
		speed = speed + 0.3;
	end
	speed = _eSendBulletSpeedRestrict(speed, rank);
	local type = CC_Bullet_MiddleBall;
	if bSmall then
		type = CC_Bullet_SmallBall;
	end
	local index = hdss.Call(
		HDSS_B,
		{
			playerindex, x, y, true, angle, speed, type, 4
		}
	)
	if bSmall then
		game.AddSendBulletInfo(setID, sendtime+1, playerindex, index);
	end
	return true;
end

function eSendBlueBullet(playerindex, x, y, sendtime, speed, setID, bSmall)
	local rank = hdss.Get(HDSS_RANK);
	local angle;
	if bSmall then
		angle = hdssAMAP(playerindex, x, y, game.Random_Int(-9000/7, 9000/7));
	else
		angle = _eSendBigBulletAngle();
	end
	if speed < 0 then
		speed = _eSendBulletSpeed(rank, bSmall);
	elseif not bSmall then
		speed = speed + 0.3;
	end
	speed = _eSendBulletSpeedRestrict(speed, rank);
	local type = CC_Bullet_MiddleBall;
	if bSmall then
		type = CC_Bullet_SmallBall;
	end
	local index = hdss.Call(
		HDSS_B,
		{
			playerindex, x, y, true, angle, speed, type, 6
		}
	)
	if bSmall then
		game.AddSendBulletInfo(setID, sendtime+1, playerindex, index);
	end
	return true;
end

function eSendExBullet(playerindex, x, y, setID)
	local rank = hdss.Get(HDSS_RANK);
	local angle = 9000 + game.Random_Int(-7500, 7500);
	local speed = 1.7 + rank * 0.1;
	--aya
	speed = speed + 0.3;
	speed = _eSendBulletSpeedRestrict(speed, rank);
	local index = hdss.Call(
		HDSS_B,
		{
			playerindex, x, y, true, angle, speed, CC_Bullet_MiddleBall, 5
		}
	)
	return true;
end

function eSendItemBullet(playerindex, x, y, setID)
	return true;
end

function eSendGhost(playerindex, x, y, sendtime, acceladd, setID)
	local rank = hdss.Get(HDSS_RANK);
	
	local accel;
	acceladd = acceladd + game.Random_Float(0, 1/120);
	if sendtime == 0 then
		acceladd =  acceladd + rank / 600;
		accel = 0.025;
	elseif sendtime == 1 then
		accel = 0.03;
	else
		accel = 0.11 / 3;
	end
		
	local angle;
	--
	if game.Random_Int(0, 4) == 0 then
		angle = hdssAMAP(playerindex, x, y, game.Random_Int(-2250, 2250));
	else
		angle = game.Random_Int(8910, 9090);
	end
	--
	local type = LConst_GhostTypeStart + sendtime * 2;
	local index = hdss.Call(
		HDSS_EB,
		{
			type, playerindex, x, y, angle, 0, type, 20, 0
		}
	);
	if index ~= nil then
		game.AddSendGhostInfo(setID, sendtime, playerindex, accel+acceladd, acceladd, index);
	end
	return true;
end

function eSendYellowGhost(playerindex, x, y, setID)
	return true;
end

function eSendRedGhost(playerindex, x, y, setID)
	return true;
end

function eSendExAttack(playerindex, x, y, playerID, appendfloat, setID)
		for i, it in pairs(LTable_ePlayerSendExChaseFunction) do
			if it[1] == playerID then
				return it[2](playerindex, x, y, playerID, appendfloat);
			end
		end
	return true;
end