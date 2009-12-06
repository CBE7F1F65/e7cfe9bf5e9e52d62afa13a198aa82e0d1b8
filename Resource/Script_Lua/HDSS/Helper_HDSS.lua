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

function hdssSTARTPREP(callinit)
	return hdss.Call(
		HDSS_STARTPREP,
		{
			callinit
		}
	)
end

function hdssBGVALUE(index, siid, cenx, ceny, w, h, col)
	return hdss.Call(
		HDSS_BGVALUE,
		{
			index, siid, cenx, ceny, w, h, col
		}
	)
end

function hdssBGFLAG(index, flag)
	return hdss.Call(
		HDSS_BGFLAG,
		{
			index, flag
		}
	)
end

function hdssBGCOLOR(index, col0, col1, col2, col3)
	return hdss.Call(
		HDSS_BGCOLOR,
		{
			index, col0, col1, col2, col3
		}
	)
end

function hdssBGOFF(index1, index2, index3, index4)
	if index1 == nil then
		return;
	end
	hdss.Call(
		HDSS_BGOFF,
		{
			index1
		}
	)
	if index2 == nil then
		return;
	end
	hdss.Call(
		HDSS_BGOFF,
		{
			index2
		}
	)
	if index3 == nil then
		return;
	end
	hdss.Call(
		HDSS_BGOFF,
		{
			index3
		}
	)
	if index4 == nil then
		return;
	end
	hdss.Call(
		HDSS_BGOFF,
		{
			index4
		}
	)
end

function hdssSETPUSHEVENT(index, key1, key2, key3, key4, pushfirst, pushrollto)
	return hdss.Call(
		HDSS_SETPUSHEVENT,
		{
			index, key1, key2, key3, key4, pushfirst, pushrollto
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

function hdssSETSTATE(tostate)
	return hdss.Call(
		HDSS_SETSTATE,
		{
			tostate
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

function hdssFRONTSPRITE(index, siid, x, y, angle, hscale, vscale)
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
				x, y, angle, hscale, vscale
			}
		)
	end
end

function hdssFREEFRONTSPRITE(index)
	return hdss.Call(
		HDSS_FREEFRONTSPRITE,
		{
			index
		}
	)
end

function hdssSETPINITLIFE(index, life)
	return hdss.Call(
		HDSS_SETPINITLIFE,
		{
			index, life
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

function hdssCOLLISION_CIRCLE(x, y, aimx, aimy, r, bbig)
	return hdss.Call(
		HDSS_COLLISION_CIRCLE,
		{
			x, y, aimx, aimy, r, bbig
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