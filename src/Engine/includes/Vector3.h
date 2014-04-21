#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include "Defines.h"

struct D3DXVECTOR3;

namespace Stu
{
	namespace Engine
	{
		class ENGINE_API Vector3
		{
		public:
			float x, y, z;

			Vector3();
			Vector3(float x, float y, float z);

			void SetValues(float x, float y, float z);
			Vector3 operator =(Vector3 other);
		
			Vector3 operator +(Vector3 other);
			Vector3 operator +=(Vector3 other);
			Vector3 operator -();
			Vector3 operator -(Vector3 other);
			Vector3 operator -=(Vector3 other);
			Vector3 Cross(Vector3 other);
			float Dot(Vector3 other);
			float Distance(Vector3 other);
			bool operator ==(Vector3 other);
			bool operator !=(Vector3 other);

			Vector3 operator *(float multiplier);
			Vector3 operator *=(float multiplier);
		
			float Magnitude();
			float SqrMagnitude();
			Vector3 Normalized();
			Vector3 Project(Vector3 axis);
			Vector3 RotateAround(Vector3 axis, float degrees);

			static const Vector3 Up;
			static const Vector3 Left;
			static const Vector3 Forward;
		
			//------------------------------------------------------------------------------
			//---------------*DirectX conversions, operators and other utils*---------------
			//------------------------------------------------------------------------------
			Vector3(D3DXVECTOR3);
		
			Vector3 operator =(D3DXVECTOR3 other);
			Vector3 operator +(D3DXVECTOR3 other);
			Vector3 operator +=(D3DXVECTOR3 other);
			Vector3 operator -(D3DXVECTOR3 other);
			Vector3 operator -=(D3DXVECTOR3 other);
			operator D3DXVECTOR3();

			Vector3 Cross(D3DXVECTOR3 other);
			float Distance(D3DXVECTOR3 other);
			static Vector3 Cross(D3DXVECTOR3 leftOp,D3DXVECTOR3 rightOp);
			static Vector3 FromDXVec(D3DXVECTOR3 vec);
			D3DXVECTOR3 getD3DVector();
			//------------------------------------------------------------------------------
			//------------------------------------------------------------------------------
		};
	}
}
#include "Vector3.inl"
#endif //__VECTOR3_H__