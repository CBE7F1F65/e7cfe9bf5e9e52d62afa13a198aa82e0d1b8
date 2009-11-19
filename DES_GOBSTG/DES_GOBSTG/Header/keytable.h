#ifndef _KEYTABLE_H
#define _KEYTABLE_H

#include "MainDependency.h"

#define SCRIPT_CTOFFSET	0xA000

#define SCR_NULL_STR		"_NULL"
#define SCR_CONST_STR		"_CONST"
#define SCR_KEYSTATE_STR	"_KEYSTATE"

enum{
	SCR_TYPEBEGIN	= 0xAFFFAA00,

	SCR_SCRIPTTAG	= 0xAFFFAB00,

	SCR_FILENAME	= 0xAFFFAC10,
	SCR_BLOCKCON	= 0xAFFFAC20,

	SCR_CONTROL		= 0xAFFFAD10,
	SCR_STAGE		= 0xAFFFAD20,
	SCR_EDEF		= 0xAFFFAD40,
	SCR_SCENE		= 0xAFFFAD80,
	SCR_FUNCTION	= 0xAFFFAE10,
	SCR_EVENT		= 0xAFFFAE20,

	SCR_CTCONTROL	= SCR_CONTROL - SCRIPT_CTOFFSET,
	SCR_CTSTAGE		= SCR_STAGE - SCRIPT_CTOFFSET,
	SCR_CTEDEF		= SCR_EDEF - SCRIPT_CTOFFSET,
	SCR_CTSCENE		= SCR_SCENE - SCRIPT_CTOFFSET,
	SCR_CTFUNCTION	= SCR_FUNCTION - SCRIPT_CTOFFSET,
	SCR_CTEVENT		= SCR_EVENT - SCRIPT_CTOFFSET,

	SCR_NULL		= 0xAFFFAF00,
	SCR_CONST		= 0xAFFFAF10,
	SCR_KEYSTATE	= 0xAFFFAF20,
};

#define SCRKT_STR_TIMEFUNC		"@@"

#define SCRKT_SIZE_TIMEFUNC		2
#define SCRKT_SIZE_OPERATOR		3
#define SCRKT_TEST_OPERATOR		0x7
#define SCRKT_SIZE_OPERATORNUM	8

#define SCRKT_CHAR_MOD			'%'
#define SCRKT_CHAR_PLUS			'+'
#define SCRKT_CHAR_LESS			'<'
#define SCRKT_CHAR_LESSEQUAL	']'
#define SCRKT_CHAR_EQUAL		'='
#define SCRKT_CHAR_GREATEQUAL	'['
#define SCRKT_CHAR_GREAT		'>'

#define SCR_TIMECONTROL			0xF0000000
#define SCR_TIMECONTROL_TEST0	0x08000000

#define SCR_TIMEFUNC_MOD		0x1
#define SCR_TIMEFUNC_PLUS		0x2
#define SCR_TIMEFUNC_TESTERBEGIN	0x3
#define SCR_TIMEFUNC_LESS		0x3
#define SCR_TIMEFUNC_LESSEQUAL	0x4
#define SCR_TIMEFUNC_EQUAL		0x5
#define SCR_TIMEFUNC_GREATEQUAL	0x6
#define SCR_TIMEFUNC_GREAT		0x7

/************************************************************************/
//
//	X				Type
// 		X			Class
// 			X		Enum
// 				X	Addition
//	Type:
// 		A	Action
// 		B	Basic
// 		C	Control
// 		D	Data
// 		E	Expression
// 		F	Function
//	Class:
// 		0	AttackObject
// 		1	Ghost
// 		2	Enemy
// 		3	Math
//		4	Other
// 		5	Spectial
//		6	Effect
// 		7	Player
// 		9	Layer
// 		A	Select
//
/************************************************************************/

#define SCRKWMASK_TYPE	0xF000
#define SCRKWMASK_CLASS	0x0F00

#define SCRKW_ACTION		0xA000
#define SCRKW_BASIC			0xB000
#define SCRKW_CONTROL		0xC000
#define SCRKW_DATA			0xD000
#define SCRKW_EXPRESSION	0xE000
#define SCRKW_FUNCTION		0xF000

#define SCRKW_CLASS_ATTACKOBJECT	0x0000
#define SCRKW_CLASS_GHOST			0x0100
#define SCRKW_CLASS_ENEMY			0x0200
#define SCRKW_CLASS_MATH			0x0300
#define SCRKW_CLASS_OTHER			0x0400
#define SCRKW_CLASS_SPECIAL			0x0500
#define SCRKW_CLASS_EFFECT			0x0600
#define SCRKW_CLASS_PLAYER			0x0700
#define SCRKW_CLASS_LAYER			0x0900
#define SCRKW_CLASS_SELECT			0x0A00

