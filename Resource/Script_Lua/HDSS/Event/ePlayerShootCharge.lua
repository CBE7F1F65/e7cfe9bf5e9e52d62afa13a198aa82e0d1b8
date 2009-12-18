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
	return true;
end

function ePlayerShootCharge_1_2(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_1_3(playerindex, level, oplayerID, px, py)
	return true;
end
