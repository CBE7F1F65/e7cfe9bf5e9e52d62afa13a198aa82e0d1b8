function Edef_ShootChargeEnemyEID_1_1(playerindex, level, x, y, timer, px, py)

	local row = (math.floor((level+1)/4) + 2) * 2;
	local timemod = math.floor(CenterH / row / hdss.Get(HDSS_ENSPEED, playerindex));
	if timer == 1 then
		hdssEA(playerindex, ENAC_FADEOUT_OOOOOTOO,
			{
			},
			{
				0, timemod*(row-1)+1
			}
		);
	end
	if math.mod(timer, timemod) == 1 then
		local num = 8;
		local baseangle;
		if x < LGlobal_GetCenterX(playerindex) then
			baseangle = 4500;
		else
			baseangle = 13500;
		end
		local speed = level * 0.02 + 0.4;
		local type = CC_Bullet_Star;
		if math.mod((timer-1)/timemod, 2) == 1 then
			type = CC_Bullet_SmallBall;
		end
		hdss.Call(
			HDSS_BL,
			{
				playerindex, num, baseangle, 0, 0, x, y, baseangle, 0, speed, 0.3, type, 6
			}
		)
	end
	return true;
end

function Edef_ShootChargeEnemyEID_1_2(playerindex, level, x, y, timer, px, py)
	local row = math.floor((level+1)/4) + 2;
	local timemod = math.floor(CenterH / row / hdss.Get(HDSS_ENSPEED, playerindex));
	if timer == 1 then
		hdssEA(playerindex, ENAC_FADEOUT_OOOOOTOO,
			{
			},
			{
				0, timemod*(row-1)+1
			}
		);
	end
	if math.mod(timer, timemod) == 1 then
		local num = 8;
		local baseangle;
		local color;
		if x < LGlobal_GetCenterX(playerindex) then
			baseangle = 4500;
			color = 10;
		else
			baseangle = 13500;
			color = 6;
		end
		local speed = level * 0.02 + 0.4;
		hdss.Call(
			HDSS_BL,
			{
				playerindex, num, baseangle, 0, 0, x, y, baseangle, 0, speed, 0.3, CC_Bullet_Star, color
			}
		)
	end
	return true;
end

function Edef_ShootChargeEnemyEID_1_3(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		local cx = LGlobal_GetCenterBossX(playerindex);
		local cy = CenterBossY;
		hdssEA(playerindex, ENAC_OVERPLAYER_XYOOOTCE,
			{
				cx, cy
			},
			{
				0, 90, 60, 60
			}
		);
	elseif timer == 810 then
		hdssEA(playerindex, ENAC_FADEOUT_OOOOOTOO,
			{
			},
			{
				0, 810
			}
		);
	elseif math.mod(timer, 90) == 60 then
		local pattern = RANDT(0, 4);
		--
		pattern = 0;
		--
		if pattern == 0 then
			
			hdss.Call(
				HDSS_EB,
				{
					CC_ShootChargeEnemyEID_1_3_A, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, RANDT(1, 36000), 0
				}
			)
			hdssENSAIM(playerindex, level);	
				
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
			local baseangle = RANDT(1, 36000);
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
			local baseangle = RANDT(1, 36000);
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

function Edef_ShootChargeEnemyEID_1_3_A(playerindex, level, x, y, timer, px, py)

	if timer == 1 then
		hdssEA(playerindex, ENAC_FADEOUT_OOOOOTOO,
			{
			},
			{
				0, 40
			}
		);
	elseif math.mod(timer, 2) == 0 then
		local baseangle = (19 * (-38 * level + 418) + 180) * timer + hdss.Get(HDSS_ENLIFE, playerindex);
		local looptime = math.floor(level/6) + 2;
		local speed = level * 0.1 + 1.4;
		local type;
		local color;
		local turn = timer / 2;
		if math.mod(turn, 4) < 2 then
			color = 10;
		else
			color = 6;
		end
		if math.mod(turn, 2) == 0 then
			type = CC_Bullet_SmallBall;
		else
			type = CC_Bullet_Star;
		end
		for i=0, looptime-1 do
			hdss.Call(
				HDSS_BC,
				{
					playerindex, 3, baseangle + i * 1000, 0, x, y, speed, type, color
				}
			)
		end
	end
	
end