//Action
enum{
	SCR_SD		= 0xA410,
	SCR_SDF		= 0xA420,
	SCR_ST		= 0xA440,
	SCR_CALL		= 0xA490,
	SCR_CALLEX		= 0xA4A0,
	SCR_EXECUTE		= 0xA4B0,

	SCR_RETURN		= 0xA510,
	SCR_SETSTATE	= 0xA520,
	SCR_SETTIME		= 0xA530,
	SCR_SETDIFFI	= 0xA540,
	SCR_SETCHARA	= 0xA550,
	SCR_SETSCENE	= 0xA560,
	SCR_SETMODE		= 0xA570,
	SCR_STARTPREP	= 0xA580,
	SCR_SETKEY			= 0xA590,
	SCR_DISABLEALLKEY	= 0xA5A0,
	SCR_SETPUSHEVENT	= 0xA5B0,
	SCR_UPDATEPUSHEVENT	= 0xA5C0,
	SCR_STOPACTION		= 0xA5D0,
	SCR_SETFRAMESKIP	= 0xA5E0,

	SCR_MUSICCHANGE		= 0xA610,
	SCR_MUSICSLIDE		= 0xA620,
	SCR_SE			= 0xA630,
	SCR_SEOFF		= 0xA640,
	SCR_HSVTORGB	= 0xA660,
	SCR_PRINT		= 0xA680,
	SCR_FRONTSPRITE	= 0xA6A0,
	SCR_FREEFRONTSPRITE		= 0xA6B0,
	SCR_SETSHAKE	= 0xA6E0,

};
//Basic
enum{
	SCR_BUBUILD			= 0xB010,
	SCR_BUACTIONSET		= 0xB020,
	SCR_BUBUILDCIRCLE	= 0xB030,
	SCR_BUBUILDLINE		= 0xB040,
	SCR_BUDECANCEL		= 0xB050,
	SCR_IZEZONE			= 0xB060,
	SCR_BEBUILD		= 0xB090,
	SCR_BEVECTOR	= 0xB0A0,
	SCR_BEHOLD		= 0xB0B0,
	SCR_BEPIN		= 0xB0C0,

	SCR_GHBUILD		= 0xB110,
	SCR_GHSAIM		= 0xB120,
	SCR_GHSET		= 0xB130,
	SCR_GHCHASE		= 0xB140,
	SCR_GHSETLIFE	= 0xB150,
	SCR_GHCHANGE	= 0xB160,

	SCR_ENBUILD		= 0xB210,
	SCR_ENACTIONSET	= 0xB220,
	SCR_ENSAIM		= 0xB230,
	SCR_ENCHASE		= 0xB240,
	SCR_ENSETLIFE	= 0xB250,
	SCR_ENCHANGE	= 0xB260,
	SCR_DAMAGEZONE	= 0xB270,
	SCR_BOSSSTORE	= 0xB280,
	SCR_BOSSATTACK	= 0xB290,

	SCR_RAMA		= 0xB310,
	SCR_DIST		= 0xB320,
	SCR_CHASEAIM	= 0xB330,
	SCR_INTER		= 0xB340,

	SCR_ITEMBUILD		= 0xB410,

	SCR_BOSSUP		= 0xB510,
	SCR_SPELLUP		= 0xB520,
	SCR_ACONTROL			= 0xB550,
	SCR_BCONTROL			= 0xB560,
	SCR_COLLISION_CIRCLE	= 0xB570,
	SCR_COLLISION_SQUARE	= 0xB580,

	SCR_EFFSETUP		= 0xB650,
	SCR_EFFSETUPEX		= 0xB660,
	SCR_EFFSETUPCHASE	= 0xB670,
	SCR_EFFSTOP			= 0xB680,
	SCR_EFFOFF			= 0xB690,
	SCR_EFFSET			= 0xB6A0,
	SCR_EFFMOVETO		= 0xB6B0,

	SCR_SETPPOS			= 0xB710,
	SCR_SETPLIFE		= 0xB720,
	SCR_SETPINITLIFE	= 0xB730,
	SCR_SETPPOWER		= 0xB740,
	SCR_SETPFAITH		= 0xB750,
	SCR_SETPPOINT		= 0xB760,
	SCR_SETPBBORDER		= 0xB770,
	SCR_SETPBSLOW		= 0xB780,
	SCR_SETPBINFI		= 0xB790,
	SCR_SETPSPEED		= 0xB7A0,
	SCR_SETPSLOWSPEED	= 0xB7B0,
	SCR_SETPSPEEDFACTOR	= 0xB7C0,
	SCR_COLLAPSE		= 0xB7D0,
	SCR_SHOOTPB			= 0xB7E0,
	SCR_BONUSFLAG		= 0xB7F0,

