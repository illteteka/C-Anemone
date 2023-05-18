#include "instances.h"

#include "objects/guy.h"
#include "objects/blueguy.h"

int instancesInit()
{
	guyInit();
	blueguyInit();

	return 0;
}