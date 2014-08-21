#include <Circle.h>

enum CollisionState
{
	Away,
	Entered,
	Stay,
	Exited
};

class MyCircle : public Stu::Engine::Circle
{
public:
	MyCircle();
	~MyCircle();

	virtual void Update(float deltaTime);
	virtual void OnCollision(Entity* other); 
private:
	CollisionState meCollState;
};