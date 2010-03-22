LGlobal_MessageBoxCount	=	{}

_DEBUG_LGlobal_Jump	=	-1;

function LGlobal_CallMessageBoxOnce(content, title, indi)
	if indi == nil then
		indi = 1;
	end
	if LGlobal_MessageBoxCount[indi] == nil or hge.Input_GetDIKey(DIK_DELETE, DIKEY_DOWN) then
		LGlobal_MessageBoxCount[indi] = 0;
	end
	if LGlobal_MessageBoxCount[indi] > 0 then
		return 0;
	end
	LGlobal_MessageBoxCount[indi] = LGlobal_MessageBoxCount[indi] + 1;
	return LGlobal_CallMessageBox(content, title);
end

function LGlobal_TranslateStringType(str)
	if str == nil then
		str = "nil";
	elseif str == true then
		str = "true";
	elseif str == false then
		str = "false";
	end
	return str;
end

function LGlobal_CallMessageBox(content, title)
	content = LGlobal_TranslateStringType(content);
	title = LGlobal_TranslateStringType(title);
	return global.MessageBox(content, title);
end

MB	=	LGlobal_CallMessageBoxOnce;
MBA	=	LGlobal_CallMessageBox;
LOG	=	hge.System_Log;

RANDT	=	game.Random_Int;
RANDTF	=	game.Random_Float;

LTable_ePlayerDrainFunction = 
{
	{0,	ePlayerDrain_00},
	{1,	ePlayerDrain_01},
	{2,	ePlayerDrain_02},
	{3,	ePlayerDrain_03},
	{4,	ePlayerDrain_04},
	{5,	ePlayerDrain_05},
	{6,	ePlayerDrain_06},
	{7,	ePlayerDrain_07},
	{8,	ePlayerDrain_08},
	{9,	ePlayerDrain_09},
	{10,	ePlayerDrain_10},
	{11,	ePlayerDrain_11},
	{12,	ePlayerDrain_12},
	{13,	ePlayerDrain_13},
	{14,	ePlayerDrain_14},
	{15,	ePlayerDrain_15},
	{16,	ePlayerDrain_16},
	{17,	ePlayerDrain_17},
	{18,	ePlayerDrain_18},
	{19,	ePlayerDrain_19},
	{20,	ePlayerDrain_20},
	{21,	ePlayerDrain_21},
	{22,	ePlayerDrain_22},
}

LTable_ePlayerShotFunction = 
{
	{0,	ePlayerShot_00},
	{1,	ePlayerShot_01},
	{2,	ePlayerShot_02},
	{3,	ePlayerShot_03},
	{4,	ePlayerShot_04},
	{5,	ePlayerShot_05},
	{6,	ePlayerShot_06},
	{7,	ePlayerShot_07},
	{8,	ePlayerShot_08},
	{9,	ePlayerShot_09},
	{10,	ePlayerShot_10},
	{11,	ePlayerShot_11},
	{12,	ePlayerShot_12},
	{13,	ePlayerShot_13},
	{14,	ePlayerShot_14},
	{15,	ePlayerShot_15},
	{16,	ePlayerShot_16},
	{17,	ePlayerShot_17},
	{18,	ePlayerShot_18},
	{19,	ePlayerShot_19},
	{20,	ePlayerShot_20},
	{21,	ePlayerShot_21},
	{22,	ePlayerShot_22},
}

LTable_ePlayerSendExFunction = 
{
	{0,	ePlayerSendEx_00},
	{1,	ePlayerSendEx_01},
	{2,	ePlayerSendEx_02},
	{3,	ePlayerSendEx_03},
	{4,	ePlayerSendEx_04},
	{5,	ePlayerSendEx_05},
	{6,	ePlayerSendEx_06},
	{7,	ePlayerSendEx_07},
	{8,	ePlayerSendEx_08},
	{9,	ePlayerSendEx_09},
	{10,	ePlayerSendEx_10},
	{11,	ePlayerSendEx_11},
	{12,	ePlayerSendEx_12},
	{13,	ePlayerSendEx_13},
	{14,	ePlayerSendEx_14},
	{15,	ePlayerSendEx_15},
	{16,	ePlayerSendEx_16},
	{17,	ePlayerSendEx_17},
	{18,	ePlayerSendEx_18},
	{19,	ePlayerSendEx_19},
	{20,	ePlayerSendEx_20},
	{21,	ePlayerSendEx_21},
	{22,	ePlayerSendEx_22},
}

