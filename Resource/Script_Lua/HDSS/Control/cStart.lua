function ControlExecute_cStart(timer)
	if timer == 1 then
		
		local scene = hdss.Get(HDSS_GETSCENE);
		local col = global.ARGB(0xff, 0);
		local baseangle = hdss.Get(HDSS_ATAN2, TotalH, TotalW);
		local enemyrandrom = RANDT();
		for i=0, 1 do
			for j=0, 1 do
				hdss.Call(
					HDSS_BGVALEX,
					{
						i, LConst_gamefg_fadeIid+j, SI_White, col
					},
					{
						(i+j-1)*TotalW/2, 0, 0, TotalW/2, TotalH, 0, 0, 0, TotalW/2
					},
					{
						10, 0, (1-j)*18000, true
					}
				)
			end
			
			hdssSD(LConst_Desc_EnemyTimeCounter+i, 0);
			hdssSD(LConst_Desc_EnemyRandom+i, enemyrandrom);
			LGlobal_GetNextEnemyRandom(i);
			
			hdssBGSETUP(i, LConst_bgset_sceneid, scene, true);
						
		end
		
		--
		hdssSETPBINFI(1, 0);
		
	elseif timer == 32 then
		for i=0, 1 do
			hdssBGOFF(i, LConst_gamefg_fadeIid);
		end
	end
		
		hdssADDPNCHARGE(0, 0, 400);
		hdssADDPNCHARGE(1, 0, 400);
		
	if timer <= 8 then
		local scale = hdssINTER(1.5, 1, timer/8);
		for i=0, 1 do
			hdssBGVALUE(i, LConst_gamefg_infoid, SI_GameInfo_Ready, LGlobal_GetCenterX(i), CenterY, 128*scale, 48*scale);
		end
	elseif timer == 32 then
		for i=0, 1 do
			hdssBGFLAG(i, LConst_gamefg_infoid, BG_FADEOUT, 16);
		end
	elseif timer > 48 and timer <= 56 then
		local scale = hdssINTER(1.5, 1, (timer-48)/8);
		for i=0, 1 do
			hdssBGVALUE(i, LConst_gamefg_infoid, SI_GameInfo_GameStart, LGlobal_GetCenterX(i), CenterY, 208*scale, 48*scale);
		end
	elseif timer == 80 then
		for i=0, 1 do
			hdssBGFLAG(i, LConst_gamefg_infoid, BG_FADEOUT, 16);
		end
	elseif timer == 96 then
		for i=0, 1 do
			hdssBGOFF(i, LConst_gamefg_infoid);
		end
		
	elseif timer > 96 then

		for i=0, 1 do
			local enemytimecounter = hdss.Get(HDSS_D, LConst_Desc_EnemyTimeCounter+i);
			local nowlinenum = hdss.Get(HDSS_D, LConst_Desc_EnemyNowLineNum+i);
			local bdrain = hdss.Get(HDSS_PBDRAIN, i);
			local bhaveenemy = hdss.Get(HDSS_ENNUM, i, 1) > 0 or hdss.Get(HDSS_ENNUM, i, 2) > 0;
			if nowlinenum <= 0 and bdrain and bhaveenemy then
				enemytimecounter = LConst_EnemyMergeInterval - 1;
			else
				enemytimecounter = enemytimecounter + 1;
			end
			if enemytimecounter >= LConst_EnemyMergeInterval then
				local nowline = hdss.Get(HDSS_D, LConst_Desc_EnemyNowLine+i);
				local nowpattern = math.floor(nowline / 2);
				local nowdirection = math.mod(nowline, 2);
				if nowlinenum > 0 then
					local type, x, y, startangle, addangle, addtimebegin, addtimeend, life = LGlobal_GetEnemyBasicData(nowpattern, nowlinenum, nowdirection, i);
					hdssEB(type, i, x, y, startangle, 2.0, type, life);
					if addangle then
						hdssEA(i, ENAC_TURNANGLE_OOOOATOE,
							{
							},
							{
								addangle, addtimebegin, 0, addtimeend
							}
						)
					end
				end
				nowlinenum = nowlinenum - 1;
				if nowlinenum <= 0 then
					if bdrain and bhaveenemy then
						hdssSD(LConst_Desc_EnemyNowLineNum+i, 0);
					else
						LGlobal_GetNextEnemyRandom(i);
					end
				else
					hdssSD(LConst_Desc_EnemyNowLineNum+i, nowlinenum);
				end
				enemytimecounter = 0;
			end
			hdssSD(LConst_Desc_EnemyTimeCounter+i, enemytimecounter);
		end
	end
		
	if hdss.Get(HDSS_CHECKKEY, 0, KSI_PAUSE, DIKEY_DOWN) and hdss.Get(HDSS_STATE) ~= STATE_CLEAR then
		hdssSE(SE_SYSTEM_PAUSE);
		hdssSETSTATE(STATE_PAUSE, -1);
	end
	
	return true;

end