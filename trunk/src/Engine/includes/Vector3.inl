inline Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

inline Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

inline void Vector3::SetValues(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

inline Vector3 Vector3::operator -()
{

	this->x -= this->x;
	this->y -= this->y;
	this->z -= this->z;
	return *this;
}

inline Vector3 Vector3::operator -(Vector3 other)
{

	Vector3 resul(this->x - other.x,
					this->y - other.y,
					this->z - other.z);
	return resul;
}

inline Vector3 Vector3::operator -=(Vector3 other)
{

	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}

inline Vector3 Vector3::operator +(Vector3 other)
{

	Vector3 resul(this->x + other.x,
					this->y + other.y,
					this->z + other.z);
	return resul;
}

inline Vector3 Vector3::operator +=(Vector3 other)
{

	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

inline Vector3 Vector3::operator *(float multiplier)
{
	Vector3 resul(this->x * multiplier,
					this->y * multiplier,
					this->z * multiplier);
	return resul;
}

inline Vector3 Vector3::operator =(Vector3 other)
{

	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	return *this;
}



inline Vector3 Vector3::operator *=(float multiplier)
{
	this->x *= multiplier;
	this->y *= multiplier;
	this->z *= multiplier;
	return *this;
}

inline bool Vector3::operator ==(Vector3 other)
{
	return ( (this->x == other.x) && (this->y == other.y) && (this->z == other.z) );
}

inline bool Vector3::operator !=(Vector3 other)
{
	return ( (this->x != other.x) || (this->y != other.y) || (this->z != other.z) );
}

inline float Vector3::SqrMagnitude()
{
	return x * x + y * y + z * z;
}

inline Vector3 Vector3::Normalized()
{
	return (*this) * (1/this->Magnitude());
}

inline Vector3 Vector3::Project(Vector3 axis)
{
	Vector3 normalAxis = axis.Normalized();
	return normalAxis * (this->Dot(normalAxis));
}

inline Vector3 Vector3::Cross(Vector3 other)
{
	Vector3 resul(this->y * other.z - other.y * this->z, other.x * this->z - this->x * other.z, this->x * other.y - other.x * this->y);
	return resul;
}

inline float Vector3::Dot(Vector3 other)
{
	return x * other.x + y * other.y + z * other.z;
}

inline float Vector3::Distance(Vector3 other)
{
	return (*this - other).Magnitude();
}