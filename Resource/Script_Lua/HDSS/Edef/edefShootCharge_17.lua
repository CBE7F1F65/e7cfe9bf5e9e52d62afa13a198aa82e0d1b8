function Edef_ShootChargeEnemyEID_17_1(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 18);
	elseif math.mod(timer, 6) == 0 then
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local nowindex = timer / 6;
		local type = CC_Bullet_Coin;
		if math.mod(nowindex, 2) == 0 then
			type = CC_Bullet_SmallBall;
		end
		local speed = (3-nowindex) * 0.5 + level * 0.08 + 1.0;
		hdssBC(playerindex, 40+level, aimangle, 0, x, y, speed, type, 0);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_17_2(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 18);
	elseif math.mod(timer, 6) == 0 then
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local nowindex = timer / 6;
		local speed = (3-nowindex) * 0.5 + level * 0.08 + 1.0;
		hdssBC(playerindex, 40+level, aimangle, 0, x, y, speed, CC_Bullet_Coin, nowindex-1);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_17_3(playerindex, level, x, y, timer, px, py)
	_ePlayerShootCharge_3_SetBGS(playerindex, 17);
	return true;
end

function Edef_ShootChargeEnemyEID_17_3_A(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_17_3_B(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_17_3_C(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_17_3_D(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_17_3_E(playerindex, level, x, y, timer, px, py)
	return true;
end