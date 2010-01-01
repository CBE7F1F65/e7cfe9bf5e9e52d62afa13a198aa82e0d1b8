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

	{100,	Spell_s00},
	{101,	Spell_s01},
	{102,	Spell_s02},
	{103,	Spell_s03},
	{104,	Spell_s04},
	{105,	Spell_s05},
	{106,	Spell_s06},
	{107,	Spell_s07},
	{108,	Spell_s08},
	{109,	Spell_s09},
	{110,	Spell_s10},
	{111,	Spell_s11},
	{112,	Spell_s12},
	{113,	Spell_s13},
	{114,	Spell_s14},
	{115,	Spell_s15},
	{116,	Spell_s16},
	{117,	Spell_s17},
	{118,	Spell_s18},
	{119,	Spell_s19},
	{120,	Spell_s20},
	{121,	Spell_s21},
	{122,	Spell_s22},
}

function SceneExecute(name, timer)
	
	local playerindex = 0;
	if name >= PLAYERTYPEMAX and name < LConst_SceneSpellOffset or name-LConst_SceneSpellOffset >= PLAYERTYPEMAX then
		name = name - PLAYERTYPEMAX;
		playerindex = 1;
	end
	
	for i, it in pairs(LTable_SceneIDFunction) do
		if it[1] == name then
			return it[2](playerindex, timer);
		end
	end

end