#include <Shape.h>
#include <Sprite.h>
#include <Scene.h>
#include <Importer.h>

class Input;

class TestScene2 : public Stu::Engine::Scene
{
public:
	TestScene2(Stu::Engine::Importer* importer, Input* input);
	~TestScene2();

private:
	Input* mpoInput;
	//Stu::Engine::Shape* shape;
	//Stu::Engine::Shape* shape2;
	Stu::Engine::Node* mesh;
	Stu::Engine::Node* turret;
protected:
	virtual void Update(float deltaTime);
};