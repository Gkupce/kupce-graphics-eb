#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Defines.h"

struct D3DXMATRIX;
struct D3DXVECTOR3;

namespace Stu
{
	namespace Engine
	{
		class Renderer;

		class Vector3;

		class ENGINE_API Camera{
		public:
			static Camera* GetCamera();
			static Camera* GetCamera(float x, float y, float z);
			static void DeleteCamera();
			~Camera();

			void SetPosition(float x, float y, float z);
			void SetUpward(float x, float y, float z);
			void SetForward(float x, float y, float z);
		
			void SetPosition(Vector3 position);
			void SetUpward(Vector3 up);
			void SetForward(Vector3 forward);

			void Rotate(float x = 0, float y = 0, float z = 0);
			void Update(Renderer* renderer);

			Vector3 GetPosition();
			Vector3 GetUpward();
			Vector3 GetForward();
			Vector3 GetLeft();

		private:
			D3DXMATRIX * viewerMatrix;
			D3DXVECTOR3 * viewerPos;
			D3DXVECTOR3 * viewerUp;
			D3DXVECTOR3 * viewerForward;
			D3DXVECTOR3 * rotation;
			bool changed;

			static Camera* instance;
		
			Camera(float x = 0, float y = 0, float z = 0);

		};
	}

}

#endif // __CAMERA_H__