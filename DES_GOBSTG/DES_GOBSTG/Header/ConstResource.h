#ifndef _CONSTRESOURCE_H
#define _CONSTRESOURCE_H

#include "Const.h"

//consts

#define LOG_STR_FILENAME		"TH_DES.log"

#define DATA_DEFAULTSTR_WIDE	"������������"
#define DATA_DEFAULTSTR			"????"

#define CONFIG_STR_FILENAME				"TH_CONFIG.ini"
#define CONFIG_STR_DEFAULTFILENAME		"hge.ini"

#define RESDEFAULT_FONTFONT				"MS Gothic"

#define RESDEFAULT_DATARESOURCE			"TH_RESOURCE.res"
#define RESDEFAULT_DATABIN				"TH_BIN.databin"
#define RESDEFAULT_DATASPELLACCESS		"TH_SPELLACCESS.databin"
#define RESDEFAULT_DATASCRIPT			"TH_SCRIPT.databin"
#define RESDEFAULT_DATACUSTOMCONST		"TH_CUSTOMCONST.table"
#define RESDEFAULT_DATASPELLDEFINE		"TH_SPELLDEFINE.table"
#define RESDEFAULT_DATAMUSICDEFINE		"TH_MUSICDEFINE.table"
#define RESDEFAULT_DATASCENEDEFINE		"TH_SCENEDEFINE.table"
#define RESDEFAULT_DATABULLETDEFINE		"TH_BULLETDEFINE.table"
#define RESDEFAULT_ENEMYDEFINE			"TH_ENEMYDEFINE.table"
#define RESDEFAULT_DATAPLAYERDEFINE		"TH_PLAYERDEFINE.table"
#define RESDEFAULT_DATASPRITEDEFINE		"TH_SPRITEDEFINE.table"
#define RESDEFAULT_DATAPLAYERBULLETDEFINE	"TH_PLAYERBULLETDEFINE.table"
#define RESDEFAULT_DATAPLAYERSHOOTDEFINE	"TH_PLAYERSHOOTDEFINE.table"
#define RESDEFAULT_DATAPLAYERGHOSTDEFINE	"TH_PLAYERGHOSTDEFINE.table"
#define RESDEFAULT_DATADATADEFINE		"TH_DataTable.table"
#define RESDEFAULT_DATAPACKAGEDEFINE	"TH_PackageTable.table"
#define RESDEFAULT_DATATEXTUREDEFINE	"TH_TextureTable.table"
#define RESDEFAULT_DATAEFFECTDEFINE		"TH_EffectTable.table"
#define RESDEFAULT_DATASEDEFINE			"TH_SETable.table"

#define RESDEFAULT_SCRIPTFOLDER		"Script/"
#define RESDEFAULT_SNAPSHOTFOLDER	"SnapShot/"
#define RESDEFAULT_REPLAYFOLDER		"Replay/"
#define RESDEFAULT_DATAFOLDER		"Data/"

#define RESDEFAULT_SCRIPTEXT7		"script"
#define RESDEFAULT_REPLAYEXT7		"rpy"

#define RESDEFAULT_RPYSIGNATURE11		"DES_TH_09X"
#define RESDEFAULT_RPYTEMPSIGN3			"rpy"
#define RESDEFAULT_RPYCOMPLETESIGN3		"RPY"
#define RESDEFAULT_RPYTAG3				"09X"

//CONFIG
#define RESCONFIGS_RESOURCE				"Resource"
#define RESCONFIGN_RESOURCEFILE			"ResourceFile"
#define RESCONFIGDEFAULT_RESOURCEFILE		""
#define RESCONFIGN_RESBINNAME			"ResourceBinName"
#define RESCONFIGDEFAULT_RESBINNAME			RESDEFAULT_DATARESOURCE
#define RESCONFIGN_PASSWORD				"Password"
#define RESCONFIGDEFAULT_PASSWORD			"h5nc"