LTable_eActiveGhostOverFunction = 
{
	{0,	eActiveGhostOver_00},
	{1,	eActiveGhostOver_01},
	{2,	eActiveGhostOver_02},
	{3,	eActiveGhostOver_03},
	{4,	eActiveGhostOver_04},
	{5,	eActiveGhostOver_05},
	{6,	eActiveGhostOver_06},
	{7,	eActiveGhostOver_07},
	{8,	eActiveGhostOver_08},
	{9,	eActiveGhostOver_09},
	{10,	eActiveGhostOver_10},
	{11,	eActiveGhostOver_11},
	{12,	eActiveGhostOver_12},
	{13,	eActiveGhostOver_13},
	{14,	eActiveGhostOver_14},
	{15,	eActiveGhostOver_15},
	{16,	eActiveGhostOver_16},
	{17,	eActiveGhostOver_17},
	{18,	eActiveGhostOver_18},
	{19,	eActiveGhostOver_19},
	{20,	eActiveGhostOver_20},
	{21,	eActiveGhostOver_21},
	{22,	eActiveGhostOver_22},
}

LTable_ePlayerSendExChaseFunction	=
{
	{0,	ePlayerSendExChase_00},
	{1,	ePlayerSendExChase_01},
	{2,	ePlayerSendExChase_02},
	{3,	ePlayerSendExChase_03},
	{4,	ePlayerSendExChase_04},
	{5,	ePlayerSendExChase_05},
	{6,	ePlayerSendExChase_06},
	{7,	ePlayerSendExChase_07},
	{8,	ePlayerSendExChase_08},
	{9,	ePlayerSendExChase_09},
	{10,	ePlayerSendExChase_10},
	{11,	ePlayerSendExChase_11},
	{12,	ePlayerSendExChase_12},
	{13,	ePlayerSendExChase_13},
	{14,	ePlayerSendExChase_14},
	{15,	ePlayerSendExChase_15},
	{16,	ePlayerSendExChase_16},
	{17,	ePlayerSendExChase_17},
	{18,	ePlayerSendExChase_18},
	{19,	ePlayerSendExChase_19},
	{20,	ePlayerSendExChase_20},
	{21,	ePlayerSendExChase_21},
	{22,	ePlayerSendExChase_22},
}

