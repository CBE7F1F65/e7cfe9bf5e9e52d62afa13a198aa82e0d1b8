LTable_EnemyEIDFunction	=	
{
	{CC_ShootChargeEnemyEID_0_1, Edef_ShootChargeEnemyEID_0_1},
	{CC_ShootChargeEnemyEID_0_2, Edef_ShootChargeEnemyEID_0_2},
	{CC_ShootChargeEnemyEID_0_3, Edef_ShootChargeEnemyEID_0_3},
	{CC_ShootChargeEnemyEID_0_3_B, Edef_ShootChargeEnemyEID_0_3_B},
	{CC_ShootChargeEnemyEID_0_3_E, Edef_ShootChargeEnemyEID_0_3_E},
	{CC_ShootChargeEnemyEID_1_1, Edef_ShootChargeEnemyEID_1_1},
	{CC_ShootChargeEnemyEID_1_2, Edef_ShootChargeEnemyEID_1_2},
	{CC_ShootChargeEnemyEID_1_3, Edef_ShootChargeEnemyEID_1_3},
}


function EdefExecute(name, con)

	local playerindex, eID, level, x, y, px, py = game.GetEdefInfo(name);
	for i, it in pairs(LTable_EnemyEIDFunction) do
		if it[1] == eID then
			return it[2](playerindex, level, x, y, con, px, py);
		end
	end
	return true;

end