MB	=	global.MessageBox;
LOG	=	hge.System_Log;

RANDT	=	game.Random_Int;
RANDTF	=	game.Random_Float;

function LGlobal_GetNextEnemyRandom(playerindex)
	local enemyrandom = hdss.Get(HDSS_D, LConst_Desc_EnemyRandom+playerindex);
	local nowline;
	nowline, enemyrandom = RANDT(0, 1599, enemyrandom);
	nowline = math.floor(nowline/100);
	hdssSD(LConst_Desc_EnemyNowLine+playerindex, nowline);
	if nowline >= 4 and nowline < 8 then
		hdssSD(LConst_Desc_EnemyNowLineNum+playerindex, 10);
	else
		hdssSD(LConst_Desc_EnemyNowLineNum+playerindex, 6);
	end
	hdssSD(LConst_Desc_EnemyRandom+playerindex, enemyrandom);
end

LGlobal_EnemyBasicData	=	
{
	{
		{-64,	0,	9000,	-140,	80,	160},
		{LConst_EnemyTypeBig,	LConst_EnemyTypeGreen,	LConst_EnemyTypeRed,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue,	LConst_EnemyTypeBlue},
	},
	{
		{-128,	0,	9000,	-140,	80,	160},
		{LConst_EnemyTypeBig,	LConst_EnemyTypeGreen,	LConst_EnemyTypeRed,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue,	LConst_EnemyTypeBlue},
	},
	{
		{-48,	0,	4500,	100,	70,	200},
		{LConst_EnemyTypeBig,	LConst_EnemyTypeGreen,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue,	LConst_EnemyTypeBlue,	LConst_EnemyTypeBlue,	LConst_EnemyTypeBlue,	LConst_EnemyTypeRed,	LConst_EnemyTypeGreen,	LConst_EnemyTypeBig},
	},
	{
		{-12,	0,	4500,	100,	80,	210},
		{LConst_EnemyTypeBig,	LConst_EnemyTypeGreen,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue,	LConst_EnemyTypeBlue,	LConst_EnemyTypeBlue,	LConst_EnemyTypeBlue,	LConst_EnemyTypeRed,	LConst_EnemyTypeGreen,	LConst_EnemyTypeBig},
	},
	{
		{-128,	480,	-9000,	160,	80,	160},
		{LConst_EnemyTypeBlue,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue,	LConst_EnemyTypeRed},
	},
	{
		{-144,	140,	0,	0,	0,	0},
		{LConst_EnemyTypeBig,	LConst_EnemyTypeGreen,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue},
	},
	{
		{-144,	208,	0,	0,	0,	0},
		{LConst_EnemyTypeBig,	LConst_EnemyTypeGreen,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue},
	},
	{
		{-144,	272,	0,	0,	0,	0},
		{LConst_EnemyTypeBig,	LConst_EnemyTypeGreen,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue},
	},
}

function LGlobal_GetEnemyBasicData(nowpattern, nowlinenum, nowdirection, playerindex)
	nowpattern = nowpattern + 1;
	local basicdatatable = LGlobal_EnemyBasicData[nowpattern][1];
	local type = LGlobal_EnemyBasicData[nowpattern][2][nowlinenum];
	if type == nil then
		MB(nowpattern, nowlinenum)
	end
	local x = basicdatatable[1];
	local y = basicdatatable[2];
	local startangle = basicdatatable[3];
	local addangle = basicdatatable[4];
	local addtimebegin = basicdatatable[5];
	local addtimeend = basicdatatable[6];
	local life;
	if type == LConst_EnemyTypeBlue then
		life = 20;
	elseif type == LConst_EnemyTypeRed then
		life = 25;
	elseif type == LConst_EnemyTypeGreen then
		life = 30;
	else
		life = 35;
	end
	
	x = x + TotalW / 4;
	
	if nowdirection == 1 then
		x = TotalW / 2 - x;
		startangle = 18000 - startangle;
		addangle = -addangle;
	end
	
	if playerindex == 1 then
		x = x + TotalW / 2;
	end
	
	return type, x, y, startangle, addangle, addtimebegin, addtimeend, life;
	
end

function LGlobal_GetCenterX(playerindex)
	if playerindex == 1 then
		return CenterX_1;
	end
	return CenterX_0;
