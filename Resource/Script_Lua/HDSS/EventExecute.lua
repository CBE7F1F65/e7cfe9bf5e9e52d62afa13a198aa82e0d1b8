function _EventExecute_PlayerDrain(etype, playerindex)
	local playerID, x, y, draintimer, type = game.GetPlayerDrainInfo(playerindex, etype);
	for i, it in pairs(LTable_ePlayerDrainFunction) do
		if it[1] == playerID then
			return it[2](playerindex, x, y, draintimer, type);
		end
	end
end

function _EventExecute_PlayerShot(playerindex)
	local playerID, nLife, shottimer, shotdelay, nchargemax = game.GetPlayerShotInfo(playerindex);
	for i, it in pairs(LTable_ePlayerShotFunction) do
		if it[1] == playerID then
			return it[2](playerindex, playerID, nLife, shottimer, shotdelay, nchargemax);
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

function _EventExecute_PlayerInSpellStop(playerindex)
	local bSpell, spellPlayerID, oplayerID, stoptimer, stopmaxtime, spellClass, spellLevel = game.GetPlayerStopInfo(playerindex);
	if bSpell ~= nil then
		return ePlayerInSpellStop(playerindex, bSpell, spellPlayerID, oplayerID, stoptimer, stopmaxtime, spellClass, spellLevel);
	end
	return false;
end

function _EventExecute_PlayerInStop(playerindex)
	local playerID = hdss.Get(HDSS_CHARA, playerindex);
	return ePlayerInStop(playerindex, playerID);
end

function _EventExecute_PlayerShootCharge(playerindex)
	local charge, level, oplayerID, px, py, opx, opy, playerID = game.GetPlayerShootChargeInfo(playerindex);
	if charge > 3 then
		charge = 3;
	end
		
	local col = {global.ARGB(0x80, 0x808080), global.ARGB(0x80, 0xff0000)};
	for i=0, 1 do
		hdssBGVALUE(i, LConst_gamefg_spellflashid, SI_White, helper_GetCenterX(i), TotalH/2, TotalW/2, TotalH, col[i+1]);
	end
	
	for i, it in pairs(LTable_ePlayerShootChargeFunction) do
		if it[1] == oplayerID then
			if it[2] == charge then
				if charge == 3 then
					local enindex, bossindex = hdss.Get(HDSS_ENI, playerindex);
					if bossindex ~= 0xff then
						hdssENTOI(playerindex, bossindex);
						hdssEA_FADEOUT(playerindex, -1);
						hdssENTOI(playerindex, enindex);
					end
				end
				return it[3](1-playerindex, level, oplayerID, px, py, opx, opy, playerID);
			end
		end
	end
	return true;
end

function _EventExecute_PlayerShootChargeOne(playerindex)
	local oplayerID = hdss.Get(HDSS_CHARA, playerindex);
	local opx = hdss.Get(HDSS_PX, playerindex);
	local opy = hdss.Get(HDSS_PY, playerindex);
	for i, it in pairs(LTable_ePlayerShootChargeOneFunction) do
		if it[1] == oplayerID then
			return it[2](playerindex, oplayerID, opx, opy);
		end
	end
end

function _EventExecute_PlayerSendEx(playerindex)
	local esindex, playerID, opx, opy, px, py, oplayerID, x, y = game.GetPlayerSendExInfo(playerindex);
	for i, it in pairs(LTable_ePlayerSendExFunction) do
		if it[1] == playerID then
			return it[2](esindex, playerindex, playerID, opx, opy, px, py, oplayerID, x, y);
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

function _EventExecute_PlayerSendLily(rank)
	hdssSE(SE_BOSS_WARNING);
	local randomitem = helper_GetRandomItem();
	local lastitem = hdss.Get(HDSS_D, LConst_Desc_LilyItem);
	if randomitem == lastitem then
		randomitem = helper_GetRandomItemNext(randomitem);
	end
	hdssSD(LConst_Desc_LilyItem, randomitem);
	for i=0, 1 do
		hdssEB(CC_EnemyEID_Lily, i, helper_GetCenterX(i), 0, 9000, 0, LConst_EnemyTypeLiLy, 830, randomitem);
		hdssENSAIM(i, rank);
	end
	return true;
end

function _EventExecute_PlayerSendItemBullet(playerindex)
	local rank = hdss.Get(HDSS_RANK);
	game.SendItemBullet(playerindex, 16+rank);
end

function _EventExecute_BossFadeout(playerindex)
	hdssBGSETUP(playerindex, LConst_bgset_spellid, BGLAYERSET_NONE);
end

function EventExecute(name, con)

	if name == EVENT_EFFSPCHASE then
		return _EventExecute_EffspChase(con);
	elseif name == EVENT_PLAYERDRAIN or name == EVENT_PLAYERDRAINCHECK then
		return _EventExecute_PlayerDrain(name, con);
	elseif name == EVENT_PLAYERSHOT then
		return _EventExecute_PlayerShot(con);
	elseif name == EVENT_PLAYERINSPELLSTOP then
		return _EventExecute_PlayerInSpellStop(con);
	elseif name == EVENT_PLAYERSHOOTCHARGE then
		return _EventExecute_PlayerShootCharge(con);
	elseif name == EVENT_PLAYERSHOOTCHARGEONE then
		return _EventExecute_PlayerShootChargeOne(con);
	elseif name == EVENT_BOSSFADEOUT then
		return _EventExecute_BossFadeout(con);
	elseif name == EVENT_PLAYERSENDEX then
		return _EventExecute_PlayerSendEx(con);
	elseif name == EVENT_ACTIVEGHOSTOVER then
		return _EventExecute_ActiveGhostOver(con);
	elseif name == EVENT_PLAYERSENDLILY then
		return _EventExecute_PlayerSendLily(con);
	elseif name == EVENT_PLAYERSENDITEMBULLET then
		return _EventExecute_PlayerSendItemBullet(con);
	elseif name == EVENT_PLAYERINSTOP then
		return _EventExecute_PlayerInStop(con);
	end
	return true;

end