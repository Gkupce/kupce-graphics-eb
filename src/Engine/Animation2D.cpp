#include "includes\Animation2D.h"
#include "includes\Game.h"
#include "includes\Sprite.h"
#include "includes\Timer.h"

Stu::Engine::Animation2D::Animation2D()
{
	mbPlaying = true;
	mpoSprite = NULL;
	muiCurrentFrame = 0;
	mfCurrentFrameTime = 0;
}


Stu::Engine::Animation2D::Animation2D(float frameTime)
{
	mpoSprite = NULL;
	mbPlaying = true;
	muiCurrentFrame = 0;
	mfCurrentFrameTime = 0;

	mfFrameTime = frameTime;
}

Stu::Engine::Animation2D::~Animation2D()
{
	while(moFrames.size())
	{
		moFrames.pop_back();
	}
}

void Stu::Engine::Animation2D::AddFrame(unsigned int x, unsigned int y, 
				unsigned int w, unsigned int h)
{
	Frame frame;
	frame.x = x;
	frame.y = y;
	frame.h = h;
	frame.w = w;

	moFrames.push_back(frame);
}

void Stu::Engine::Animation2D::SetSprite(Stu::Engine::Sprite* sprite)
{
	mpoSprite = sprite;
}

void Stu::Engine::Animation2D::Clone(const Stu::Engine::Animation2D& copyFrom)
{
	mfFrameTime = copyFrom.mfFrameTime;
	mbPlaying = copyFrom.mbPlaying;
	muiCurrentFrame = copyFrom.muiCurrentFrame;
	mfCurrentFrameTime = copyFrom.mfCurrentFrameTime;;
	
	for(int i = 0; i < copyFrom.moFrames.size(); i++)
	{
		const Frame* pFrm = &(copyFrom.moFrames[i]); 
		moFrames.push_back(Frame(pFrm->x, pFrm->y, pFrm->w, pFrm->h));
	}
}

void Stu::Engine::Animation2D::Update(Stu::Engine::Game* game)
{
	mfCurrentFrameTime += game->GetTimer()->GetDT();
	if(mfCurrentFrameTime >= mfFrameTime)
	{
		mfCurrentFrameTime -= mfFrameTime;
		muiCurrentFrame++;
		if(muiCurrentFrame >= moFrames.size())
		{//TODO looping types
			muiCurrentFrame = 0;
		}

		mpoSprite->SetFrame(moFrames[muiCurrentFrame]);
	}
}