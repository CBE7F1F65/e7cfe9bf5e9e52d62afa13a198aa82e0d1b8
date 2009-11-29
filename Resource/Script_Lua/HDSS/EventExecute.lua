function EventExecute(name, con)

	if name == EVENT_EFFSPCHASE then
		local playerindex, x, y = game.GetSendItemInfo();
		if con == EFFSPCHASE_SENDREDBULLET_0 or con == EFFSPCHASE_SENDREDBULLET_1 or con == EFFSPCHASE_SENDREDBULLET_2 then
			return eSendRedBullet(playerindex, x, y, con, true);
		elseif con == EFFSPCHASE_SENDBLUEBULLET_0 or con == EFFSPCHASE_SENDBLUEBULLET_1 or con == EFFSPCHASE_SENDBLUEBULLET_2 then
			return eSendBlueBullet(playerindex, x, y, con, true);
		elseif con == EFFSPCHASE_SENDREDBIGBULLET then
			return eSendRedBullet(playerindex, x, y, con, false);
		elseif con == EFFSPCHASE_SENDBLUEBIGBULLET then
			return eSendBlueBullet(playerindex, x, y, con, false);
		elseif con == EFFSPCHASE_SENDITEMBULLET then
			return eSendItemBullet(playerindex, x, y, con);
		elseif con == EFFSPCHASE_SENDGREENGHOST then
			return eSendGreenGhost(playerindex, x, y, con);
		elseif con == EFFSPCHASE_SENDYELLOWGHOST then
			return eSendYellowGhost(playerindex, x, y, con);
		elseif con == EFFSPCHASE_SENDREDGHOST then
			return eSendRedGhost(playerindex, x, y, con);
		elseif con == EFFSPCHASE_SENDEXATTACK then
			return eSendExAttack(playerindex, x, y, con);
		end
	end
	return true;

end