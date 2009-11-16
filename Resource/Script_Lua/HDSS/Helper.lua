function hdssSD(index, value)
	hdss.Call(
		HDSS_SD,
		{
			index, value
		}
	)
end

function hdssSDf(index, value)
	hdss.Call(
		HDSS_SDf,
		{
			index, value
		}
	)
end

function hdssBGVALUE(index, siid, cenx, ceny, w, h, col)
	hdss.Call(
		HDSS_BGVALUE,
		{
			index, siid, cenx, ceny, w, h, col
		}
	)
end

function hdssBGFLAG(index, flag)
	hdss.Call(
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
	hdss.Call(
		HDSS_SETSTATE,
		{
			tostate
		}
	)
end

function hdssRETURN(ret)
	hdss.Call(
		HDSS_RETURN,
		{
			ret
		}
	)
end

function hdssSE(seid)
	hdss.Call(
		HDSS_SE,
		{
			seid
		}
	)
end