#define RESCONFIGS_KEYSETTING_1	"KeySetting_1"
#define RESCONFIGS_KEYSETTING_2	"KeySetting_2"

#define RESCONFIGN_JOYFIRE		"JoyFire"
#define RESCONFIGDEFAULT_JOYFIRE	3
#define RESCONFIGN_JOYQUICK		"JoyQuick"
#define RESCONFIGDEFAULT_JOYQUICK	2
#define RESCONFIGN_JOYSLOW		"JoySlow"
#define RESCONFIGDEFAULT_JOYSLOW	7
#define RESCONFIGN_JOYDRAIN		"JoyDrain"
#define RESCONFIGDEFAULT_JOYDRAIN	6
#define RESCONFIGN_JOYPAUSE		"JoyPause"
#define RESCONFIGDEFAULT_JOYPAUSE	1
#define RESCONFIGN_DEBUG_JOYSPEEDUP	"Debug_JoySpeedUp"
#define RESCONFIGDEFAULT_DEBUG_JOYSPEEDUP	5

#define RESCONFIGN_KEYUP		"KeyUp"
#define RESCONFIGN_KEYDOWN		"KeyDown"
#define RESCONFIGN_KEYLEFT		"KeyLeft"
#define RESCONFIGN_KEYRIGHT		"KeyRight"
#define RESCONFIGN_KEYFIRE		"KeyFire"
#define RESCONFIGN_KEYQUICK		"KeyQuick"
#define RESCONFIGN_KEYSLOW		"KeySlow"
#define RESCONFIGN_KEYDRAIN		"KeyDrain"
#define RESCONFIGN_KEYPAUSE		"KeyPause"
#define RESCONFIGN_KEYSKIP		"KeySkip"
#define RESCONFIGN_KEYENTER		"KeyEnter"
#define RESCONFIGN_KEYESCAPE	"KeyEscape"
#define RESCONFIGN_KEYCAPTURE	"KeyCapture"

#define RESCONFIGDEFAULT_KEYUP_1		DIK_UP
#define RESCONFIGDEFAULT_KEYDOWN_1		DIK_DOWN
#define RESCONFIGDEFAULT_KEYLEFT_1		DIK_LEFT
#define RESCONFIGDEFAULT_KEYRIGHT_1		DIK_RIGHT
#define RESCONFIGDEFAULT_KEYFIRE_1		DIK_Z
#define RESCONFIGDEFAULT_KEYQUICK_1		DIK_X
#define RESCONFIGDEFAULT_KEYSLOW_1		DIK_LSHIFT
#define RESCONFIGDEFAULT_KEYDRAIN_1	DIK_C
#define RESCONFIGDEFAULT_KEYUP_2		DIK_W
#define RESCONFIGDEFAULT_KEYDOWN_2		DIK_S
#define RESCONFIGDEFAULT_KEYLEFT_2		DIK_A
#define RESCONFIGDEFAULT_KEYRIGHT_2		DIK_D
#define RESCONFIGDEFAULT_KEYFIRE_2		DIK_J
#define RESCONFIGDEFAULT_KEYQUICK_2		DIK_K
#define RESCONFIGDEFAULT_KEYSLOW_2		DIK_L
#define RESCONFIGDEFAULT_KEYDRAIN_2	DIK_I

#define RESCONFIGDEFAULT_KEYPAUSE	DIK_SPACE
#define RESCONFIGDEFAULT_KEYSKIP	DIK_LCONTROL
#define RESCONFIGDEFAULT_KEYENTER	DIK_RETURN
#define RESCONFIGDEFAULT_KEYESCAPE	DIK_F4
#define RESCONFIGDEFAULT_KEYCAPTURE	DIK_HOME

#define RESCONFIGS_VOLUME		"Volume"
#define RESCONFIGN_VOLMUSIC		"Music"
#define RESCONFIGDEFAULT_VOLMUSIC	100
#define RESCONFIGN_VOLSE		"SE"
#define RESCONFIGDEFAULT_VOLSE		100

