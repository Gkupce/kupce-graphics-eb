//Engine includes
#include <Game.h>
#include <Shape.h>
#include <Sprite.h>


class TestGame : public Stu::Engine::Game
{
private:
	Stu::Engine::Shape* shape;
	Stu::Engine::Sprite* sprite;
protected:
	bool OnStartUp();
	bool OnLoop();
	bool OnShutDown();
};