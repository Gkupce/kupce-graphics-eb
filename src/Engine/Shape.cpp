#include "includes\Renderer.h"
#include "includes\Shape.h"
#include "includes\Structs.h"

Stu::Engine::Shape::Shape()
{
	mptVertexs = NULL;
	mptVertexs = new ColorVertex[3];
	muiVertexCount = 3;
	if(!mptVertexs)
	{
		throw 3;
	}

	mptVertexs[0].color = 0xffff0000;
	mptVertexs[0].x = 0.0f;
	mptVertexs[0].y = 0.0f;
	mptVertexs[0].z = 0.0f;

	mptVertexs[1].color = 0xff00ff00;
	mptVertexs[1].x = 1.0f;
	mptVertexs[1].y = 0.0f;
	mptVertexs[1].z = 0.0f;

	mptVertexs[2].color = 0xff0000ff;
	mptVertexs[2].x = 0.0f;
	mptVertexs[2].y = 1.0f;
	mptVertexs[2].z = 0.0f;
}

Stu::Engine::Shape::~Shape()
{
	if(mptVertexs)
	{
		delete mptVertexs;
		mptVertexs = NULL;
	}
}

bool Stu::Engine::Shape::Draw(Renderer* renderer)
{
	if(!Entity2D::Draw(renderer))
	{
		return renderer->Draw(mptVertexs, muiVertexCount);
	}
	return true;
}