function _eSendBulletSpeedRestrict(speed, rank)
	speed = speed + hge.Random_Float(-0.1, 0.1);
	if speed < 0.8 then
		speed = 0.8;
	elseif speed > 3.0 + rank * 0.1 then
		speed = 3.0 + rank * 0.1;
	end
	return speed;
end

function eSendRedBullet(playerindex, x, y, sendtime, speed, setID, bSmall)
	local rank = hdss.Get(HDSS_RANK);
	local angle = 9000 + hge.Random_Int(-1500, 1500);
	if speed < 0 then
		speed = 1.3 + rank * 0.11;
		speed = _eSendBulletSpeedRestrict(speed, rank);
	end
	local type = 3;
	if bSmall then
		type = 13;
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
	local angle = hdssAMAP(playerindex, x, y, hge.Random_Int(-9000/7, 9000/7));
	if speed < 0 then
		speed = 1.3 + rank * 0.11;
		speed = _eSendBulletSpeedRestrict(speed, rank);
	end
	local type = 3;
	if bSmall then
		type = 13;
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
	local angle = 9000 + hge.Random_Int(-7500, 7500);
	local speed = 1.7 + rank * 0.1;
	--aya
	speed = speed + 0.3;
	speed = _eSendBulletSpeedRestrict(speed, rank);
	local index = hdss.Call(
		HDSS_B,
		{
			playerindex, x, y, true, angle, speed, 3, 5
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
	acceladd = acceladd + hge.Random_Float(0, 1/120);
	if sendtime == 0 then
		acceladd =  acceladd + rank / 600;
		accel = 0.025;
	elseif sendtime == 1 then
		accel = 0.03;
	else
		accel = 0.11 / 3;
	end
	
	sendtime = sendtime + 1;
	if sendtime >= 3 then
		sendtime = 3;
	end
	local angle = hge.Random_Int(8910, 9090);
	--
	local type = 8 + sendtime * 2;
	local index = hdss.Call(
		HDSS_EB,
		{
			type, playerindex, x, y, angle, 0, type, 20, 0
		}
	)
	if accel+acceladd <= 0.0001 then
		MB()
	end
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

function eSendExAttack(playerindex, x, y, setID)
	return true;
end