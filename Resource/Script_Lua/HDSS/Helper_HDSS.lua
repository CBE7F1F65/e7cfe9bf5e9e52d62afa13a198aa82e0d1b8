function hdssSD(index, value)
	return hdss.Call(
		HDSS_SD,
		{
			index, value
		}
	)
end

function hdssSDf(index, value)
	return hdss.Call(
		HDSS_SDf,
		{
			index, value
		}
	)
end

function hdssSETCHARA(index, id, id_sub_1, id_sub_2)
	return hdss.Call(
		HDSS_SETCHARA,
		{
			index, id, id_sub_1, id_sub_2
		}
	)
end

function hdssSETSCENE(scene)
	return hdss.Call(
		HDSS_SETSCENE,
		{
			scene
		}
	)
end

function hdssSTARTPREP(callinit)
	return hdss.Call(
		HDSS_STARTPREP,
		{
			callinit
		}
	)
end

function hdssSAVEREPLAY(bSave, bFill)
	return hdss.Call(
		HDSS_SAVEREPLAY,
		{
			bSave, bFill
		}
	)
end

function hdssBGVALUE(playerindex, index, siid, cenx, ceny, w, h, col)
	return hdss.Call(
		HDSS_BGVALUE,
		{
			playerindex, index, siid, cenx, ceny, w, h, col
		}
	)
end

function hdssBGFLAG(playerindex, index, flag)
	return hdss.Call(
		HDSS_BGFLAG,
		{
			playerindex, index, flag
		}
	)
end

function hdssBGCOLOR(playerindex, index, col0, col1, col2, col3, blend)
	return hdss.Call(
		HDSS_BGCOLOR,
		{
			playerindex, index, col0, col1, col2, col3, blend
		}
	)
end

function hdssBGBLEND(playerindex, index, blend)
	return hdss.Call(
		HDSS_BGBLEND,
		{
			playerindex, index, blend
		}
	)
end

function hdssBGOFF(playerindex, index1, index2, index3, index4)
	if index1 == nil then
		return;
	end
	hdss.Call(
		HDSS_BGOFF,
		{
			playerindex, index1
		}
	)
	if index2 == nil then
		return;
	end
	hdss.Call(
		HDSS_BGOFF,
		{
			playerindex, index2
		}
	)
	if index3 == nil then
		return;
	end
	hdss.Call(
		HDSS_BGOFF,
		{
			playerindex, index3
		}
	)
	if index4 == nil then
		return;
	end
	hdss.Call(
		HDSS_BGOFF,
		{
			playerindex, index4
		}
	)
end

function hdssBGSETUP(playerindex, setID, sID, bForce)
	return hdss.Call(
		HDSS_BGSETUP,
		{
			playerindex, setID, sID, bForce
		}
	)
end

function hdssSETKEY(playerindex, ksi, set)
	return hdss.Call(
		HDSS_SETKEY,
		{
			playerindex, ksi, set
		}
	)
end

function hdssSETPUSHEVENT(index, playerindex, key1, key2, key3, key4, pushfirst, pushrollto)
	return hdss.Call(
		HDSS_SETPUSHEVENT,
		{
			index, playerindex, key1, key2, key3, key4, pushfirst, pushrollto
		}
	)
end

function hdssUPDATEPUSHEVENT(index)
	return hdss.Call(
		HDSS_UPDATEPUSHEVENT,
		{
			index
		}
	)
end

function hdssSELSET(index, select)
	return hdss.Call(
		HDSS_SELSET,
		{
			index, select
		}
	)
end

function hdssSELCONFIRM(index, keyminus, keyplus, keyok, keycancel, cenx, ceny, settrue)
	return hdss.Call(
		HDSS_SELCONFIRM,
		{
			index, keyminus, keyplus, keyok, keycancel, cenx, ceny, settrue
		}
	)
end

