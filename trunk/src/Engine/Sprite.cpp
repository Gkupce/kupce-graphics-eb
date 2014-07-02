#include "includes\Texture.h"
#include "includes\Renderer.h"
#include "includes\Sprite.h"
#include "includes\Animation2D.h"

Stu::Engine::Sprite::Sprite(Texture::Ptr texture, Stu::Engine::Animation2D* animator,
							unsigned int x, unsigned int y, 
							unsigned int width, unsigned int height)
{
	mpoAnimator = animator;
	if(mpoAnimator)
	{
		mpoAnimator->SetSprite(this);
	}

	mpoTexture = texture;
	mptVertexs = NULL;
	mptVertexs = new TexVertex[4];
	if(!mptVertexs)
	{
		throw "Sprite failed to create";
	}
	
	msCurrentFrame.x = x;
	msCurrentFrame.y = y;
	msCurrentFrame.w = width;
	msCurrentFrame.h = height;

	SetVertexs();
}

Stu::Engine::Sprite::Sprite()
{
	mpoAnimator = NULL;

	mptVertexs = NULL;
	mptVertexs = new TexVertex[4];
	if(!mptVertexs)
	{
		throw "Sprite failed to create";
	}
}

void Stu::Engine::Sprite::SetVertexs()
{
	float hwRatio = ((float)msCurrentFrame.h / (float)msCurrentFrame.w);

	//top left
	mptVertexs[0].x = 0.5f;
	mptVertexs[0].y = 0.5f * hwRatio;
	mptVertexs[0].z = 0.0f;
	mptVertexs[0].u = (float)msCurrentFrame.x / (float)mpoTexture->getWidth();
	mptVertexs[0].v = (float)msCurrentFrame.y / (float)mpoTexture->getHeight();
	
	//top right
	mptVertexs[1].x = -0.5f;
	mptVertexs[1].y = 0.5f * hwRatio;
	mptVertexs[1].z = 0.0f;
	mptVertexs[1].u = (float)(msCurrentFrame.x + msCurrentFrame.w) / (float)mpoTexture->getWidth();
	mptVertexs[1].v = (float)msCurrentFrame.y / (float)mpoTexture->getHeight();
	
	//bot left
	mptVertexs[2].x = 0.5f;
	mptVertexs[2].y = -0.5f * hwRatio;
	mptVertexs[2].z = 0.0f;
	mptVertexs[2].u = (float)msCurrentFrame.x / (float)mpoTexture->getWidth();
	mptVertexs[2].v = (float)(msCurrentFrame.y + msCurrentFrame.h) / (float)mpoTexture->getHeight();

	//bot right
	mptVertexs[3].x = -0.5f;
	mptVertexs[3].y = -0.5f * hwRatio;
	mptVertexs[3].z = 0.0f;
	mptVertexs[3].u = (float)(msCurrentFrame.x + msCurrentFrame.w) / (float)mpoTexture->getWidth();
	mptVertexs[3].v = (float)(msCurrentFrame.y + msCurrentFrame.h) / (float)mpoTexture->getHeight();
}

void Stu::Engine::Sprite::Clone(const Stu::Engine::Sprite* copyFrom)
{
	mpoTexture = copyFrom->mpoTexture;
	msCurrentFrame = Frame(copyFrom->msCurrentFrame);
	
	if(copyFrom->mpoAnimator)
	{
		mpoAnimator = new Animation2D();
		if(!mpoAnimator)
		{
			throw "out of memory cloning sprite";
		}

		mpoAnimator->Clone(*(copyFrom->mpoAnimator));
		mpoAnimator->SetSprite(this);
	}

	SetVertexs();
}

Stu::Engine::Sprite::~Sprite()
{
	if(mpoAnimator)
	{
		delete mpoAnimator;
		mpoAnimator = NULL;
	}

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

void Stu::Engine::Sprite::Update(Game* game)
{
	if(mpoAnimator)
	{
		mpoAnimator->Update(game);
	}
}

void Stu::Engine::Sprite::SetFrame(Stu::Engine::Frame frame)
{
	msCurrentFrame = frame;
	SetVertexs();
}