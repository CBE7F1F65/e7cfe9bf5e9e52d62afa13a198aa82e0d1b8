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

function hdssSE(seid)
	return hdss.Call(
		HDSS_SE,
		{
			seid
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