function ControlExecute_cStart(con)
	if con == 1 then
		
		local enemyrandrom = RANDT();
		for i=0, 1 do
			hdssSD(LConst_Desc_EnemyTimeCounter+i, 0);
			hdssSD(LConst_Desc_EnemyRandom+i, enemyrandrom);
			LGlobal_GetNextEnemyRandom(i);
		end
		
		local col = global.ARGB(0xff, 0xffffff);
		for i=0,1 do
			local xoffset = i * 320;
			hdss.Call(
				HDSS_BGVALEX,
				{
					i, 0, SI_TitleScene
				},
				{
					xoffset, 480, -480, 320, 480, 9000, 0, 0
				},
				{
					0.008, 9000
				}
			)
			hdss.Call(
				HDSS_BGVALEX,
				{
					i, 1, SI_TitleScene
				},
				{
					xoffset, 0, -480, 320, 480, 9000, 0, 0
				},
				{
					0.008, 9000
				}
			)
			hdss.Call(
				HDSS_BGVALEX,
				{
					i, 2, SI_TitleScene
				},
				{
					xoffset, 0, -480, 480, 480, 0, 9000, 0
				},
				{
					0.008
				}
			)
			hdss.Call(
				HDSS_BGVALEX,
				{
					i, 3, SI_TitleScene
				},
				{
					xoffset+320, 0, -480, 480, 480, 0, 9000, 0
				},
				{
					0.008
				}
			)
		hdssBGCOLOR(i, 0, 0, 0, col, col);
		hdssBGCOLOR(i, 1, 0, 0, col, col);
		hdssBGCOLOR(i, 2, 0, col, col, 0);
		hdssBGCOLOR(i, 3, 0, col, col, 0);
		end
		
		--
		hdssSETPBINFI(1, 0);
		hdssSETPBINFI(0, 0);
		
	end


	for i=0, 1 do
		local enemytimecounter = hdss.Get(HDSS_D, LConst_Desc_EnemyTimeCounter+i);
		local nowlinenum = hdss.Get(HDSS_D, LConst_Desc_EnemyNowLineNum+i);
		local bdrain = hdss.Get(HDSS_PBDRAIN, i);
		if nowlinenum <= 0 and bdrain and (hdss.Get(HDSS_ENNUM, i, 1) > 0 or hdss.Get(HDSS_ENNUM, i, 2) > 0) then
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
				if bdrain then
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
	
	if hdss.Get(HDSS_CHECKKEY, 0, KSI_PAUSE, DIKEY_DOWN) and hdss.Get(HDSS_STATE) ~= STATE_CLEAR then
		hdssSE(SE_SYSTEM_PAUSE);
		hdssSETSTATE(STATE_PAUSE, -1);
	end
	
	return true;

end