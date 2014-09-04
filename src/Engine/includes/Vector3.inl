inline Stu::Engine::Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

inline Stu::Engine::Vector3::Vector3(const float x, const float y, const float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

inline void Stu::Engine::Vector3::SetValues(const float x, const float y, const float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

inline Stu::Engine::Vector3 Stu::Engine::Vector3::operator -() const
{
	Vector3 resul(-this->x, -this->y, -this->z);
	return resul;
}

inline Stu::Engine::Vector3 Stu::Engine::Vector3::operator -(const Stu::Engine::Vector3 other) const
{

	Vector3 resul(this->x - other.x,
					this->y - other.y,
					this->z - other.z);
	return resul;
}

inline Stu::Engine::Vector3 Stu::Engine::Vector3::operator -=(const Stu::Engine::Vector3 other)
{

	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}

inline Stu::Engine::Vector3 Stu::Engine::Vector3::operator +(const Stu::Engine::Vector3 other) const
{

	Vector3 resul(this->x + other.x,
					this->y + other.y,
					this->z + other.z);
	return resul;
}

inline Stu::Engine::Vector3 Stu::Engine::Vector3::operator +=(const Stu::Engine::Vector3 other)
{

	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

inline Stu::Engine::Vector3 Stu::Engine::Vector3::operator *(const float multiplier) const
{
	Vector3 resul(this->x * multiplier,
					this->y * multiplier,
					this->z * multiplier);
	return resul;
}

inline Stu::Engine::Vector3 Stu::Engine::Vector3::operator =(const Stu::Engine::Vector3 other)
{

	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	return *this;
}



inline Stu::Engine::Vector3 Stu::Engine::Vector3::operator *=(const float multiplier)
{
	this->x *= multiplier;
	this->y *= multiplier;
	this->z *= multiplier;
	return *this;
}

inline bool Stu::Engine::Vector3::operator ==(const Stu::Engine::Vector3 other) const
{
	return ( (this->x == other.x) && (this->y == other.y) && (this->z == other.z) );
}

inline bool Stu::Engine::Vector3::operator !=(const Stu::Engine::Vector3 other) const
{
	return ( (this->x != other.x) || (this->y != other.y) || (this->z != other.z) );
}

inline float Stu::Engine::Vector3::SqrMagnitude() const
{
	return x * x + y * y + z * z;
}

inline Stu::Engine::Vector3 Stu::Engine::Vector3::Normalized() const
{
	return (*this) * (1/this->Magnitude());
}

inline Stu::Engine::Vector3 Stu::Engine::Vector3::Project(const Stu::Engine::Vector3 axis) const
{
	Vector3 normalAxis = axis.Normalized();
	return normalAxis * (this->Dot(normalAxis));
}

inline Stu::Engine::Vector3 Stu::Engine::Vector3::Cross(const Stu::Engine::Vector3 other) const
{
	Vector3 resul(this->y * other.z - other.y * this->z, other.x * this->z - this->x * other.z, this->x * other.y - other.x * this->y);
	return resul;
}

inline float Stu::Engine::Vector3::Dot(const Stu::Engine::Vector3 other) const
{
	return x * other.x + y * other.y + z * other.z;
}

inline float Stu::Engine::Vector3::Distance(const Stu::Engine::Vector3 other) const
{
	return (*this - other).Magnitude();
}
/*
Stu::Engine::Vector3 Stu::Engine::Vector3::Up()
{
	return Vector3::_Up;
}

Stu::Engine::Vector3 Stu::Engine::Vector3::Left()
{
	return Vector3::_Left;
}

Stu::Engine::Vector3 Stu::Engine::Vector3::Forward()
{
	return Vector3::_Forward;
}
*/