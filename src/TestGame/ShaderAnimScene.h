#include <Shape.h>
#include <Sprite.h>
#include <Scene.h>
#include <Importer.h>
#include <Window.h>
#include <Light.h>

class Input;

class ShaderAnimScene : public Stu::Engine::Scene
{
public:
	ShaderAnimScene(Stu::Engine::Importer* importer, Input* input, Stu::Engine::Window* window);
	~ShaderAnimScene();

private:
	Input* mpoInput;
	Stu::Engine::Window* mpoWindow;
	Stu::Engine::Light* light;
	Stu::Engine::Node* mesh;
protected:
	virtual void Update(float deltaTime);
};