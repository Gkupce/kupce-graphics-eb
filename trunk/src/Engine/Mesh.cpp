#include "includes\Mesh.h"

Stu::Engine::Mesh::Mesh(Renderer* renderer)
{
	mpoIndexBuffer = NULL;
	mpoIndexBuffer = new IndexBuffer3D();
	if(!mpoIndexBuffer)
	{
		throw "Error creating index buffer for mesh";
	}

	mpoVertexBuffer = NULL;
	mpoVertexBuffer = new VertexBuffer3D<ColorVertex, COLOR_VERTEX>();
	if(!mpoIndexBuffer)
	{
		throw "Error creating vertex buffer for mesh";
	}

	ColorVertex* vertexs = NULL;
	vertexs = new ColorVertex[8];
	if(!vertexs)
	{
		throw "Error creating vertex data for mesh";
	}
	GenerateCubeVertexData(vertexs);

	DWORD* indexs = NULL;
	indexs = new DWORD[36];
	if(!indexs)
	{
		throw "Error creating index data for mesh";
	}

	GenerateCubeIndexData(indexs);

}

Stu::Engine::Mesh::~Mesh()
{

}

bool Stu::Engine::Mesh::Draw(Renderer* renderer)
{
	return false;
}


//TEMPORARY AUXILIAR FUNCTION
void GenerateCubeVertexData(Stu::Engine::ColorVertex* vertexs)
{
	vertexs[0].x = 0.5f;
	vertexs[0].y = 0.5f;
	vertexs[0].z = 0.5f;
	vertexs[0].color.argb = 0xff0000ff;

	vertexs[1].x = -0.5f;
	vertexs[1].y = 0.5f;
	vertexs[1].z = 0.5f;
	vertexs[1].color.argb = 0xff0000ff;

	vertexs[2].x = 0.5f;
	vertexs[2].y = -0.5f;
	vertexs[2].z = 0.5f;
	vertexs[2].color.argb = 0xff0000ff;

	vertexs[3].x = -0.5f;
	vertexs[3].y = -0.5f;
	vertexs[3].z = 0.5f;
	vertexs[3].color.argb = 0xff0000ff;

	vertexs[4].x = 0.5f;
	vertexs[4].y = 0.5f;
	vertexs[4].z = -0.5f;
	vertexs[4].color.argb = 0xff0000ff;

	vertexs[5].x = -0.5f;
	vertexs[5].y = 0.5f;
	vertexs[5].z = -0.5f;
	vertexs[5].color.argb = 0xff0000ff;

	vertexs[6].x = 0.5f;
	vertexs[6].y = -0.5f;
	vertexs[6].z = -0.5f;
	vertexs[6].color.argb = 0xff0000ff;

	vertexs[7].x = -0.5f;
	vertexs[7].y = -0.5f;
	vertexs[7].z = -0.5f;
	vertexs[7].color.argb = 0xff0000ff;
}

void GenerateCubeIndexData(DWORD* indexs)
{
	//TODO
}