end

function LGlobal_GetCenterBossX(playerindex)
	if playerindex == 1 then
		return CenterBossX_1;
	end
	return CenterBossX_0;
end

function LGlobal_GetRandomItem()
	local ret = math.pow(4, RANDT(0, 3));
	return ret;
end

LTable_ePlayerDrainFunction = 
{
	{0,	ePlayerDrain_0},
	{1,	ePlayerDrain_1},
	{2,	ePlayerDrain_2},
	{3,	ePlayerDrain_3},
	{4,	ePlayerDrain_4},
	{5,	ePlayerDrain_5},
	{6,	ePlayerDrain_6},
	{7,	ePlayerDrain_7},
	{8,	ePlayerDrain_8},
	{9,	ePlayerDrain_9},
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
	{23,	ePlayerDrain_23},
}

LTable_ePlayerSendExFunction = 
{
	{0,	ePlayerSendEx_0},
	{1,	ePlayerSendEx_1},
	{2,	ePlayerSendEx_2},
	{3,	ePlayerSendEx_3},
	{4,	ePlayerSendEx_4},
	{5,	ePlayerSendEx_5},
	{6,	ePlayerSendEx_6},
	{7,	ePlayerSendEx_7},
	{8,	ePlayerSendEx_8},
	{9,	ePlayerSendEx_9},
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
	{0,	eActiveGhostOver_0},
	{1,	eActiveGhostOver_1},
	{2,	eActiveGhostOver_2},
	{3,	eActiveGhostOver_3},
	{4,	eActiveGhostOver_4},
	{5,	eActiveGhostOver_5},
	{6,	eActiveGhostOver_6},
	{7,	eActiveGhostOver_7},
	{8,	eActiveGhostOver_8},
	{9,	eActiveGhostOver_9},
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
	{0,	ePlayerSendExChase_0},
	{1,	ePlayerSendExChase_1},
	{2,	ePlayerSendExChase_2},
	{3,	ePlayerSendExChase_3},
	{4,	ePlayerSendExChase_4},
	{5,	ePlayerSendExChase_5},
	{6,	ePlayerSendExChase_6},
	{7,	ePlayerSendExChase_7},
	{8,	ePlayerSendExChase_8},
	{9,	ePlayerSendExChase_9},
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
	{23,	ePlayerSendExChase_23},
}

LTable_ePlayerShootChargeFunction	=
{	
	{0,	1,	ePlayerShootCharge_0_1},
	{0,	2,	ePlayerShootCharge_0_2},
	{0,	3,	ePlayerShootCharge_0_3},
	{1,	1,	ePlayerShootCharge_1_1},
	{1,	2,	ePlayerShootCharge_1_2},
	{1,	3,	ePlayerShootCharge_1_3},
	{2,	1,	ePlayerShootCharge_2_1},
	{2,	2,	ePlayerShootCharge_2_2},
	{2,	3,	ePlayerShootCharge_2_3},
	{3,	1,	ePlayerShootCharge_3_1},
	{3,	2,	ePlayerShootCharge_3_2},
	{3,	3,	ePlayerShootCharge_3_3},
	{4,	1,	ePlayerShootCharge_4_1},
	{4,	2,	ePlayerShootCharge_4_2},
	{4,	3,	ePlayerShootCharge_4_3},
	{5,	1,	ePlayerShootCharge_5_1},
	{5,	2,	ePlayerShootCharge_5_2},
	{5,	3,	ePlayerShootCharge_5_3},
	{6,	1,	ePlayerShootCharge_6_1},
	{6,	2,	ePlayerShootCharge_6_2},
	{6,	3,	ePlayerShootCharge_6_3},
	{7,	1,	ePlayerShootCharge_7_1},
	{7,	2,	ePlayerShootCharge_7_2},
	{7,	3,	ePlayerShootCharge_7_3},
	{8,	1,	ePlayerShootCharge_8_1},
	{8,	2,	ePlayerShootCharge_8_2},
	{8,	3,	ePlayerShootCharge_8_3},
	{9,	1,	ePlayerShootCharge_9_1},
	{9,	2,	ePlayerShootCharge_9_2},
	{9,	3,	ePlayerShootCharge_9_3},
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