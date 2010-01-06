LTable_PlayerWinLoseChat	=	
{				
	{0,	0,	"約束通り、お賽銭もらったわよ。",	"これはシャレになれないわね。"},
	{1,	0,	"もう終わり？大したことじゃなかったぜ。",	"も、もう一回勝負しろ！"},
	{2,	0,	"私はいつも本気です。",	"負けてしまいました。"},
	{3,	0,	"winner",	"loser"},
	{4,	0,	"winner",	"loser"},
	{5,	0,	"winner",	"loser"},
	{6,	0,	"winner",	"loser"},
	{7,	0,	"winner",	"loser"},
	{8,	0,	"winner",	"loser"},
	{9,	0,	"winner",	"loser"},
	{10,	0,	"winner",	"loser"},
	{11,	0,	"winner",	"loser"},
	{12,	0,	"winner",	"loser"},
	{13,	0,	"winner",	"loser"},
	{14,	0,	"winner",	"loser"},
	{15,	0,	"winner",	"loser"},
	{16,	0,	"winner",	"loser"},
	{17,	0,	"winner",	"loser"},
	{18,	0,	"winner",	"loser"},
	{19,	0,	"winner",	"loser"},
	{20,	0,	"winner",	"loser"},
	{21,	0,	"winner",	"loser"},
	{22,	0,	"winner",	"loser"},
}

function CEClear_CloseUsed()
end

function CEClear_ExitState(tostate)
	CEClear_CloseUsed();
	hdssSETSTATE(tostate);
	hdssCLEARALL();
end

function ControlExecute_cClear(timer)
	
	local chati = hdss.Get(HDSS_CHATI);
	local winner = 0;
	local csbegin = CS_L;
	local csafter = CS_L;
	if hdss.Get(HDSS_PLIFE, 1) > 0 then
		winner = 1;
		csbegin = CS_R;
		csafter = CS_L;
	end
	
	if timer == 1 then
		for i=0, 1 do
			local siadd = 1;
			if i == winner then
				siadd = 0;
			end
			hdssBGVALUE(i, LConst_gamefg_infoid, SI_GameInfo_Winner+siadd, helper_GetCenterX(i), CenterY-100);
			hdssFRONTSPRITE(LConst_game_FrontSprite_WinLoseID_0+i, SI_GameInfo_GameSet, helper_GetCenterX(i), TotalCenterY-160);
			hdssFADEOUTFRONTSPRITE(LConst_game_FrontSprite_WinLoseID_0+i, 64);
		end
	end
		
	
	if chati == 0 then
		hdssCHATON(-1, -1, csbegin);
	elseif chati == 1 then
		hdssCHAT(-1, csbegin, 0);
	elseif chati == 2 then
		hdssCHAT(-1, csafter, 1);
	elseif chati == 3 then
		hdssCHATOFF();
		CEClear_ExitState(STATE_OVER);
	end
end