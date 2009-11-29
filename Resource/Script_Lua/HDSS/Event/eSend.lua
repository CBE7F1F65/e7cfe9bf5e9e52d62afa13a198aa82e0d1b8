function _eSendBulletSpeedRestrict(speed, rank)
	speed = speed + hge.Random_Float(-0.1, 0.1);
	if speed < 0.8 then
		speed = 0.8;
	elseif speed > 3.0 + rank * 0.1 then
		speed = 3.0 + rank * 0.1;
	end
	return speed;
end

function eSendRedBullet(playerindex, x, y, setID, bSmall)
	local rank = hdss.Get(HDSS_RANK);
	local angle = 9000 + hge.Random_Int(-1500, 1500);
	local speed = 1.3 + rank * 0.11;
	speed = _eSendBulletSpeedRestrict(speed, rank);
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
		game.AddSendBulletInfo(setID+2, playerindex, index);
	end
	return true;
end

function eSendBlueBullet(playerindex, x, y, setID, bSmall)
	local rank = hdss.Get(HDSS_RANK);
	local angle = hdssAMAP(playerindex, x, y, hge.Random_Int(-9000/7, 9000/7));
	local speed = 1.3 + rank * 0.11;
	speed = _eSendBulletSpeedRestrict(speed, rank);
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
		game.AddSendBulletInfo(setID+2, playerindex, index);
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

function eSendGreenGhost(playerindex, x, y, setID)
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