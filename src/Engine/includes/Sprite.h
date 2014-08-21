#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Entity.h"
#include "Texture.h"
#include "Structs.h"

namespace Stu
{
	namespace Engine
	{
		class Animation2D;

		enum ENGINE_API FlipState
		{
			none = 0,
			diagonal = 1,
			vertical = 2,
			horizontal = 4
		};

		class ENGINE_API Sprite : public Entity
		{
		public:
			Sprite(Texture::Ptr texture, Animation2D* animator,
										unsigned int x, unsigned int y, 
										unsigned int width, unsigned int height);
			Sprite();

			void SetVertexs();
			void Clone(const Sprite* copyFrom);
			void SetFrame(Frame frame);

			~Sprite();

			virtual bool Draw(Renderer* renderer);
			virtual void Update(float deltaTime);
			void SetFlipState(FlipState state);
			FlipState GetFlipState();
		protected:
			TexVertex* mptVertexs;
			Texture::Ptr mpoTexture;
		private:
			Frame msCurrentFrame;
			Animation2D* mpoAnimator;
			FlipState meFlipState;
		};
		inline FlipState operator|(FlipState a, FlipState b) 
		{
			return static_cast<FlipState>(static_cast<int>(a) | static_cast<int>(b));
		}

		inline FlipState operator&(FlipState a, FlipState b)
		{
			return static_cast<FlipState>(static_cast<int>(a) & static_cast<int>(b));
		}
	}
}

#include "Sprite.inl"

#endif //__SPRITE_H__