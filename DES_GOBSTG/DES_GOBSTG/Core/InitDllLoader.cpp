#include "../Header/MainDependency.h"

#pragma init_seg(lib)

static class InitDllLoader {
public:
	InitDllLoader() 
	{
		modulehge = LoadLibraryA(DEFAULT_HGEDLLPATH);
		modulekaillera = LoadLibraryA(DEFAULT_KAILLERADLLPATH);
	}

	~InitDllLoader() 
	{
		FreeLibrary(modulehge);
		FreeLibrary(modulekaillera);
	}

private:

	HMODULE modulehge;
	HMODULE modulekaillera;

} _initDllLoader;
