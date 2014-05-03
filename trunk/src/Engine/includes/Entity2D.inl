inline Stu::Engine::Vector3 Stu::Engine::Entity2D::GetPosition()
{
	return moPosition;
}

inline void Stu::Engine::Entity2D::SetPosition(Stu::Engine::Vector3 position)
{
	moPosition = position;
}

inline Stu::Engine::Vector3 Stu::Engine::Entity2D::GetRotation()
{
	return moRotation;
}

inline void Stu::Engine::Entity2D::SetRotation(Stu::Engine::Vector3 rotation)
{
	moRotation = rotation;
}

inline Stu::Engine::Vector3 Stu::Engine::Entity2D::GetScale()
{
	return moScale;
}

inline void Stu::Engine::Entity2D::SetScale(Stu::Engine::Vector3 scale)
{
	moScale = scale;
}

inline void Stu::Engine::Entity2D::SetPosition(float x, float y, float z)
{
	moPosition = Vector3(x,y,z);
}

inline void Stu::Engine::Entity2D::SetRotation(float x, float y, float z)
{
	moRotation = Vector3(x,y,z);
}

inline void Stu::Engine::Entity2D::SetScale(float x, float y, float z)
{
	moScale = Vector3(x,y,z);
}