function hdssSELCLEAR(index1, index2, index3, index4)
	if index1 == nil then
		return;
	end
	hdss.Call(
		HDSS_SELCLEAR,
		{
			index1
		}
	)
	if index2 == nil then
		return;
	end
	hdss.Call(
		HDSS_SELCLEAR,
		{
			index2
		}
	)
	if index3 == nil then
		return;
	end
	hdss.Call(
		HDSS_SELCLEAR,
		{
			index3
		}
	)
	if index4 == nil then
		return;
	end
	hdss.Call(
		HDSS_SELCLEAR,
		{
			index4
		}
	)
end

function hdssSETSTATE(tostate, time)
	return hdss.Call(
		HDSS_SETSTATE,
		{
			tostate, time
		}
	)
end

function hdssRETURN(ret)
	return hdss.Call(
		HDSS_RETURN,
		{
			ret
		}
	)
end

function hdssCLEARALL()
	return hdss.Call(
		HDSS_CLEARALL,
		{
		}
	)
end

function hdssSE(seid, x)
	if x == nil then
		x = TotalCenterX;
	end
	return hdss.Call(
		HDSS_SE,
		{
			seid, x
		}
	)
end

function hdssSEOFF(seid)
	if seid == nil then
		seid = -1;
	end
	return hdss.Call(
		HDSS_SEOFF,
		{
			seid
		}
	)
end

function hdssFRONTSPRITE(index, siid, x, y, angle, hscale, vscale, col, blend)
	if x == nil or y == nil then
		return hdss.Call(
			HDSS_FRONTSPRITE,
			{
				index, siid
			}
		)
	else
		return hdss.Call(
			HDSS_FRONTSPRITE,
			{
				index, siid
			},
			{
				x, y, angle, hscale, vscale, col, blend
			}
		)
	end
end

function hdssFADEOUTFRONTSPRITE(index, time)
	return hdss.Call(
		HDSS_FADEOUTFRONTSPRITE,
		{
			index, time
		}
	)
end

function hdssFREEFRONTSPRITE(index)
	return hdss.Call(
		HDSS_FREEFRONTSPRITE,
		{
			index
		}
	)
end

function hdssSETPINITLIFE(playerindex, life)
	return hdss.Call(
		HDSS_SETPINITLIFE,
		{
			playerindex, life
		}
	)
end

function hdssSETPBINFI(playerindex, reasonflag, infitimer)
	return hdss.Call(
		HDSS_SETPBINFI,
		{
			playerindex, reasonflag, infitimer
		}
	)
end

function hdssRMA(x, y, aimx, aimy, r)
	return hdss.Call(
		HDSS_RAMA,
		{
			true, x, y, r, aimx, aimy
		}
	)
end

function hdssRMAP(playerindex, x, y, r)
	return hdss.Call(
		HDSS_RAMA,
		{
			true, x, y, r, hdss.Get(HDSS_PX, playerindex), hdss.Get(HDSS_PY, playerindex)
		}
	)
end

function hdssAMA(x, y, aimx, aimy, angle)
	if angle == nil then
		angle = 0;
	end
	return hdss.Call(
		HDSS_RAMA,
		{
			false, x, y, angle, aimx, aimy
		}
	)
end

function hdssAMAP(playerindex, x, y, angle)
	if angle == nil then
		angle = 0;
	end
	return hdss.Call(
		HDSS_RAMA,
		{
			false, x, y, angle, hdss.Get(HDSS_PX, playerindex), hdss.Get(HDSS_PY, playerindex)
		}
	)
end

function hdssINTER(a, b, x)
	return hdss.Call(
		HDSS_INTER,
		{
			a, b, x
		}
	)
end

function hdssCOLLISION_CIRCLE(x, y, aimx, aimy, r, bbig)
	return hdss.Call(
		HDSS_COLLISION_CIRCLE,
		{
			x, y, aimx, aimy, r, bbig
		}
	)
end

function hdssEFFSETUP(playerindex, effID, x, y, lifetime, angle, speed)
	return hdss.Call(
		HDSS_EFFSETUP,
		{
			effID, playerindex, x, y, 0, lifetime, 0xff, angle, speed
		}
	)
end

