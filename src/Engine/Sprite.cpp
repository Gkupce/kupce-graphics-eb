
#include "includes\Renderer.h"
#include "includes\Sprite.h"

Stu::Engine::Sprite::Sprite()
{
	mptVertexs = NULL;
	mptVertexs = new TexVertex[4];
	if(!mptVertexs)
	{
		throw "Sprite failed to create";
	}

	mptVertexs[0].x = 0.5f;
	mptVertexs[0].y = 0.5f;
	mptVertexs[0].z = 0.0f;
	mptVertexs[0].u = 0.0f;
	mptVertexs[0].v = 0.0f;
	
	mptVertexs[1].x = -0.5f;
	mptVertexs[1].y = 0.5f;
	mptVertexs[1].z = 0.0f;
	mptVertexs[1].u = 1.0f;
	mptVertexs[1].v = 0.0f;
	
	mptVertexs[2].x = 0.5f;
	mptVertexs[2].y = -0.5f;
	mptVertexs[2].z = 0.0f;
	mptVertexs[2].u = 0.0f;
	mptVertexs[2].v = 1.0f;

	mptVertexs[3].x = -0.5f;
	mptVertexs[3].y = -0.5f;
	mptVertexs[3].z = 0.0f;
	mptVertexs[3].u = 1.0f;
	mptVertexs[3].v = 1.0f;
}

Stu::Engine::Sprite::~Sprite()
{
	if(mptVertexs)
	{
		delete[] mptVertexs;
		mptVertexs = NULL;
	}
}

bool firstTime = true;

bool Stu::Engine::Sprite::Draw(Renderer* renderer)
{
	if(firstTime)
	{
		firstTime = false;
		renderer->LoadTexture();
	}
	Entity2D::Draw(renderer);
	renderer->Draw(mptVertexs, 4, DrawPrimitives::TriangleStrip);

	return false;
}