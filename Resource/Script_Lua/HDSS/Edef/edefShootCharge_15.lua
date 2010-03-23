function Edef_ShootChargeEnemyEID_15_1(playerindex, level, x, y, timer, px, py)
	if math.mod(timer, 5) == 0 then
		local nowindex = timer / 5;
		local enangle = hdss.Get(HDSS_ENANGLE, playerindex);
		local leftrightindi = math.mod(timer/6, 2)*2-1;
		local angle = enangle;
		local type = CC_Bullet_MiddleBall;
		if math.mod(nowindex, 2) == 0 then
			hdssA(playerindex,
				{
					TIMERRANGE, 75, 100+level*2, SPEEDSETADD, 4
				}
			)
			type = CC_Bullet_SmallBall;
		else
			hdssA(playerindex,
				{
					TIMERGREAT, 75, SPEEDSETADD, 3,
					TIMEREQUAL, 115+level*2, FADEOUT
				}
			)
			angle = angle+leftrightindi*RANDT(13500, 16000);
		end
		hdssB(playerindex, x, y, angle, 0, type, 14);
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_15_2(playerindex, level, x, y, timer, px, py)
	if math.mod(timer, 5) == 0 then
		local nowindex = timer / 5;
		local enangle = hdss.Get(HDSS_ENANGLE, playerindex);
		local leftrightindi = math.mod(timer/6, 2)*2-1;
		local angle;
		local type = CC_Bullet_MiddleBall;
		if math.mod(nowindex, 2) == 0 then
			hdssA(playerindex,
				{
					TIMERRANGE, 75, 100+level*2, SPEEDSETADD, 4
				}
			)
			type = CC_Bullet_Scale;
			angle = 18000 + enangle;
		else
			hdssA(playerindex,
				{
					TIMERGREAT, 75, SPEEDSETADD, 3,
					TIMEREQUAL, 115+level*2, FADEOUT
				}
			)
			angle = enangle+leftrightindi*RANDT(13500, 16000);
		end
		hdssB(playerindex, x, y, angle, 0, type, 14);
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_15_3(playerindex, level, x, y, timer, px, py)
	_ePlayerShootCharge_3_SetBGS(playerindex, 15);
	return true;
end

function Edef_ShootChargeEnemyEID_15_3_A(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_15_3_B(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_15_3_C(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_15_3_D(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_15_3_E(playerindex, level, x, y, timer, px, py)
	return true;
end