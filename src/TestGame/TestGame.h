//Engine includes
#include <Game.h>
#include <Shape.h>
#include <Sprite.h>
#include <Scene.h>

#include "CamMover.h"

class TestGame : public Stu::Engine::Game
{
private:
	Stu::Engine::Scene* mpoScene2;
	Stu::Engine::Scene* mpoScene1;
	Stu::Engine::Scene* mpoScene3;
	CamMover* camMover;
protected:
	bool OnStartUp();
	bool OnLoop();
	bool OnShutDown();
};