//Engine includes
#include <Game.h>
#include <Shape.h>


class TestGame : public Stu::Engine::Game
{
private:
	Stu::Engine::Shape* shape;
protected:
	bool OnStartUp();
	bool OnLoop();
	bool OnShutDown();
};