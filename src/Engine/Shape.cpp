#include "includes\Renderer.h"
#include "includes\Shape.h"
#include "includes\Structs.h"

Stu::Engine::Shape::Shape()
{
	mptVertexs = NULL;
	//mptVertexs[2].rhw = mptVertexs[1].rhw = mptVertexs[0].rhw = 0.0f;
}

Stu::Engine::Shape::~Shape()
{
	if(mptVertexs)
	{
		delete[] mptVertexs;
		mptVertexs = NULL;
	}
}

bool Stu::Engine::Shape::Draw(Renderer* renderer)
{
	if(!Entity::Draw(renderer))	
	{
		renderer->UnbindTexture();
		return renderer->Draw(mptVertexs, muiVertexCount, (DrawPrimitives)miDrawPrimitive);
	}
	return true;
}


void Stu::Engine::Shape::SetColor(unsigned long color)
{
	assert(mptVertexs);
	for(unsigned int i = 0; i < muiVertexCount; i++)
	{
		mptVertexs[i].color.argb = color;
	}
}

void Stu::Engine::Shape::SetColor(char a, char r, char g, char b)
{
	assert(mptVertexs);
	for(unsigned int i = 0; i < muiVertexCount; i++)
	{
		mptVertexs[i].color.part.a = a;
		mptVertexs[i].color.part.r = r;
		mptVertexs[i].color.part.g = g;
		mptVertexs[i].color.part.b = b;
	}
}

void Stu::Engine::Shape::SetColor(int vertex, unsigned long color)
{
	assert(mptVertexs);
	assert(vertex < (int)muiVertexCount);
	mptVertexs[vertex].color.argb = color;
}

void Stu::Engine::Shape::SetColor(int vertex, char a, char r, char g, char b)
{
	assert(mptVertexs);
	assert(vertex < (int)muiVertexCount);
	mptVertexs[vertex].color.part.a = a;
	mptVertexs[vertex].color.part.r = r;
	mptVertexs[vertex].color.part.g = g;
	mptVertexs[vertex].color.part.b = b;
}

void Stu::Engine::Shape::GetColor(char* a, char* r, char* g, char* b, int vertex)
{
	assert(mptVertexs);
	assert(vertex < (int)muiVertexCount);
	*a = mptVertexs[vertex].color.part.a;
	*r = mptVertexs[vertex].color.part.r;
	*g = mptVertexs[vertex].color.part.g;
	*b = mptVertexs[vertex].color.part.b;
}

unsigned long Stu::Engine::Shape::GetColor(int vertex)
{
	assert(mptVertexs);
	assert(vertex < (int)muiVertexCount);
	return mptVertexs[vertex].color.argb;
}