function EventExecute(name, con)

	if name == EVENT_EFFSPCHASE then
		local playerindex, x, y, sendtime, speed = game.GetSendItemInfo();
		
		if con == EFFSPCHASE_SENDREDBULLET then
			return eSendRedBullet(playerindex, x, y, sendtime, speed, con, true);
		elseif con == EFFSPCHASE_SENDBLUEBULLET then
			return eSendBlueBullet(playerindex, x, y, sendtime, speed, con, true);
		elseif con == EFFSPCHASE_SENDREDBIGBULLET then
			return eSendRedBullet(playerindex, x, y, sendtime, speed, con, false);
		elseif con == EFFSPCHASE_SENDBLUEBIGBULLET then
			return eSendBlueBullet(playerindex, x, y, sendtime, speed, con, false);
		elseif con == EFFSPCHASE_SENDITEMBULLET then
			return eSendItemBullet(playerindex, x, y, con);
		elseif con == EFFSPCHASE_SENDGHOST then
			return eSendGhost(playerindex, x, y, sendtime, speed, con);
		elseif con == EFFSPCHASE_SENDEXATTACK then
			return eSendExAttack(playerindex, x, y, con);
		end
	elseif name == EVENT_PLAYERDRAIN or name == EVENT_PLAYERDRAINCHECK then
		local playerID, x, y, draintimer, type = game.GetPlayerDrainInfo(con, name);
		local playerfunctiontable = 
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
		for i, it in pairs(playerfunctiontable) do
			if it[1] == playerID then
				return it[2](con, x, y, draintimer, type);
			end
		end
	elseif name == EVENT_ACTIVEGHOSTOVER then
		local playerID = hdss.Get(HDSS_CHARA, playerindex);
		local playerfunctiontable = 
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
		for i, it in pairs(playerfunctiontable) do
			if it[1] == playerID then
				return it[2](con);
			end
		end
	end
	return true;

end