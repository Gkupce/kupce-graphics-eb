//Engine includes
#include <Game.h>

class TestGame : public Stu::Engine::Game
{
protected:
	bool OnStartUp();
	bool OnLoop();
	bool OnShutDown();
};