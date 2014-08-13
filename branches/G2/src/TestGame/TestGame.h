//Engine includes
#include <Game.h>
#include <Shape.h>
#include <Sprite.h>
#include <Scene.h>

class TestGame : public Stu::Engine::Game
{
private:
	Stu::Engine::Scene* mpoScene2;
	Stu::Engine::Scene* mpoScene1;
protected:
	bool OnStartUp();
	bool OnLoop();
	bool OnShutDown();
};