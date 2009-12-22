function Edef_Lily(playerindex, rank, x, y, timer, px, py)
	local actiontime = (40-rank) * 4;
	if timer == 1 then
		hdssEA(playerindex, ENAC_CHASEAIM_XYSOAOCO,
			{
				x, CenterY+40, 1.0
			},
			{
				-9000, 0, actiontime
			}
		)
	elseif timer > actiontime then
		if math.mod(timer, 4) == 1 then
			local oneset =  math.mod(timer-actiontime, 12);
			local angle = (timer-actiontime) * 231 - 9000 - oneset * 47;
			local speed = rank * 0.04 + 1.8 - oneset * 0.05;
			for i=0, 2 do
				hdss.Call(
					HDSS_B,
					{
						playerindex, x, y, true, angle, speed, CC_Bullet_Ring, 2
					}
				)
				hdss.Call(
					HDSS_B,
					{
						playerindex, x, y, true, 18000-angle, speed, CC_Bullet_Ring, 5
					}
				)
				hdss.Call(
					HDSS_B,
					{
						playerindex, x, y, true, angle+1000, speed+0.3, CC_Bullet_SmallBall, 2
					}
				)
				hdss.Call(
					HDSS_B,
					{
						playerindex, x, y, true, 18000-angle-1000, speed+0.3, CC_Bullet_SmallBall, 5
					}
				)
				angle = angle + 3000;
				speed = speed + 0.5
			end
		end
	end
	return true;
end