function Edef_ShootChargeEnemyEID_02_1(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 80);
	end
	if math.mod(timer, 12) == 0 then
		local turn = timer/12;
		local num = level * 1.5;
		local angle = level * 1340 + turn * 120;
		local r = 64 - turn * 8;
		local speed = turn * 0.08 + level * 0.1 + 1.2;
		hdssA(playerindex,
			{
				TIMEREQUAL, 9, ANGLESETADD, 18000 + turn * 400
			}
		)
		hdssBC(playerindex, num, angle, r, x, y, speed, CC_Bullet_Shuttle, turn+7);
		hdssBC(playerindex, num, angle+18000/num, r, x, y, speed, CC_Bullet_SmallBall, turn+7);
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_02_2(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 60);
	end
	local timemod = 64;
	if level > 12 then
		timemod = 32;
	end
	if math.mod(timer, timemod) == 1 then
		local turn = math.floor(timer/timemod);
		local length = 80 + turn * 20;
		local num = level * 2;
		if level <= 12 then
			num = num * 1.5;
		end
		local space = length/(num-2);
		local tr = length / 1.618;
		
		hdssA(playerindex,
			{
				TIMERRANGE, 32, 64, SPEEDSETADD, level/5+2
			}
		)
		for i=0, 4 do
			local baseangle = i*7200 + turn * 18000;
			local tx = tr * hdss.Get(HDSS_COSA, baseangle+19800) + x;
			local ty = tr * hdss.Get(HDSS_SINA, baseangle+19800) + y;
			local angle = baseangle + 9000;
			hdss.Call(
				HDSS_BL,
				{
					playerindex, num, baseangle, space, 0, tx, ty, angle, -27000/num + turn * 18000, 0, 0, CC_Bullet_Shuttle, turn*4+2
				}
			)
		end
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_02_3(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_02_3_A(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_02_3_B(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_02_3_C(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_02_3_D(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_02_3_E(playerindex, level, x, y, timer, px, py)
	return true;
end