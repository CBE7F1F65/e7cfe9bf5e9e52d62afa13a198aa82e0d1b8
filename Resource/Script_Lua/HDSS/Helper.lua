function helper_GetActiveGhostOverInfo(playerindex)
	local x = hdss.Get(HDSS_ENX, playerindex);
	local y = hdss.Get(HDSS_ENY, playerindex);
	local angle = hdssAMAP(playerindex, x, y);
	local rank = hdss.Get(HDSS_RANK);
	return x, y, angle, rank;
end

function helper_GetNextEnemyRandom(playerindex)
	local enemyrandom = hdss.Get(HDSS_D, LConst_Desc_EnemyRandom+playerindex);
	local nowline;
	nowline, enemyrandom = RANDT(0, 1599, enemyrandom);
	nowline = math.floor(nowline/100);
	hdssSD(LConst_Desc_EnemyNowLine+playerindex, nowline);
	if nowline >= 4 and nowline < 8 then
		hdssSD(LConst_Desc_EnemyNowLineNum+playerindex, 10);
	else
		hdssSD(LConst_Desc_EnemyNowLineNum+playerindex, 6);
	end
	hdssSD(LConst_Desc_EnemyRandom+playerindex, enemyrandom);
end

helper_EnemyBasicData	=	
{
	{
		{-64,	0,	9000,	-140,	80,	160},
		{LConst_EnemyTypeBig,	LConst_EnemyTypeGreen,	LConst_EnemyTypeRed,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue,	LConst_EnemyTypeBlue},
	},
	{
		{-128,	0,	9000,	-140,	80,	160},
		{LConst_EnemyTypeBig,	LConst_EnemyTypeGreen,	LConst_EnemyTypeRed,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue,	LConst_EnemyTypeBlue},
	},
	{
		{-48,	0,	4500,	100,	70,	200},
		{LConst_EnemyTypeBig,	LConst_EnemyTypeGreen,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue,	LConst_EnemyTypeBlue,	LConst_EnemyTypeBlue,	LConst_EnemyTypeBlue,	LConst_EnemyTypeRed,	LConst_EnemyTypeGreen,	LConst_EnemyTypeBig},
	},
	{
		{-12,	0,	4500,	100,	80,	210},
		{LConst_EnemyTypeBig,	LConst_EnemyTypeGreen,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue,	LConst_EnemyTypeBlue,	LConst_EnemyTypeBlue,	LConst_EnemyTypeBlue,	LConst_EnemyTypeRed,	LConst_EnemyTypeGreen,	LConst_EnemyTypeBig},
	},
	{
		{-128,	480,	-9000,	160,	80,	160},
		{LConst_EnemyTypeBlue,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue,	LConst_EnemyTypeRed},
	},
	{
		{-144,	140,	0,	0,	0,	0},
		{LConst_EnemyTypeBig,	LConst_EnemyTypeGreen,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue},
	},
	{
		{-144,	208,	0,	0,	0,	0},
		{LConst_EnemyTypeBig,	LConst_EnemyTypeGreen,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue},
	},
	{
		{-144,	272,	0,	0,	0,	0},
		{LConst_EnemyTypeBig,	LConst_EnemyTypeGreen,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue,	LConst_EnemyTypeRed,	LConst_EnemyTypeBlue},
	},
}

function helper_GetEnemyBasicData(nowpattern, nowlinenum, nowdirection, playerindex)
	nowpattern = nowpattern + 1;
	local basicdatatable = helper_EnemyBasicData[nowpattern][1];
	local type = helper_EnemyBasicData[nowpattern][2][nowlinenum];
	if type == nil then
		MB(nowpattern, nowlinenum)
	end
	local x = basicdatatable[1];
	local y = basicdatatable[2];
	local startangle = basicdatatable[3];
	local addangle = basicdatatable[4];
	local addtimebegin = basicdatatable[5];
	local addtimeend = basicdatatable[6];
	local life;
	if type == LConst_EnemyTypeBlue then
		life = 20;
	elseif type == LConst_EnemyTypeRed then
		life = 25;
	elseif type == LConst_EnemyTypeGreen then
		life = 30;
	else
		life = 35;
	end
	
	x = x + TotalW / 4;
	
	if nowdirection == 1 then
		x = TotalW / 2 - x;
		startangle = 18000 - startangle;
		addangle = -addangle;
	end
	
	if playerindex == 1 then
		x = x + TotalW / 2;
	end
	
	return type, x, y, startangle, addangle, addtimebegin, addtimeend, life;
	
end

function helper_GetCenterX(playerindex)
	if playerindex == 1 then
		return CenterX_1;
	end
	return CenterX_0;
end

function helper_GetCenterBossX(playerindex)
	if playerindex == 1 then
		return CenterBossX_1;
	end
	return CenterBossX_0;
end

function helper_GetRandomItem(itemid)
	if itemid == nil then
		itemid = RANDT(0, 3);
	end
	local ret = math.pow(16, itemid);
	return ret;
end

function helper_GetRandomItemNext(randomitem)
	local itemid = 0;
	for i=0, 2 do
		if math.pow(16, i) == randomitem then
			itemid = i+1;
			break;
		end
	end
	return helper_GetRandomItem(itemid);
end