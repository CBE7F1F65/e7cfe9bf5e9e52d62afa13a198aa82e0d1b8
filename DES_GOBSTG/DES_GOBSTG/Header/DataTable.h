#include "Const.h"

static class _DataTable
{
public:
	void SetFile(FILE * file);
	bool DataTableDefine();
	bool PackageTableDefine();
	bool TextureTableDefine();
	bool EffectTableDefine();
	bool SETableDefine();
	bool SceneDefineFile();
	bool CustomConstFile();
	bool SpellDefineFile();
	bool MusicDefineFile();
	bool BulletDefineFile();
	bool EnemyDefineFile();
	bool PlayerDefineFile();
	bool SpriteDefineFile();
	bool PlayerBulletDefineFile();
	bool PlayerShootDefineFile();
	bool PlayerGhostDefineFile();

public:
	FILE * file;
	char buffer[M_STRMAX];
	int tindex;
	int tint[32];
}_datatable;