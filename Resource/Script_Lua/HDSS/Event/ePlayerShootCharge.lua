function _ePlayerShootCharge_CheckBoss(playerindex)
	local eni, bosseni = hdss.Get(HDSS_ENI, playerindex);
	if bosseni == 0xff then
		hdssEA_FADEOUT(playerindex, 0);
		return true;
	end
	return false;
end

function ePlayerShootCharge_00_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex) * 2 - px;
	local y = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_00_1, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_00_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex) * 2 - px;
	local y = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_00_2, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_00_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_00_3, playerindex, x, y, 9000, 0, oplayerID, 1400, 0, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	hdssBGSETUP(playerindex, LConst_bgset_spellid, oplayerID+LConst_SceneSpellOffset, true);
	return true;
end


function ePlayerShootCharge_01_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	if px > x then
		x = x - CenterW/2;
	else
		x = x + CenterW/2;
	end
	local y = 0;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_01_1, playerindex, x, y, 9000, 6.0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_01_2(playerindex, level, oplayerID, px, py)
	local leftx = helper_GetCenterX(playerindex) - CenterW/2;
	local y = 0;
	for i=0, 1 do
		local x = leftx + i * CenterW;
		hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
		hdssEB(CC_ShootChargeEnemyEID_01_2, playerindex, x, y, 9000, 6.0, LConst_EnemyTypeNull, 10);
		hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
		hdssENSAIM(playerindex, level);
	end
	return true;
end

function ePlayerShootCharge_01_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_01_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	hdssBGSETUP(playerindex, LConst_bgset_spellid, oplayerID+LConst_SceneSpellOffset, true);
	return true;
end

