#include <d3dx9.h>
#include <cmath>

#include "includes\Vector3.h"

const MegaEngine::Vector3 MegaEngine::Vector3::Up(0,1,0);
const MegaEngine::Vector3 MegaEngine::Vector3::Left(1,0,0);
const MegaEngine::Vector3 MegaEngine::Vector3::Forward(0,0,-1);

inline D3DXVECTOR3 MegaEngine::Vector3::getD3DVector()
{
	D3DXVECTOR3 vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return vec;
}

inline float MegaEngine::Vector3::Magnitude()
{
	return sqrtf(x * x + y * y + z * z);
}

inline MegaEngine::Vector3 MegaEngine::Vector3::RotateAround(MegaEngine::Vector3 axis, float degrees)
{
	Vector3 normalAxis = axis.Normalized();
	Vector3 resul = (*this) * cos(degrees) + normalAxis.Cross((*this)) * sin(degrees) + normalAxis * (normalAxis.Dot((*this))) * (1 - cos(degrees));
	return resul;
}

inline MegaEngine::Vector3::Vector3(D3DXVECTOR3 vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
}

inline MegaEngine::Vector3 MegaEngine::Vector3::operator= (D3DXVECTOR3 other)
{

	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	return *this;
}

inline MegaEngine::Vector3 MegaEngine::Vector3::FromDXVec(D3DXVECTOR3 vec)
{
	MegaEngine::Vector3 out;
	out.x = vec.x;
	out.y = vec.y;
	out.z = vec.z;

	return out;
}

inline MegaEngine::Vector3 MegaEngine::Vector3::Cross(D3DXVECTOR3 leftOp,D3DXVECTOR3 rightOp)
{
	MegaEngine::Vector3 resul(leftOp.y * rightOp.z - rightOp.y * leftOp.z, rightOp.x * leftOp.z - leftOp.x * rightOp.z, leftOp.x * rightOp.y - rightOp.x * leftOp.y);
	return resul;
}

inline MegaEngine::Vector3 MegaEngine::Vector3::Cross(D3DXVECTOR3 other)
{
	Vector3 resul(this->y * other.z - other.y * this->z, other.x * this->z - this->x * other.z, this->x * other.y - other.x * this->y);
	return resul;
}

inline MegaEngine::Vector3 MegaEngine::Vector3::operator +(D3DXVECTOR3 other)
{
	Vector3 resul(this->x + other.x, this->y + other.y, this->z + other.z);
	return resul;
}

inline MegaEngine::Vector3 MegaEngine::Vector3::operator +=(D3DXVECTOR3 other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

inline MegaEngine::Vector3 MegaEngine::Vector3::operator -(D3DXVECTOR3 other)
{
	Vector3 resul(this->x - other.x, this->y - other.y, this->z - other.z);
	return resul;
}

inline MegaEngine::Vector3 MegaEngine::Vector3::operator -=(D3DXVECTOR3 other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}

inline float MegaEngine::Vector3::Distance(D3DXVECTOR3 other)
{
	return (*this - other).Magnitude();
}

inline MegaEngine::Vector3::operator D3DXVECTOR3()
{
	D3DXVECTOR3 vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return vec;
}