function hdssEA(playerindex, ac, fpara, ipara)
	if fpara == nil then
		fpara = {0, 0, 0, 0};
	end
	if ipara == nil then
		ipara = {0, 0, 0, 0};
	end
	for i=1, 4 do
		if fpara[i] == nil then
			fpara[i] = 0;
		end
		if ipara[i] == nil then
			ipara[i] = 0;
		end
	end
	return hdss.Call(
		HDSS_EA,
		{
			playerindex, ac, fpara[1], fpara[2], fpara[3], fpara[4], ipara[1], ipara[2], ipara[3], ipara[4], 
		}
	)
end

function hdssEA_FADEOUT(playerindex, time)
	return hdss.Call(
		HDSS_EA,
		{
			playerindex, ENAC_FADEOUT_OOOOOTOO, 0, 0, 0, 0, 0, time
		}
	)
end

function hdssEA_OVERPLAYER(playerindex, x, y, time, counter, endtime)
	return hdss.Call(
		HDSS_EA,
		{
			playerindex, ENAC_OVERPLAYER_XYOOOTCE, x, y, 0, 0, 0, time, counter, endtime
		}
	)
end

function hdssENSAIM(playerindex, level, aimx, aimy)
	return hdss.Call(
		HDSS_ENSAIM,
		{
			playerindex, level, aimx, aimy
		}
	)
end

function hdssENTOI(playerindex, enindex)
	return hdss.Call(
		HDSS_ENTOI,
		{
			playerindex, enindex
		}
	)
end

function hdssENAZBUILD(playerindex, type, x, y, rPrep, rParal, angle)
	return hdss.Call(
		HDSS_ENAZBUILD,
		{
			playerindex, type, x, y, rPrep, rParal, angle
		}
	)
end

function hdssA(playerindex, table)
	if table == nil then
		return hdss.Call(
			HDSS_A,
			{
				playerindex
			}
		)
	end
	return hdss.Call(
		HDSS_A,
		{
			playerindex
		},
		table
	)
end

function hdssB(playerindex, x, y, angle, speed, type, color, fadeintime, avoid)
	return hdss.Call(
		HDSS_B,
		{
			playerindex, x, y, angle, speed, type, color, fadeintime, avoid
		}
	)
end

function hdssEB(eID, playerindex, x, y, angle, speed, type, life, take)
	if take == nil or take == 0 then
		return hdss.Call(
			HDSS_EB,
			{
				eID, playerindex, x, y, angle, speed, type, life
			}
		)
	else
		return hdss.Call(
			HDSS_EB,
			{
				eID, playerindex, x, y, angle, speed, type, life
			},
			{
				0xff
			},
			{
				take
			}
		)
	end
end

function hdssCHATON(leftID, rightID, flag)
	if leftID < 0 then
		leftID = hdss.Get(HDSS_CHARA, 0);
	end
	if rightID < 0 then
		rightID = hdss.Get(HDSS_CHARA, 1);
	end
	local blf = false;
	local brf = false;
	for i, it in pairs(LTable_PlayerWinLoseChat) do
		if it[1] == leftID and it[2] == 1 then
			blf = true;
		end
		if it[1] == rightID and it[2] == 1 then
			brf = true;
		end
	end
	if blf then
		flag = flag + CS_LF;
	end
	if not brf then
		flag = flag + CS_RF;
	end
	return hdss.Call(
		HDSS_CHATON,
		{
			leftID, rightID, flag
		}
	)
end

function hdssCHAT(ID, flag, text)
	if ID < 0 then
		if flag == CS_L then
			ID = hdss.Get(HDSS_CHARA, 0);
		else
			ID = hdss.Get(HDSS_CHARA, 1);
		end
	end
	
	for i, it in pairs(LTable_PlayerWinLoseChat) do
		if it[1] == ID then
			if it[2] == 0 then
				if flag == CS_R then
					flag = CS_R + CS_RF;
				end
			else
				if flag == CS_L then
					flag = CS_L + CS_LF;
				end
			end
			if text == 0 or text == 1 then
				text = it[3+text];
			end
		end
	end
	return hdss.Call(
		HDSS_CHAT,
		{
			ID, flag, text
		}
	)
end

function hdssCHATOFF()
	return hdss.Call(
		HDSS_CHATOFF,
		{
		}
	)
end