#include <Importer.h>
#include <Shape.h>
#include <Sprite.h>
#include <Scene.h>
#include <Tilemap.h>
#include <Mesh.h>

class Input;

class TestScene1 : public Stu::Engine::Scene
{
public:
	TestScene1(Stu::Engine::Importer* importer, Input* input);
	~TestScene1();

private:
	Input* mpoInput;
	Stu::Engine::Sprite* sprite2;
	Stu::Engine::Sprite* sprite;
	Stu::Engine::Tilemap* tilemap;
	
protected:
	//virtual void PreUpdate(float deltaTime);
};