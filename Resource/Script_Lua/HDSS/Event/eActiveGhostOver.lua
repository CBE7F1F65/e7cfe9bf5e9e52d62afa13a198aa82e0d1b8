function _eActiveGhostOver_Send3(playerindex)
	local x, y, angle, rank = helper_GetActiveGhostOverInfo(playerindex);
	local speed = 1 + rank * 0.1;
	for i=-1, 1 do
		hdss.Call(
			HDSS_B,
			{
				playerindex, x, y, true, angle + i * 900, speed, 2, 2
			}
		)
	end
end

function eActiveGhostOver_0(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_1(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end
