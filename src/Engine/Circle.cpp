#include <math.h>

#include "includes\Circle.h"
#include "includes\Renderer.h"

Stu::Engine::Circle::Circle(unsigned int faceAmount)
{
	Shape();

	miDrawPrimitive = TriangleFan;

	if(SetFaceAmount(faceAmount))
	{
		throw faceAmount;
	}
}

bool Stu::Engine::Circle::SetFaceAmount(unsigned int faceAmount)
{
	float twoPi = 3.14159f * 2;
	float degStep = twoPi / (float)faceAmount;

	mptVertexs = new ColorVertex[faceAmount + 2];
	if(!mptVertexs)
	{
		return true;
	}
	muiVertexCount = faceAmount + 2;

	Vector3 max,min;

	mptVertexs[0].color.argb = 0xff0000ff;
	mptVertexs[0].x = 0.0f;
	mptVertexs[0].y = 0.0f;
	mptVertexs[0].z = 0.0f;

	float angle = 0;

	for(unsigned int i = 1; i < faceAmount + 2; i++)
	{
		angle = i * twoPi/ faceAmount;
		mptVertexs[i].color.argb = 0xff0000ff;
		mptVertexs[i].x = sin(angle);
		mptVertexs[i].y = cos(angle);
		mptVertexs[i].z = 0.0f;

		if(mptVertexs[i].x > max.x)
		{
			max.x = mptVertexs[i].x;
		}
		if(mptVertexs[i].y > max.y)
		{
			max.y = mptVertexs[i].y;
		}
		if(mptVertexs[i].x < min.x)
		{
			min.x = mptVertexs[i].x;
		}
		if(mptVertexs[i].y < min.y)
		{
			min.y = mptVertexs[i].y;
		}
	}

	CreateAABB(max,min);

	return false;
}