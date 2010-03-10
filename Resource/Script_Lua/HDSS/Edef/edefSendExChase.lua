function Edef_SendExChase_00(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_01(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_02(playerindex, rank, x, y, timer, px, py)
	
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 60);
	elseif math.mod(timer, 12) == 0 then
		local angle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local speed = 1.5 + rank * 0.05;
		hdssB(playerindex, x, y, angle, speed, CC_Bullet_FakeKnife, 3);
		hdssA(1-playerindex, 
			{
				TIMERLESS, 240, REMAIN
			}
		);
		hdssB(1-playerindex, x, y, angle, speed, CC_Bullet_Knife, 3);
		hdssA(1-playerindex);
	end
	
	return true;
end

function Edef_SendExChase_03(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_04(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_05(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_06(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_07(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_08(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_09(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_10(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_11(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_12(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_13(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_14(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_15(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_16(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_17(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_18(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_19(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_20(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_21(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_22(playerindex, rank, x, y, timer, px, py)
	return true;
end