	SCR_BGVALUE		= 0xB910,
	SCR_BGVALEX		= 0xB920,
	SCR_BGTEXRECT	= 0xB930,
	SCR_BGRECT		= 0xB940,
	SCR_BGZ			= 0xB950,
	SCR_BGSCALE		= 0xB960,
	SCR_BGCOLOR		= 0xB970,
	SCR_BGMOVE		= 0xB980,
	SCR_BGFLAG		= 0xB990,
	SCR_BGPARAL		= 0xB9A0,
	SCR_BG4V		= 0xB9B0,
	SCR_BGOFF		= 0xB9C0,
	SCR_BGBLEND		= 0xB9D0,
	SCR_BGSETUP		= 0xB9E0,

	SCR_SELBUILD	= 0xBA10,
	SCR_SELCLEAR	= 0xBA20,
	SCR_SELCONFIRM	= 0xBA30,
	SCR_SELSETUP	= 0xBA40,
	SCR_SELFLAG		= 0xBA50,
	SCR_SELSET		= 0xBA60,
	SCR_ISELBUILD		= 0xBA90,
	SCR_ISELCLEAR		= 0xBAA0,
	SCR_ISELSET			= 0xBAB0,
	SCR_ISELFLAG		= 0xBAC0,
	SCR_ISELCOLOR		= 0xBAD0,
};
//Control
enum{
	SCR_IF			= 0xC410,
	SCR_ELSE		= 0xC420,
	SCR_ELSEIF		= 0xC430,
	SCR_THEN		= 0xC440,
	SCR_END			= 0xC450,
	SCR_LOOP		= 0xC460,
	SCR_SKIP		= 0xC470,

	SCR_CHATON		= 0xC510,
	SCR_CHATOFF		= 0xC520,
};
//Data
enum{
	SCR_DATAGET			= 0xD410,
	SCR_DATAGETf		= 0xD420,
	SCR_DATASET			= 0xD430,
	SCR_DATASETf		= 0xD440,
	SCR_SETFLAG			= 0xD450,
	SCR_TRYSTAGE	= 0xD490,
	SCR_DEBUG_BREAKPOINT	= 0xD4D0,
};
//Expression	(items in Copy)
enum{
	SCR_ADD_INT		= 0xE410,
	SCR_SUB_INT		= 0xE420,
	SCR_MUL_INT		= 0xE430,
	SCR_DIV_INT		= 0xE440,
	SCR_ADD_FLOAT	= 0xE450,
	SCR_SUB_FLOAT	= 0xE460,
	SCR_MUL_FLOAT	= 0xE470,
	SCR_DIV_FLOAT	= 0xE480,
	SCR_ADD_UINT	= 0xE490,
	SCR_SUB_UINT	= 0xE4A0,
	SCR_MUL_UINT	= 0xE4B0,
	SCR_DIV_UINT	= 0xE4C0,
	SCR_MOD			= 0xE4D0,
	SCR_MOD_UINT	= 0xE4E0,

	SCR_INVERSE		= 0xE510,
	SCR_NOT			= 0xE520,
	SCR_GREAT_INT	= 0xE530,
	SCR_LESS_INT	= 0xE540,
	SCR_GREAT_FLOAT	= 0xE550,
	SCR_LESS_FLOAT	= 0xE560,
	SCR_GREAT_UINT	= 0xE570,
	SCR_LESS_UINT	= 0xE580,
};
//Function		(items in Value)
enum{
	SCR_BUI			= 0xF010,
	SCR_BUANGLE		= 0xF020,
	SCR_BUSPEED		= 0xF030,
	SCR_BUX			= 0xF040,
	SCR_BUY			= 0xF050,
	SCR_BUTIMER		= 0xF060,
	SCR_BUCANCELABLE	= 0xF070,
	SCR_BUHAVEGRAY	= 0xF080,
	SCR_BEI		= 0xF090,
	SCR_BEANGLE	= 0xF0A0,
	SCR_BESPEED	= 0xF0B0,
	SCR_BEX		= 0xF0C0,
	SCR_BEY		= 0xF0D0,
	SCR_BETIMER	= 0xF0E0,
	SCR_BEHOLDTAR	= 0xF0F0,
	SCR_BEPINTAR	= 0xF0F8,

