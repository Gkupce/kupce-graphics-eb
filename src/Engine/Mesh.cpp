#include "includes\Mesh.h"

//-------------------------------------------------------------------------------

//TEMPORARY AUXILIAR FUNCTIONS
void GenerateCubeVertexData(Stu::Engine::ColorVertex* vertexs)
{
	//top left front
	vertexs[0].x = 0.5f;
	vertexs[0].y = 0.5f;
	vertexs[0].z = 0.5f;
	vertexs[0].color.argb = 0xff0000ff;

	//top right front
	vertexs[1].x = -0.5f;
	vertexs[1].y = 0.5f;
	vertexs[1].z = 0.5f;
	vertexs[1].color.argb = 0xff0000ff;

	//bot left front
	vertexs[2].x = 0.5f;
	vertexs[2].y = -0.5f;
	vertexs[2].z = 0.5f;
	vertexs[2].color.argb = 0xff00ff00;

	//bot right front
	vertexs[3].x = -0.5f;
	vertexs[3].y = -0.5f;
	vertexs[3].z = 0.5f;
	vertexs[3].color.argb = 0xff00ff00;

	//top left back
	vertexs[4].x = 0.5f;
	vertexs[4].y = 0.5f;
	vertexs[4].z = -0.5f;
	vertexs[4].color.argb = 0xffff0000;

	//top right back
	vertexs[5].x = -0.5f;
	vertexs[5].y = 0.5f;
	vertexs[5].z = -0.5f;
	vertexs[5].color.argb = 0xffff0000;

	//bot left back
	vertexs[6].x = 0.5f;
	vertexs[6].y = -0.5f;
	vertexs[6].z = -0.5f;
	vertexs[6].color.argb = 0xffff00ff;

	//bot right back
	vertexs[7].x = -0.5f;
	vertexs[7].y = -0.5f;
	vertexs[7].z = -0.5f;
	vertexs[7].color.argb = 0xffff00ff;
}

void GenerateCubeIndexData(DWORD* indexs)
{
	indexs[0] = 0;indexs[1] = 1;indexs[2] = 2;
	indexs[3] = 1;indexs[4] = 2;indexs[5] = 3;
	indexs[6] = 1;indexs[7] = 7;indexs[8] = 3;
	indexs[9] = 1;indexs[10] = 7;indexs[11] = 5;
	indexs[12] = 4;indexs[13] = 5;indexs[14] = 6;
	indexs[15] = 5;indexs[16] = 6;indexs[17] = 7;
	indexs[18] = 0;indexs[19] = 4;indexs[20] = 6;
	indexs[21] = 0;indexs[22] = 6;indexs[23] = 2;
	indexs[24] = 2;indexs[25] = 6;indexs[26] = 3;
	indexs[27] = 6;indexs[28] = 3;indexs[29] = 7;
	indexs[30] = 0;indexs[31] = 4;indexs[32] = 1;
	indexs[33] = 4;indexs[34] = 1;indexs[35] = 5;
}

//---------------------------------------------------------------------------------------


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

	if(renderer->InitVertexBuffer3D(mpoVertexBuffer, false, vertexs, 8))
	{
		throw "Error initializing vertex buffer";
	}

	DWORD* indexs = NULL;
	indexs = new DWORD[36];
	if(!indexs)
	{
		throw "Error creating index data for mesh";
	}

	GenerateCubeIndexData(indexs);

	if(renderer->InitIndexBuffer3D(mpoIndexBuffer, false, indexs, 36))
	{
		throw "Error initializing index buffer";
	}
	
	delete[] indexs;
	delete[] vertexs;
}

Stu::Engine::Mesh::~Mesh()
{

}

bool Stu::Engine::Mesh::Draw(Renderer* renderer)
{
	if(!Entity::Draw(renderer))
	{
		return renderer->Draw(mpoVertexBuffer, mpoIndexBuffer, TriangleList);
	}
	return true;
}