function ePlayerShootCharge_02_1(playerindex, level, oplayerID, px, py)
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, px, py, LConst_ShootCharge_EnemyDelay);
	local opx = hdss.Get(HDSS_PX, 1-playerindex);
	local opy = hdss.Get(HDSS_PY, 1-playerindex);
	hdssEB(CC_ShootChargeEnemyEID_02_1, 1-playerindex, opx, opy, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(1-playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(1-playerindex, level);
	return true;
end

function ePlayerShootCharge_02_2(playerindex, level, oplayerID, px, py)
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, px, py, LConst_ShootCharge_EnemyDelay);
	local opx = hdss.Get(HDSS_PX, 1-playerindex);
	local opy = hdss.Get(HDSS_PY, 1-playerindex);
	hdssEB(CC_ShootChargeEnemyEID_02_2, 1-playerindex, opx, opy, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(1-playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(1-playerindex, level);
	return true;
end

function ePlayerShootCharge_02_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_02_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	hdssBGSETUP(playerindex, LConst_bgset_spellid, oplayerID+LConst_SceneSpellOffset, true);
	return true;
end

function ePlayerShootCharge_03_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	if x > px then
		x = x + CenterW / 2;
	else
		x = x - CenterW / 2;
	end
	local y = 0;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_03_1, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_03_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	if x > px then
		x = x + CenterW / 2;
	else
		x = x - CenterW / 2;
	end
	local y = 0;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_03_2, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_03_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_03_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	hdssBGSETUP(playerindex, LConst_bgset_spellid, oplayerID+LConst_SceneSpellOffset, true);
	return true;
end

function ePlayerShootCharge_04_1(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_04_2(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_04_3(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_05_1(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_05_2(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_05_3(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_06_1(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_06_2(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_06_3(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_07_1(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_07_2(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_07_3(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_08_1(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_08_2(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_08_3(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_09_1(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_09_2(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_09_3(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_10_1(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_10_2(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_10_3(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_11_1(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_11_2(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_11_3(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_12_1(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_12_2(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_12_3(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_13_1(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_13_2(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_13_3(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_14_1(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_14_2(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_14_3(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_15_1(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_15_2(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_15_3(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_16_1(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_16_2(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_16_3(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_17_1(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_17_2(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_17_3(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_18_1(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_18_2(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_18_3(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_19_1(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_19_2(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_19_3(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_20_1(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_20_2(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_20_3(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_21_1(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_21_2(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_21_3(playerindex, level, oplayerID, px, py)
	return true;
end

function ePlayerShootCharge_22_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex) * 2 - px;
	local y = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_22_1, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_22_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex) * 2 - px;
	local y = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_22_2, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_22_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_22_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	hdssBGSETUP(playerindex, LConst_bgset_spellid, oplayerID+LConst_SceneSpellOffset, true);
	return true;
end

--

function ePlayerShootChargeOne_00(playerindex, oplayerID, opx, opy)
	return true;
end

function ePlayerShootChargeOne_01(playerindex, oplayerID, opx, opy)
	return true;
end

function ePlayerShootChargeOne_02(playerindex, oplayerID, opx, opy)
	return true;
end

function ePlayerShootChargeOne_03(playerindex, oplayerID, opx, opy)
	hdssSE(CC_SE_Slash, opx);
	hdssEFFSETUP(playerindex, LConst_effid_youmuslash, opx, opy-25, 32);
	hdss.Call(HDSS_EZONEBUILD,
		{
			EZONETYPE_BULLETFADEOUT+EZONETYPE_ENEMYDAMAGE, playerindex, opx, opy-33,
			18, 16, 15
		}
	)
	hdss.Call(HDSS_EZONEBUILD,
		{
			EZONETYPE_BULLETFADEOUT+EZONETYPE_ENEMYDAMAGE, playerindex, opx+16, opy-33,
			18, 12, 7
		}
	)
	hdss.Call(HDSS_EZONEBUILD,
		{
			EZONETYPE_BULLETFADEOUT+EZONETYPE_ENEMYDAMAGE, playerindex, opx-16, opy-33,
			18, 12, 7
		}
	)
	hdss.Call(HDSS_EZONEBUILD,
		{
			EZONETYPE_BULLETFADEOUT+EZONETYPE_ENEMYDAMAGE, playerindex, opx+28, opy-33,
			18, 12, 7
		}
	)
	hdss.Call(HDSS_EZONEBUILD,
		{
			EZONETYPE_BULLETFADEOUT+EZONETYPE_ENEMYDAMAGE, playerindex, opx-28, opy-33,
			18, 12, 7
		}
	)
	hdss.Call(HDSS_EZONEBUILD,
		{
			EZONETYPE_PLAYERSPEED, playerindex, opx, opy,
			18, EVENTZONE_OVERZONE, 0.2
		}
	)
	return true;
end

function ePlayerShootChargeOne_04(playerindex, oplayerID, opx, opy)
	return true;
end

function ePlayerShootChargeOne_05(playerindex, oplayerID, opx, opy)
	return true;
end

function ePlayerShootChargeOne_06(playerindex, oplayerID, opx, opy)
	return true;
end

function ePlayerShootChargeOne_07(playerindex, oplayerID, opx, opy)
	return true;
end

function ePlayerShootChargeOne_08(playerindex, oplayerID, opx, opy)
	return true;
end

function ePlayerShootChargeOne_09(playerindex, oplayerID, opx, opy)
	return true;
end

function ePlayerShootChargeOne_10(playerindex, oplayerID, opx, opy)
	return true;
end

function ePlayerShootChargeOne_11(playerindex, oplayerID, opx, opy)
	return true;
end

function ePlayerShootChargeOne_12(playerindex, oplayerID, opx, opy)
	return true;
end

function ePlayerShootChargeOne_13(playerindex, oplayerID, opx, opy)
	return true;
end

function ePlayerShootChargeOne_14(playerindex, oplayerID, opx, opy)
	return true;
end

function ePlayerShootChargeOne_15(playerindex, oplayerID, opx, opy)
	return true;
end

function ePlayerShootChargeOne_16(playerindex, oplayerID, opx, opy)
	return true;
end

function ePlayerShootChargeOne_17(playerindex, oplayerID, opx, opy)
	return true;
end

function ePlayerShootChargeOne_18(playerindex, oplayerID, opx, opy)
	return true;
end

function ePlayerShootChargeOne_19(playerindex, oplayerID, opx, opy)
	return true;
end

function ePlayerShootChargeOne_20(playerindex, oplayerID, opx, opy)
	return true;
end

function ePlayerShootChargeOne_21(playerindex, oplayerID, opx, opy)
	return true;
end

function ePlayerShootChargeOne_22(playerindex, oplayerID, opx, opy)
	return true;
end