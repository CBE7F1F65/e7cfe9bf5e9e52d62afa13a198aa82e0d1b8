function eSendRedBullet(playerindex, x, y)
	local rank = hdss.Get(HDSS_RANK);
	local angle = hdssAMAP(x, y, hge.Random_Int(-1500, 1500));
	local speed = 1.3 + rank * 0.11;
	hdss.Call(
		HDSS_B,
		{
			playerindex, x, y, true, angle, speed, 13, 4
		}
	)
	return true;
end

function eSendBlueBullet(playerindex, x, y)
	local rank = hdss.Get(HDSS_RANK);
	local angle = 9000 + hge.Random_Int(-9000/7, 9000/7);
	local speed = 1.3 + rank * 0.11;
	hdss.Call(
		HDSS_B,
		{
			playerindex, x, y, true, angle, speed, 13, 6
		}
	)
	return true;
end

function eSendExBullet(playerindex, x, y)
	return true;
end

function eSendItemBullet(playerindex, x, y)
	return true;
end

function eSendGreenGhost(playerindex, x, y)
	return true;
end

function eSendYellowGhost(playerindex, x, y)
	return true;
end

function eSendRedGhost(playerindex, x, y)
	return true;
end

function eSendExAttack(playerindex, x, y)
	return true;
end