LTable_ePlayerShootChargeFunction	=
{	
	{0,	1,	ePlayerShootCharge_00_1},
	{0,	2,	ePlayerShootCharge_00_2},
	{0,	3,	ePlayerShootCharge_00_3},
	{1,	1,	ePlayerShootCharge_01_1},
	{1,	2,	ePlayerShootCharge_01_2},
	{1,	3,	ePlayerShootCharge_01_3},
	{2,	1,	ePlayerShootCharge_02_1},
	{2,	2,	ePlayerShootCharge_02_2},
	{2,	3,	ePlayerShootCharge_02_3},
	{3,	1,	ePlayerShootCharge_03_1},
	{3,	2,	ePlayerShootCharge_03_2},
	{3,	3,	ePlayerShootCharge_03_3},
	{4,	1,	ePlayerShootCharge_04_1},
	{4,	2,	ePlayerShootCharge_04_2},
	{4,	3,	ePlayerShootCharge_04_3},
	{5,	1,	ePlayerShootCharge_05_1},
	{5,	2,	ePlayerShootCharge_05_2},
	{5,	3,	ePlayerShootCharge_05_3},
	{6,	1,	ePlayerShootCharge_06_1},
	{6,	2,	ePlayerShootCharge_06_2},
	{6,	3,	ePlayerShootCharge_06_3},
	{7,	1,	ePlayerShootCharge_07_1},
	{7,	2,	ePlayerShootCharge_07_2},
	{7,	3,	ePlayerShootCharge_07_3},
	{8,	1,	ePlayerShootCharge_08_1},
	{8,	2,	ePlayerShootCharge_08_2},
	{8,	3,	ePlayerShootCharge_08_3},
	{9,	1,	ePlayerShootCharge_09_1},
	{9,	2,	ePlayerShootCharge_09_2},
	{9,	3,	ePlayerShootCharge_09_3},
	{10,	1,	ePlayerShootCharge_10_1},
	{10,	2,	ePlayerShootCharge_10_2},
	{10,	3,	ePlayerShootCharge_10_3},
	{11,	1,	ePlayerShootCharge_11_1},
	{11,	2,	ePlayerShootCharge_11_2},
	{11,	3,	ePlayerShootCharge_11_3},
	{12,	1,	ePlayerShootCharge_12_1},
	{12,	2,	ePlayerShootCharge_12_2},
	{12,	3,	ePlayerShootCharge_12_3},
	{13,	1,	ePlayerShootCharge_13_1},
	{13,	2,	ePlayerShootCharge_13_2},
	{13,	3,	ePlayerShootCharge_13_3},
	{14,	1,	ePlayerShootCharge_14_1},
	{14,	2,	ePlayerShootCharge_14_2},
	{14,	3,	ePlayerShootCharge_14_3},
	{15,	1,	ePlayerShootCharge_15_1},
	{15,	2,	ePlayerShootCharge_15_2},
	{15,	3,	ePlayerShootCharge_15_3},
	{16,	1,	ePlayerShootCharge_16_1},
	{16,	2,	ePlayerShootCharge_16_2},
	{16,	3,	ePlayerShootCharge_16_3},
	{17,	1,	ePlayerShootCharge_17_1},
	{17,	2,	ePlayerShootCharge_17_2},
	{17,	3,	ePlayerShootCharge_17_3},
	{18,	1,	ePlayerShootCharge_18_1},
	{18,	2,	ePlayerShootCharge_18_2},
	{18,	3,	ePlayerShootCharge_18_3},
	{19,	1,	ePlayerShootCharge_19_1},
	{19,	2,	ePlayerShootCharge_19_2},
	{19,	3,	ePlayerShootCharge_19_3},
	{20,	1,	ePlayerShootCharge_20_1},
	{20,	2,	ePlayerShootCharge_20_2},
	{20,	3,	ePlayerShootCharge_20_3},
	{21,	1,	ePlayerShootCharge_21_1},
	{21,	2,	ePlayerShootCharge_21_2},
	{21,	3,	ePlayerShootCharge_21_3},
	{22,	1,	ePlayerShootCharge_22_1},
	{22,	2,	ePlayerShootCharge_22_2},
	{22,	3,	ePlayerShootCharge_22_3},
}

LTable_ePlayerShootChargeOneFunction	=	
{
	{0,	ePlayerShootChargeOne_00},
	{1,	ePlayerShootChargeOne_01},
	{2,	ePlayerShootChargeOne_02},
	{3,	ePlayerShootChargeOne_03},
	{4,	ePlayerShootChargeOne_04},
	{5,	ePlayerShootChargeOne_05},
	{6,	ePlayerShootChargeOne_06},
	{7,	ePlayerShootChargeOne_07},
	{8,	ePlayerShootChargeOne_08},
	{9,	ePlayerShootChargeOne_09},
	{10,	ePlayerShootChargeOne_10},
	{11,	ePlayerShootChargeOne_11},
	{12,	ePlayerShootChargeOne_12},
	{13,	ePlayerShootChargeOne_13},
	{14,	ePlayerShootChargeOne_14},
	{15,	ePlayerShootChargeOne_15},
	{16,	ePlayerShootChargeOne_16},
	{17,	ePlayerShootChargeOne_17},
	{18,	ePlayerShootChargeOne_18},
	{19,	ePlayerShootChargeOne_19},
	{20,	ePlayerShootChargeOne_20},
	{21,	ePlayerShootChargeOne_21},
	{22,	ePlayerShootChargeOne_22},
}