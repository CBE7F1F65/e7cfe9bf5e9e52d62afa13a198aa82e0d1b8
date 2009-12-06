function helper_GetActiveGhostOverInfo(playerindex)
	local x = hdss.Get(HDSS_ENX, playerindex);
	local y = hdss.Get(HDSS_ENY, playerindex);
	local angle = hdssAMAP(playerindex, x, y);
	local rank = hdss.Get(HDSS_RANK);
	return x, y, angle, rank;
end

function helper_GetCenterX(playerindex)
	if playerindex == 1 then
		return CenterX_1;
	else
		return CenterX_0;
	end
end