#define RESCONFIGS_CUSTOM		"Custom"
#define RESCONFIGN_SCREENMODE	"ScreenMode"
#define RESCONFIGDEFAULT_SCREENMODE	0
#define RESCONFIGN_USERNAME		"UserName"
#define RESCONFIGDEFAULT_USERNAME	"NoName"
#define RESCONFIGN_RENDERSKIP	"RenderSkip"
#define RESCONFIGDEFAULT_RENDERSKIP	0

#define RESCONFIGS_CONNECT		"Connect"
#define RESCONFIGN_LASTIPX		"LastIPx"
#define RESCONFIGN_LASTIPPORT	"LastIPPort"

#define RESCONFIGS_CUSTOMWINDOW		"CustomWindow"
#define RESCONFIGN_DEFAULTWINDOW	"DefaultWindow"
#define RESCONFIGDEFAULT_DEFAULTWINDOW	1
#define RESCONFIGN_WINDOWLEFT		"WindowLeft"
#define RESCONFIGDEFAULT_WINDOWLEFT		0
#define RESCONFIGN_WINDOWTOP		"WindowTop"
#define RESCONFIGDEFAULT_WINDOWTOP		0
#define RESCONFIGN_WINDOWWIDTH		"WindowWidth"
#define RESCONFIGDEFAULT_WINDOWWIDTH	640
#define RESCONFIGN_WINDOWHEIGHT		"WindowHeight"
#define RESCONFIGDEFAULT_WINDOWHEIGHT	480
#define RESCONFIGN_WINDOWTOPMOST	"WindowTopMost"
#define RESCONFIGDEFAULT_WINDOWTOPMOST	0

#define RESCONFIGS_SYSTEM			"System"
#define RESCONFIGN_USE3DMODE		"Use3DMode"
#define RESCONFIGDEFAULT_USE3DMODE		0

#define RESLOADING_PCK	"Loading.pck"
#define RESLOADING_TEX	"Loading/Loading.tex"

#define RESDEFAULT_UISTR_FILENAME		"File"
#define RESDEFAULT_UISTR_USERNAME		"Name"
#define RESDEFAULT_UISTR_SCORE			"Score"
#define RESDEFAULT_UISTR_POINT			"Point Item"
#define RESDEFAULT_UISTR_FAITH			"Faith"
#define RESDEFAULT_UISTR_ALLTIME		"Play Time"
#define RESDEFAULT_UISTR_DATE			"Date"
#define RESDEFAULT_UISTR_LOST			"Lost Rate"
#define RESDEFAULT_UISTR_BORDERRATE		"Border Rate"
#define RESDEFAULT_UISTR_FASTRATE		"Fast Rate"
#define RESDEFAULT_UISTR_MODEFLAG		"Mode"
#define RESDEFAULT_UISTR_MODE_NONE		"Normal"
#define RESDEFAULT_UISTR_MODE_PRACTICE	"Stage Practice"
#define RESDEFAULT_UISTR_MODE_SPELL		"SpellCard Practice"
#define RESDEFAULT_UISTR_USINGCHARA		"Charactors"
//#define RESDEFAULT_UISTR_MAXPLAYER		"Max Player"
#define RESDEFAULT_UISTR_MISSTIME		"Miss"
#define RESDEFAULT_UISTR_BORDERTIME		"Border"
#define RESDEFAULT_UISTR_CONTINUETIME	"Continue"
#define RESDEFAULT_UISTR_GETTIME		"SpellCard Get"
#define RESDEFAULT_UISTR_PAUSETIME		"Pause"
#define RESDEFAULT_UISTR_DIFFLV			"Level"
#define RESDEFAULT_UISTR_LASTSTAGE		"Last Stage"
#define RESDEFAULT_UISTR_GRAZE			"Graze"
#define RESDEFAULT_UISTR_CONFIRM		"OK"

#define SNAPSHOT_PRIFIX		"SnapShot"
#define SNAPSHOT_EXTENSION	"bmp"

#endif