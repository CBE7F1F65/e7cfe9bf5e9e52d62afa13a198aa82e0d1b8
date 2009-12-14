function CEClear_CloseUsed()
end

function CEClear_ExitState(tostate)
	CEClear_CloseUsed();
	hdssSETSTATE(tostate);
end

function ControlExecute_cClear(con)
	if con > 60 then
		CEClear_ExitState(STATE_OVER);
	end
end