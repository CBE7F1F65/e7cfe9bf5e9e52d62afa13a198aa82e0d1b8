function ePlayerShootCharge_0_1(playerindex, level, oplayerID, px, py)
	local x = LGlobal_GetCenterX(playerindex) * 2 - px;
	local y = 144;
	hdss.Call(
		HDSS_EB,
		{
			CC_ShootChargeEnemyEID_0_1, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10, 0
		}
	)
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_0_2(playerindex, level, oplayerID, px, py)
	local x = LGlobal_GetCenterX(playerindex) * 2 - px;
	local y = 144;
	hdss.Call(
		HDSS_EB,
		{
			CC_ShootChargeEnemyEID_0_2, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10, 0
		}
	)
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_0_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdss.Call(
		HDSS_EB,
		{
			CC_ShootChargeEnemyEID_0_3, playerindex, x, y, 9000, 0, oplayerID, 1400, 0
		}
	)
	hdssENSAIM(playerindex, level);
	return true;
end


function ePlayerShootCharge_1_1(playerindex, level, oplayerID, px, py)
	local x = LGlobal_GetCenterX(playerindex);
	if px > x then
		x = x - CenterW/2;
	else
		x = x + CenterW/2;
	end
	local y = 0;
	hdss.Call(
		HDSS_EB,
		{
			CC_ShootChargeEnemyEID_1_1, playerindex, x, y, 9000, 6.0, LConst_EnemyTypeNull, 10, 0
		}
	)
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_1_2(playerindex, level, oplayerID, px, py)
	local leftx = LGlobal_GetCenterX(playerindex) - CenterW/2;
	local y = 0;
	for i=0, 1 do
		hdss.Call(
			HDSS_EB,
			{
				CC_ShootChargeEnemyEID_1_2, playerindex, leftx + i * CenterW, y, 9000, 6.0, LConst_EnemyTypeNull, 10, 0
			}
		)
		hdssENSAIM(playerindex, level);
	end
	return true;
end

function ePlayerShootCharge_1_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdss.Call(
		HDSS_EB,
		{
			CC_ShootChargeEnemyEID_1_3, playerindex, x, y, 9000, 0, oplayerID, 1400, 0
		}
	)
	hdssENSAIM(playerindex, level);
	return true;
end
