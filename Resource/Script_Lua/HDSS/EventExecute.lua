function EventExecute(name, con)

	if name == EVENT_EFFSPCHASE then
		local setID, x, y, appendint, appendfloat = game.GetSendItemInfo(con);
		
		if setID == EFFSPCHASE_SENDREDBULLET then
			return eSendRedBullet(con, x, y, appendint, appendfloat, setID, true);
		elseif setID == EFFSPCHASE_SENDBLUEBULLET then
			return eSendBlueBullet(con, x, y, appendint, appendfloat, setID, true);
		elseif setID == EFFSPCHASE_SENDREDBIGBULLET then
			return eSendRedBullet(con, x, y, appendint, appendfloat, setID, false);
		elseif setID == EFFSPCHASE_SENDBLUEBIGBULLET then
			return eSendBlueBullet(con, x, y, appendint, appendfloat, setID, false);
		elseif setID == EFFSPCHASE_SENDITEMBULLET then
			return eSendItemBullet(con, x, y, setID);
		elseif setID == EFFSPCHASE_SENDGHOST then
			return eSendGhost(con, x, y, appendint, appendfloat, setID);
		elseif setID == EFFSPCHASE_SENDEXATTACK then
			return eSendExAttack(con, x, y, appendint, appendfloat, setID);
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
	elseif name == EVENT_PLAYERINSTOP then
		local bSpell, spellPlayerID, oplayerID, stoptimer, stopmaxtime, spellClass, spellLevel = game.GetPlayerStopInfo(con);
		return ePlayerInStop(con, bSpell, spellPlayerID, oplayerID, stoptimer, stopmaxtime, spellClass, spellLevel);
	elseif name == EVENT_PLAYERSHOOTCHARGE then
		hdss.Call(
			HDSS_B,
			{
				1-con, (1-con)*320+160, 0, true, hge.Random_Int(4500, 13500), hge.Random_Float(1.2, 1.4), 10, 2
			}
		)
	elseif name == EVENT_PLAYERSENDEX then
		local esindex, playerID, opx, opy, px, py, oplayerID = game.GetPlayerSendExInfo(con);
		local playerfunctiontable = 
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
		for i, it in pairs(playerfunctiontable) do
			if it[1] == playerID then
				return it[2](esindex, con, playerID, opx, opy, px, py, oplayerID);
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
	elseif name == EVENT_PLAYERSENDLILY then
		hdssSE(SE_BOSS_WARNING);
	end
	return true;

end