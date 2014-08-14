#ifndef __CAMMOVER_H__
#define __CAMMOVER_H__

namespace Stu
{
	namespace Engine
	{
		class Camera;
		class Vector3;
	}
}

class Input;

class CamMover{
public:
	CamMover(Stu::Engine::Camera* camera, Input* input);
	~CamMover();
	void OnLoop();
private:
	Stu::Engine::Camera* camera;
	Input* input;
	Stu::Engine::Vector3* camPos;
};

#endif