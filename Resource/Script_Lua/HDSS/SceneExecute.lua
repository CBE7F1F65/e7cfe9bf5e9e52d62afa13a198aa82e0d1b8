LTable_SceneIDFunction	=
{		
	{0,	Scene_s00},
	{1,	Scene_s01},
	{2,	Scene_s02},
	{3,	Scene_s03},
	{4,	Scene_s04},
	{5,	Scene_s05},
	{6,	Scene_s06},
	{7,	Scene_s07},
	{8,	Scene_s08},
	{9,	Scene_s09},
	{10,	Scene_s10},
	{11,	Scene_s11},
	{12,	Scene_s12},
	{13,	Scene_s13},
	{14,	Scene_s14},
	{15,	Scene_s15},
	{16,	Scene_s16},
	{17,	Scene_s17},
	{18,	Scene_s18},
	{19,	Scene_s19},
	{20,	Scene_s20},
	{21,	Scene_s21},
	{22,	Scene_s22},
}

function SceneExecute(name, con)
	
	local playerindex = 0;
	if name >= PLAYERTYPEMAX then
		name = name - PLAYERTYPEMAX;
		playerindex = 1;
	end
	
	for i, it in pairs(LTable_SceneIDFunction) do
		if it[1] == name then
			return it[2](playerindex, con);
		end
	end

end