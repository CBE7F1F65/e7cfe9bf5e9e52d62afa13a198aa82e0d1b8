function EventExecute(name, con)

	if name == EVENT_EFFSPCHASE then
		local playerindex, x, y = game.GetSendItemInfo();
		if con == EFFSPCHASE_SENDREDBULLET then
			return eSendRedBullet(playerindex, x, y);
		elseif con == EFFSPCHASE_SENDBLUEBULLET then
			return eSendBlueBullet(playerindex, x, y);
		elseif con == EFFSPCHASE_SENDEXBULLET then
			return eSendExBullet(playerindex, x, y);
		elseif con == EFFSPCHASE_SENDITEMBULLET then
			return eSendItemBullet(playerindex, x, y);
		elseif con == EFFSPCHASE_SENDGREENGHOST then
			return eSendGreenGhost(playerindex, x, y);
		elseif con == EFFSPCHASE_SENDYELLOWGHOST then
			return eSendYellowGhost(playerindex, x, y);
		elseif con == EFFSPCHASE_SENDREDGHOST then
			return eSendRedGhost(playerindex, x, y);
		elseif con == EFFSPCHASE_SENDEXATTACK then
			return eSendExAttack(playerindex, x, y);
		end
	end
	return true;

end