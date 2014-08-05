#include "includes\Texture.h"
#include "includes\Renderer.h"
#include "includes\Sprite.h"
#include "includes\Animation2D.h"

#define VERTEX_AMNT 4

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
	mptVertexs = new TexVertex[VERTEX_AMNT];
	if(!mptVertexs)
	{
		throw "Sprite failed to create";
	}
	
	msCurrentFrame.x = x;
	msCurrentFrame.y = y;
	msCurrentFrame.w = width;
	msCurrentFrame.h = height;
	
	meFlipState = none;
	
	SetVertexs();
}

Stu::Engine::Sprite::Sprite()
{
	mpoAnimator = NULL;

	mptVertexs = NULL;
	mptVertexs = new TexVertex[VERTEX_AMNT];
	meFlipState = none;
	if(!mptVertexs)
	{
		throw "Sprite failed to create";
	}
}

void Stu::Engine::Sprite::SetVertexs()
{
	float hwRatio = ((float)msCurrentFrame.h / (float)msCurrentFrame.w);

	float leftU = (float)msCurrentFrame.x / (float)mpoTexture->getWidth();
	float rightU = (float)(msCurrentFrame.x + msCurrentFrame.w) / (float)mpoTexture->getWidth();
	float topV = (float)msCurrentFrame.y / (float)mpoTexture->getHeight();
	float botV = (float)(msCurrentFrame.y + msCurrentFrame.h) / (float)mpoTexture->getHeight();
	
	if(static_cast<int>(meFlipState) != static_cast<int>(none))
	{
		float aux;

		if( ((static_cast<int>(meFlipState & horizontal) != static_cast<int>(none)) 
			&& (static_cast<int>(meFlipState & diagonal) == static_cast<int>(none)))
			|| (static_cast<int>(meFlipState & vertical & diagonal) != none) )
		{
			aux = leftU;
			leftU = rightU;
			rightU = aux;
		}

		if( ((static_cast<int>(meFlipState & vertical) != static_cast<int>(none)) 
			&& (static_cast<int>(meFlipState & diagonal) == static_cast<int>(none)))
			|| (static_cast<int>(meFlipState & horizontal & diagonal) != static_cast<int>(none)) )
		{
			aux = topV;
			topV = botV;
			botV = aux;
		}

	}

	if(static_cast<int>(meFlipState & diagonal) == static_cast<int>(none))
	{
		//don't change bot left with top right
		mptVertexs[1].u = rightU;
		mptVertexs[1].v = topV;
		mptVertexs[2].u = leftU;
		mptVertexs[2].v = botV;
	}
	else
	{
		//change bot left with top right
		mptVertexs[2].u = rightU;
		mptVertexs[2].v = topV;
		mptVertexs[1].u = leftU;
		mptVertexs[1].v = botV;
	}

	//top left
	mptVertexs[0].x = 0.5f;
	mptVertexs[0].y = 0.5f * hwRatio;
	mptVertexs[0].z = 0.0f;
	mptVertexs[0].u = leftU;
	mptVertexs[0].v = topV;
		

	//top right
	mptVertexs[1].x = -0.5f;
	mptVertexs[1].y = 0.5f * hwRatio;
	mptVertexs[1].z = 0.0f;
	
	//bot left
	mptVertexs[2].x = 0.5f;
	mptVertexs[2].y = -0.5f * hwRatio;
	mptVertexs[2].z = 0.0f;

	//bot right
	mptVertexs[3].x = -0.5f;
	mptVertexs[3].y = -0.5f * hwRatio;
	mptVertexs[3].z = 0.0f;
	mptVertexs[3].u = rightU;
	mptVertexs[3].v = botV;

	CreateAABB(Vector3(mptVertexs[0].x,mptVertexs[0].y,0), 
				Vector3(mptVertexs[3].x,mptVertexs[3].y,0));
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
	meFlipState = copyFrom->meFlipState;

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

	if(renderer->BindTexture(mpoTexture->getTexCode()))
	{
		return true;
	}
	
	return renderer->Draw(mptVertexs, VERTEX_AMNT, DrawPrimitives::TriangleStrip);
}

void Stu::Engine::Sprite::Update(float deltaTime)
{
	if(mpoAnimator)
	{
		mpoAnimator->Update(deltaTime);
	}
}

void Stu::Engine::Sprite::SetFrame(Stu::Engine::Frame frame)
{
	msCurrentFrame = frame;
	SetVertexs();
}