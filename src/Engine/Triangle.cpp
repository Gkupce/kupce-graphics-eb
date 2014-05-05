#include "includes\Triangle.h"
#include "includes\Structs.h"
#include "includes\Renderer.h"

Stu::Engine::Triangle::Triangle()
{
	Shape();

	miDrawPrimitive = TriangleStrip;

	mptVertexs = new ColorVertex[3];
	if(!mptVertexs)
	{
		throw 3;
	}
	muiVertexCount = 3;

	mptVertexs[0].color.argb = 0xffff0000;
	mptVertexs[0].x = -0.5f;
	mptVertexs[0].y = -0.5f;
	mptVertexs[0].z = 0.0f;

	mptVertexs[1].color.argb = 0xff00ff00;
	mptVertexs[1].x = -0.5f;
	mptVertexs[1].y = 0.5f;
	mptVertexs[1].z = 0.0f;

	mptVertexs[2].color.argb = 0xff0000ff;
	//mptVertexs[2].color.part.a = 255;
	//mptVertexs[2].color.part.r = 0;
	//mptVertexs[2].color.part.g = 0;
	//mptVertexs[2].color.part.b = 255;
	mptVertexs[2].x = 0.5f;
	mptVertexs[2].y = -0.5f;
	mptVertexs[2].z = 0.0f;
}