function Edef_ShootChargeEnemyEID_0_1(playerindex, x, y, timer, px, py)
	if timer == 1 then
		hdssEA(playerindex, ENAC_FADEOUT_T, 100);
	end
	if math.mod(timer, 32) == 2 then
		local turn = math.floor(timer / 32);
		local level = hdss.Get(HDSS_ENLEVEL, playerindex);
		if level < 15 and turn > 1 then
			return;
		end
		local num = level * 2 + 32;
		local baseangle = game.Random_Int(0, 36000);
		local addangle = 18000 / num;
		local speed = level * 0.2 + 0.4
		hdss.Call(
			HDSS_BC,
			{
				playerindex, num, baseangle, 0, x, y, speed, CC_Bullet_SmallBall, 1
			}
		)
		baseangle = baseangle + addangle;
		hdss.Call(
			HDSS_BC,
			{
				playerindex, num, baseangle, 0, x, y, speed, CC_Bullet_Shuttle, 1
			}
		)
		
		baseangle = game.Random_Int(0, 36000);
		hdssA(playerindex,
			{
				TIMERLESS, 90, SPEEDSETADD, -2,
				TIMEREQUAL, 90, SPEEDSET, speed*150,
				TIMEREQUAL, 90, ANGLESETAMAP, 0,
				TIMERLESS, 180, REMAIN,
			}
		)
		hdss.Call(
			HDSS_BC,
			{
				playerindex, num, baseangle, 0, x, y, speed, CC_Bullet_SmallBall, 15
			}
		)
		baseangle = baseangle + addangle;
		hdss.Call(
			HDSS_BC,
			{
				playerindex, num, baseangle, 0, x, y, speed, CC_Bullet_Shuttle, 15
			}
		)
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_0_2(playerindex, x, y, timer, px, py)
	if timer == 1 then
		hdssEA(playerindex, ENAC_FADEOUT_T, 100);
	end
	if math.mod(timer, 32) == 2 then
		local turn = math.floor(timer / 32);
		local level = hdss.Get(HDSS_ENLEVEL, playerindex);
		if level < 15 and turn > 1 then
			return;
		end
		local num = level * 2 + 48;
		local baseangle = game.Random_Int(0, 36000);
		local speed = level * 0.08 + 1.4
		hdss.Call(
			HDSS_BC,
			{
				playerindex, num, baseangle, 0, x, y, speed, CC_Bullet_Amulet, 1
			}
		)
		
		hdssA(playerindex,
			{
				TIMERLESS, 90, SPEEDSETADD, -2,
				TIMEREQUAL, 90, SPEEDSET, speed*150,
				TIMEREQUAL, 90, ANGLESETAMAP, 0,
				TIMERRANGE, 90, 170, SPEEDSETADD, -speed*15/8,
				TIMEREQUAL, 170, SPEEDSET, speed*100,
				TIMEREQUAL, 170, ANGLESETAMAP, 0,
				TIMERLESS, 240, REMAIN,
			}
		)
		hdss.Call(
			HDSS_BC,
			{
				playerindex, num, baseangle, 0, x, y, speed, CC_Bullet_Amulet, 15
			}
		)
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_0_3(playerindex, x, y, timer, px, py)
	if timer == 1 then
		local cx = LGlobal_GetCenterBossX(playerindex);
		local cy = CenterBossY;
		hdssEA(playerindex, ENAC_OVERPLAYER_CXYT, 60, cx, cy, 120);
	end
	return true;
end


function Edef_ShootChargeEnemyEID_1_1(playerindex, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_1_2(playerindex, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_1_3(playerindex, x, y, timer, px, py)
	return true;
end
