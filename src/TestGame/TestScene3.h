#include <Shape.h>
#include <Sprite.h>
#include <Scene.h>
#include <Importer.h>
#include <Window.h>
#include <Light.h>

class Input;

class TestScene3 : public Stu::Engine::Scene
{
public:
	TestScene3(Stu::Engine::Importer* importer, Input* input, Stu::Engine::Window* window);
	~TestScene3();

private:
	Input* mpoInput;
	Stu::Engine::Window* mpoWindow;
	Stu::Engine::Light* light;
	Stu::Engine::Node* mesh;
protected:
	virtual void Update(float deltaTime);
};