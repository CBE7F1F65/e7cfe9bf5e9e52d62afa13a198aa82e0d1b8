function CEPlayerSelect_Init()
end

function CEPlayerSelect_SetSelect(selsysplayerid, x, minuskey, pluskey, okkey)
	playercontenttable, playercount = game.GetPlayerContentTable();
	for j, it in pairs(playercontenttable) do
		local i = j-1;
		local dcol = global.ARGB(0xff, 0xff3333+(0xff-0x40)/playercount * i);
		hdss.Call(
			HDSS_SELBUILD,
			{
				selsysplayerid, i, it.siid, x + i * TotalW / 4, TotalCenterY, 0.75
			},
			{
				0, 0,
				-4, -4,
				0, 0,
				8, 8
			},
			{
				it.name, LConst_selsys_ucol, dcol, LConst_selsys_shadow, 40, global.SIGN(i) * 12 + 150, 1.2
			}
		)
	end
	hdss.Call(
		HDSS_SELSET,
		{
			selsysplayerid, playercount, 0, minuskey, pluskey, okkey
		},
		{
			1, x, TotalW / 4, 0, 0
		}
	)
end

function CEPlayerSelect_SetBG()
	hdssBGVALUE(LConst_uibg_topcontentid, SI_TopContent_Girl, TotalCenterX, 96);
end

function ControlExecute_cPlayerSelect(con)
	
	local dsel1complete = RESERVEBEGIN;
	local dsel2complete = RESERVEBEGIN + 1;
	
	if con == 1 then
		CEPlayerSelect_Init();
		hdssSD(dsel1complete, 0);
		hdssSD(dsel2complete, 0);
		CEPlayerSelect_SetBG()
	end
	
	local _sel1complete = hdss.Get(HDSS_D, dsel1complete);
	local _sel2complete = hdss.Get(HDSS_D, dsel2complete);
	
	if _sel1complete == 0 then
		CEPlayerSelect_SetSelect(LConst_selsys_player1id, TotalW / 4, KS_LEFT_0, KS_RIGHT_0, KS_FIRE_0);
		_sel1complete = 1;
	end
		
	hdssSD(dsel1complete, _sel1complete);
	hdssSD(dsel2complete, _sel2complete);
	
	return true;

end