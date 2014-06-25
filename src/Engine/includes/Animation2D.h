#ifndef __ANIMATION2D_H__
#define __ANIMATION2D_H__

#include <vector>

#include "defines.h"
#include "Structs.h"

namespace Stu
{
	namespace Engine
	{
		class Sprite;
		class Game;

		class ENGINE_API Animation2D
		{
		private:
			
			float mfFrameTime;
			float mfCurrentFrameTime;
			std::vector<Frame> moFrames;
			bool mbPlaying;
			Sprite* mpoSprite;
			unsigned int muiCurrentFrame;

		public:
			Animation2D();
			Animation2D(float frameTime);
			~Animation2D();

			bool AddFrame(unsigned int x, unsigned int y, 
							unsigned int w, unsigned int h);
			void SetSprite(Sprite* sprite);
			void Update(Game* game);
			void Clone(const Animation2D& copyFrom);
		};
	}
}

#endif //__ANIMATION2D_H__