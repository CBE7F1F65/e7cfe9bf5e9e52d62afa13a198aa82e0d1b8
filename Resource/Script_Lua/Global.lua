MB	=	global.MessageBox;
LOG	=	hge.System_Log;

function LGlobal_GetCenterX(playerindex)
	if playerindex == 1 then
		return CenterX_1;
	end
	return CenterX_0;
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