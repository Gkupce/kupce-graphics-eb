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

	mptVertexs[0].color = D3DCOLOR_XRGB(255,0,0);
	mptVertexs[0].x = -0.5f;
	mptVertexs[0].y = -0.5f;
	mptVertexs[0].z = 1.0f;

	mptVertexs[1].color = D3DCOLOR_XRGB(0,255,0);
	mptVertexs[1].x = -0.5f;
	mptVertexs[1].y = 0.5f;
	mptVertexs[1].z = 1.0f;

	mptVertexs[2].color = D3DCOLOR_XRGB(0,0,255);
	mptVertexs[2].x = 0.5f;
	mptVertexs[2].y = -0.5f;
	mptVertexs[2].z = 1.0f;
	//mptVertexs[2].rhw = mptVertexs[1].rhw = mptVertexs[0].rhw = 0.0f;
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