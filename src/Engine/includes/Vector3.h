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
			Vector3(const float x, const float y, const float z);

			void SetValues(const float x, const float y, const float z);
			Vector3 operator =(Vector3 other);
		
			Vector3 operator +(const Vector3 other) const;
			Vector3 operator +=(const Vector3 other);
			Vector3 operator -() const;
			Vector3 operator -(const Vector3 other) const;
			Vector3 operator -=(const Vector3 other);
			Vector3 Cross(const Vector3 other) const;
			float Dot(const Vector3 other) const;
			float Distance(const Vector3 other) const;
			bool operator ==(const Vector3 other) const;
			bool operator !=(const Vector3 other) const;

			Vector3 operator *(const float multiplier) const;
			Vector3 operator *=(const float multiplier);
		
			float Magnitude() const;
			float SqrMagnitude() const;
			Vector3 Normalized() const;
			Vector3 Project(const Vector3 axis) const;
			Vector3 RotateAround(const Vector3 axis, const float degrees) const;
			
			/*
			static Vector3 Up();
			static Vector3 Left();
			static Vector3 Forward();
			*/
			//------------------------------------------------------------------------------
			//---------------*DirectX conversions, operators and other utils*---------------
			//------------------------------------------------------------------------------
			Vector3(D3DXVECTOR3);
		
			Vector3 operator =(D3DXVECTOR3 other);
			Vector3 operator +(D3DXVECTOR3 other);
			Vector3 operator +=(D3DXVECTOR3 other);
			Vector3 operator -(D3DXVECTOR3 other);
			Vector3 operator -=(D3DXVECTOR3 other);
			
			Vector3 Cross(D3DXVECTOR3 other);
			float Distance(D3DXVECTOR3 other);
			static Vector3 Cross(D3DXVECTOR3 leftOp,D3DXVECTOR3 rightOp);
			static Vector3 FromDXVec(D3DXVECTOR3 vec);
			D3DXVECTOR3 getD3DVector();
			//------------------------------------------------------------------------------
			//------------------------------------------------------------------------------
		private:
			/*
			static const Vector3 _Up;
			static const Vector3 _Left;
			static const Vector3 _Forward;
			*/
		};
	}
}

#include "Vector3.inl"
#endif //__VECTOR3_H__