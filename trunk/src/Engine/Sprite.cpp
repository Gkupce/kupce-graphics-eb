#include "includes\Texture.h"
#include "includes\Renderer.h"
#include "includes\Sprite.h"

Stu::Engine::Sprite::Sprite(Texture::Ptr texture, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
	mpoTexture = texture;
	mptVertexs = NULL;
	mptVertexs = new TexVertex[4];
	if(!mptVertexs)
	{
		throw "Sprite failed to create";
	}
	//placeholder
	/*
	mpoTexture = new Texture("tink",NULL,165,465);
	height = 33;
	width = 20;
	x = 242;
	y = 5;
	*/
	// /placeholder
	float hwRatio = ((float)height / (float)width);

	//top left
	mptVertexs[0].x = 0.5f;
	mptVertexs[0].y = 0.5f * hwRatio;
	mptVertexs[0].z = 0.0f;
	mptVertexs[0].u = (float)x / (float)mpoTexture->getWidth();
	mptVertexs[0].v = (float)y / (float)mpoTexture->getHeight();
	
	//top right
	mptVertexs[1].x = -0.5f;
	mptVertexs[1].y = 0.5f * hwRatio;
	mptVertexs[1].z = 0.0f;
	mptVertexs[1].u = (float)(x + width) / (float)mpoTexture->getWidth();
	mptVertexs[1].v = (float)y / (float)mpoTexture->getHeight();
	
	//bot left
	mptVertexs[2].x = 0.5f;
	mptVertexs[2].y = -0.5f * hwRatio;
	mptVertexs[2].z = 0.0f;
	mptVertexs[2].u = (float)x / (float)mpoTexture->getWidth();
	mptVertexs[2].v = (float)(y + height) / (float)mpoTexture->getHeight();

	//bot right
	mptVertexs[3].x = -0.5f;
	mptVertexs[3].y = -0.5f * hwRatio;
	mptVertexs[3].z = 0.0f;
	mptVertexs[3].u = (float)(x + width) / (float)mpoTexture->getWidth();
	mptVertexs[3].v = (float)(y + height) / (float)mpoTexture->getHeight();
}

Stu::Engine::Sprite::~Sprite()
{
	if(mptVertexs)
	{
		delete[] mptVertexs;
		mptVertexs = NULL;
	}
}


bool Stu::Engine::Sprite::Draw(Renderer* renderer)
{
	Entity2D::Draw(renderer);

	renderer->BindTexture(mpoTexture->getTexCode());
	renderer->Draw(mptVertexs, 4, DrawPrimitives::TriangleStrip);

	return false;
}