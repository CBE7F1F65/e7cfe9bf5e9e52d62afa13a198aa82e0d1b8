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
		local playerID, x, y, draintimer, type, aimx, aimy = game.GetPlayerDrainInfo(con, name);
		if playerID == 0 then
			return ePlayerDrain_0(con, x, y, draintimer, type, aimx, aimy);
		elseif playerID == 1 then
			return ePlayerDrain_1(con, x, y, draintimer, type, aimx, aimy);
		end
	end
	return true;

end