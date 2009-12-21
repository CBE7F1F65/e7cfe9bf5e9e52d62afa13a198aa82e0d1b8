function Edef_ShootChargeEnemyEID_0_1(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA(playerindex, ENAC_FADEOUT_T, 100);
	end
	if math.mod(timer, 32) == 2 then
		local turn = math.floor(timer / 32);
		if level < 15 and turn > 1 then
			return;
		end
		local num = level * 2 + 32;
		local baseangle = game.Random_Int(1, 36000);
		local addangle = 18000 / num;
		local speed = level * 0.2 + 0.4;
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
		
		baseangle = game.Random_Int(1, 36000);
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

function Edef_ShootChargeEnemyEID_0_2(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA(playerindex, ENAC_FADEOUT_T, 100);
	end
	if math.mod(timer, 32) == 2 then
		local turn = math.floor(timer / 32);
		if level < 15 and turn > 1 then
			return;
		end
		local num = level * 2 + 48;
		local baseangle = game.Random_Int(1, 36000);
		local speed = level * 0.08 + 1.4;
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

function Edef_ShootChargeEnemyEID_0_3(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		local cx = LGlobal_GetCenterBossX(playerindex);
		local cy = CenterBossY;
		hdssEA(playerindex, ENAC_OVERPLAYER_CXYT, 60, cx, cy, 90);
	elseif timer == 810 then
		hdssEA(playerindex, ENAC_FADEOUT_T, 810);
	elseif math.mod(timer, 90) == 60 then
		local pattern = game.Random_Int(0, 4);
		if pattern == 0 then
			
			local baseangle = game.Random_Int(1, 36000);
			local num = 40 + level * 4;
			for i=0, 4 do
				local speed = level * 0.1 + i * 0.5 + 0.4;
				hdss.Call(
					HDSS_BC,
					{
						playerindex, num, baseangle, 0, x, y, speed, CC_Bullet_Amulet, 1
					}
				)
			end
				
		elseif pattern == 1 then
			hdss.Call(
				HDSS_EB,
				{
					CC_ShootChargeEnemyEID_0_3_B, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10, 0
				}
			)
			hdssENSAIM(playerindex, level);	
		elseif pattern == 2 then
			
			local num = 40 + level * 2;
			local baseangle = game.Random_Int(1, 36000);
			local speed = level * 0.08 + 1.2;
			hdssA(playerindex,
				{
					TIMERLESS, 90, SPEEDSETADD, -2,
					TIMEREQUAL, 90, SPEEDSET, speed*100,
					TIMEREQUAL, 90, ANGLESETAMAP, 0,
					TIMERLESS, 180, REMAIN,
				}
			)
			for i=0, 1 do
				hdss.Call(
					HDSS_BC,
					{
						playerindex, num, baseangle, 0, x, y, speed + i * 0.4, CC_Bullet_Amulet, 15
					}
				)
			end
			hdssA(playerindex);
		
		elseif pattern == 3 then
			
			local num = 30 + level;
			local baseangle = game.Random_Int(1, 36000);
			local speed = level * 0.02 + 0.8;
			for i=0, 1 do
				hdssA(playerindex,
					{
						TIMERLESS, 90, ANGLESETADD, hdss.Get(HDSS_SIGN, i) * 100
					}
				)
				hdss.Call(
					HDSS_BC,
					{
						playerindex, num, baseangle, 0, x, y, speed, CC_Bullet_SmallBall, i * 14 + 1
					}
				)
			end
			hdssA(playerindex);
			
		else
			hdss.Call(
				HDSS_EB,
				{
					CC_ShootChargeEnemyEID_0_3_E, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10, 0
				}
			)
			hdssENSAIM(playerindex, level);	
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_0_3_B(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA(playerindex, ENAC_FADEOUT_T, 8+math.floor(level/2));
	else
		local baseangle = hdssAMAP(playerindex, x, y);
		local speed = 0.5 + timer * 0.1 + level * 0.02;
		hdss.Call(
			HDSS_B,
			{
				playerindex, x, y, true, baseangle, speed, CC_Bullet_Amulet, 1
			}
		)
		for i=0, 2 do
			local angle = baseangle + (i-1) * 1500;
			speed = 1.0 + timer * 0.1 + level * 0.02;
			hdss.Call(
				HDSS_B,
				{
					playerindex, x, y, true, angle, speed, CC_Bullet_SmallBall, 15
				}
			)
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_0_3_E(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA(playerindex, ENAC_FADEOUT_T, 48+level*4);
	elseif math.mod(timer, 12) == 0 then
		ePlayerSendExChase_0(playerindex, x, y);
	end
	return true;
end