	SCR_GHX			= 0xF110,
	SCR_GHY			= 0xF120,
	SCR_GHTIMER		= 0xF130,
	SCR_GHI			= 0xF140,
	SCR_GHANGLE		= 0xF150,
	SCR_GHSPEED		= 0xF160,
	SCR_GHAMAP		= 0xF170,
	SCR_GHRMAP		= 0xF180,
	SCR_GHAIMX		= 0xF190,
	SCR_GHAIMY		= 0xF1A0,
	SCR_GHLIFE		= 0xF1B0,
	SCR_GHAC		= 0xF1C0,

	SCR_ENX			= 0xF210,
	SCR_ENY			= 0xF220,
	SCR_ENTIMER		= 0xF230,
	SCR_ENI			= 0xF240,
	SCR_ENANGLE		= 0xF250,
	SCR_ENSPEED		= 0xF260,
	SCR_ENAMAP		= 0xF270,
	SCR_ENRMAP		= 0xF280,
	SCR_ENAIMX		= 0xF290,
	SCR_ENAIMY		= 0xF2A0,
	SCR_ENLIFE		= 0xF2B0,

	SCR_RAND		= 0xF310,
	SCR_RANDR		= 0xF320,
	SCR_SEED		= 0xF330,
	SCR_SINA		= 0xF340,
	SCR_COSA		= 0xF342,
	SCR_TANA		= 0xF344,
	SCR_ASIN2		= 0xF350,
	SCR_ACOS2		= 0xF352,
	SCR_ATAN2		= 0xF360,
	SCR_SQRT		= 0xF370,
	SCR_SIGN		= 0xF380,
	SCR_ROLL		= 0xF390,

	SCR_D		= 0xF410,
	SCR_DU		= 0xF420,
	SCR_TX		= 0xF430,
	SCR_TY		= 0xF440,
	SCR_TIME	= 0xF450,
	SCR_NOWNAME	= 0xF460,
	SCR_NOWCON	= 0xF470,
	SCR_DIFFI		= 0xF480,
	SCR_SNOSTAGE	= 0xF490,
	SCR_SNODIFFI	= 0xF492,
	SCR_SNOBATTLE	= 0xF494,
	SCR_SNOUSER		= 0xF498,
	SCR_CHARA		= 0xF4A0,
	SCR_GETSCENE	= 0xF4B0,
	SCR_MODE		= 0xF4C0,
	SCR_REPLAYMODE	= 0xF4D0,
	SCR_FRAMESKIP	= 0xF4E0,

	SCR_CHATI	= 0xF510,
	SCR_BOSSFAILED	= 0xF530,
	SCR_BOSSFLAG	= 0xF540,
	SCR_CHECKKEY	= 0xF590,
	SCR_GETFLAG		= 0xF5A0,
	SCR_PLAYERNAME	= 0xF5B0,
	SCR_ENEMYNAME	= 0xF5C0,
	SCR_SPELLNAME	= 0xF5D0,
	SCR_SPELLUSERNAME	= 0xF5E0,
	SCR_SPELLUSERENAME	= 0xF5F0,

	SCR_PX			= 0xF710,
	SCR_PY			= 0xF720,
	SCR_PLIFE		= 0xF730,
	SCR_PBOMB		= 0xF740,
	SCR_PPOWER		= 0xF750,
	SCR_PFAITH		= 0xF760,
	SCR_PPOINT		= 0xF770,
	SCR_PBBORDER	= 0xF780,
	SCR_PBSLOW		= 0xF790,
	SCR_PBINFI		= 0xF7A0,
	SCR_PSPEED		= 0xF7B0,
	SCR_PSLOWSPEED	= 0xF7C0,
	SCR_PGX			= 0xF7D0,
	SCR_PGY			= 0xF7E0,
	SCR_HAVEPLAYER	= 0xF7F0,

	SCR_BGSINDEX	= 0xF910,
	SCR_BGSTIMER	= 0xF920,

	SCR_SELCOMPLETE	= 0xFA10,
	SCR_SEL			= 0xFA20,
	SCR_SELFIRSTID	= 0xFA30,
	SCR_ISELCOMPLETE	= 0xFA90,
	SCR_ISEL			= 0xFAA0,
	SCR_ISELFIRSTID		= 0xFAB0,
};

enum {
	/*UIEvent*/

	SCR_EVENT_ENTERSTATE		= 0x0010,
	SCR_EVENT_LEAVESTATE		= 0x0020,

	/*Player*/
	SCR_EVENT_PLAYERBOMB	= 0x01A0,
	/*Bullet*/
	SCR_EVENT_BULLETENTERIZE	= 0x0210,
	/*0x20*/
};

struct scrKeyWord
{
	char*	word;
	DWORD	code;
};

extern scrKeyWord scrKeyTable[];

#endif