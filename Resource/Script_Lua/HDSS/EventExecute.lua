function _EventExecute_PlayerDrain(etype, playerindex)
	local playerID, x, y, draintimer, type = game.GetPlayerDrainInfo(playerindex, etype);
	for i, it in pairs(LTable_ePlayerDrainFunction) do
		if it[1] == playerID then
			return it[2](playerindex, x, y, draintimer, type);
		end
	end
end

function _EventExecute_EffspChase(playerindex)
	local setID, x, y, appendint, appendfloat = game.GetSendItemInfo(playerindex);
	
	if setID == EFFSPCHASE_SENDREDBULLET then
		return eSendRedBullet(playerindex, x, y, appendint, appendfloat, setID, true);
	elseif setID == EFFSPCHASE_SENDBLUEBULLET then
		return eSendBlueBullet(playerindex, x, y, appendint, appendfloat, setID, true);
	elseif setID == EFFSPCHASE_SENDREDBIGBULLET then
		return eSendRedBullet(playerindex, x, y, appendint, appendfloat, setID, false);
	elseif setID == EFFSPCHASE_SENDBLUEBIGBULLET then
		return eSendBlueBullet(playerindex, x, y, appendint, appendfloat, setID, false);
	elseif setID == EFFSPCHASE_SENDITEMBULLET then
		return eSendItemBullet(playerindex, x, y, setID);
	elseif setID == EFFSPCHASE_SENDGHOST then
		return eSendGhost(playerindex, x, y, appendint, appendfloat, setID);
	elseif setID == EFFSPCHASE_SENDEXATTACK then
		return eSendExAttack(playerindex, x, y, appendint, appendfloat, setID);
	end
end

function _EventExecute_PlayerInStop(playerindex)
	local bSpell, spellPlayerID, oplayerID, stoptimer, stopmaxtime, spellClass, spellLevel = game.GetPlayerStopInfo(playerindex);
	if bSpell ~= nil then
		return ePlayerInStop(playerindex, bSpell, spellPlayerID, oplayerID, stoptimer, stopmaxtime, spellClass, spellLevel);
	end
	return false;
end

function _EventExecute_PlayerShootCharge(playerindex)
	local charge, level, playerID, opx, opy, px, py, oplayerID = game.GetPlayerShootChargeInfo(playerindex);
	MB(charge, level)
	hdss.Call(
		HDSS_B,
		{
			playerindex, (playerindex)*320+160, 0, true, game.Random_Int(4500, 13500), game.Random_Float(1.2, 1.4), 10, 2
		}
	)
	return true;
end

function _EventExecute_PlayerSendEx(playerindex)
	local esindex, playerID, opx, opy, px, py, oplayerID = game.GetPlayerSendExInfo(playerindex);
	for i, it in pairs(LTable_ePlayerSendExFunction) do
		if it[1] == playerID then
			return it[2](esindex, playerindex, playerID, opx, opy, px, py, oplayerID);
		end
	end
end

function _EventExecute_ActiveGhostOver(playerindex)
	local playerID = hdss.Get(HDSS_CHARA, playerindex);
	for i, it in pairs(LTable_eActiveGhostOverFunction) do
		if it[1] == playerID then
			return it[2](playerindex);
		end
	end
end

function _EventExecute_PlayerSendLily(playerindex)
	hdssSE(SE_BOSS_WARNING);
	return true;
end

function EventExecute(name, con)

	if name == EVENT_EFFSPCHASE then
		return _EventExecute_EffspChase(con);
	elseif name == EVENT_PLAYERDRAIN or name == EVENT_PLAYERDRAINCHECK then
		return _EventExecute_PlayerDrain(name, con);
	elseif name == EVENT_PLAYERINSTOP then
		return _EventExecute_PlayerInStop(con);
	elseif name == EVENT_PLAYERSHOOTCHARGE then
		return _EventExecute_PlayerShootCharge(con);
	elseif name == EVENT_PLAYERSENDEX then
		return _EventExecute_PlayerSendEx(con);
	elseif name == EVENT_ACTIVEGHOSTOVER then
		return _EventExecute_ActiveGhostOver(con);
	elseif name == EVENT_PLAYERSENDLILY then
		return _EventExecute_PlayerSendLily(con);
	end
	return true;

end