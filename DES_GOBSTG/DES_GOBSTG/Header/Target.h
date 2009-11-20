#ifndef _TARGET_H
#define _TARGET_H
#include "Const.h"

class Target
{
public:
	static void SetValue(int index, float x, float y);
	static void ClearAll();

public:
	float x;
	float y;

public:
	static Target tar[TARGETMAX];
};

#endif