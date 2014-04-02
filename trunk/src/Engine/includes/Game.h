#ifndef __GAME_H__
#define __GAME_H__

#include "includes\defines.h"

class ENGINE_API Game
{
public:
	StartUp();
	Loop();
	ShutDown();
protected:
	OnStartUp();
	OnLoop();
	OnShutDown();
};

#endif //__GAME_H__
