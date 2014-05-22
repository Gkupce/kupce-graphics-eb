#include "includes\Square.h"
#include "includes\Structs.h"
#include "includes\Renderer.h"

Stu::Engine::Square::Square()
{
	Shape();

	miDrawPrimitive = TriangleStrip;

	mptVertexs = new ColorVertex[4];
	if(!mptVertexs)
	{
		throw 4;
	}
	muiVertexCount = 4;

	mptVertexs[0].color.argb = 0xffff0000;
	mptVertexs[0].x = -0.5f;
	mptVertexs[0].y = -0.5f;
	mptVertexs[0].z = 0.0f;

	mptVertexs[1].color.argb = 0xff00ff00;
	mptVertexs[1].x = -0.5f;
	mptVertexs[1].y = 0.5f;
	mptVertexs[1].z = 0.0f;

	mptVertexs[2].color.argb = 0xff0000ff;
	mptVertexs[2].x = 0.5f;
	mptVertexs[2].y = -0.5f;
	mptVertexs[2].z = 0.0f;

	mptVertexs[3].color.argb = 0xff00ff00;
	mptVertexs[3].x = 0.5f;
	mptVertexs[3].y = 0.5f;
	mptVertexs[3].z = 0.0f;
}