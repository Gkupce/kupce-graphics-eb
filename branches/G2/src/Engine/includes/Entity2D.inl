inline Stu::Engine::Vector3 Stu::Engine::Entity2D::GetPosition() const
{
	return moPosition;
}

inline void Stu::Engine::Entity2D::SetPosition(Stu::Engine::Vector3 position)
{
	moPosition = position;
}

inline Stu::Engine::Vector3 Stu::Engine::Entity2D::GetRotation() const
{
	return moRotation;
}

inline void Stu::Engine::Entity2D::SetRotation(Stu::Engine::Vector3 rotation)
{
	moRotation = rotation;
}

inline Stu::Engine::Vector3 Stu::Engine::Entity2D::GetScale() const
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

inline void Stu::Engine::Entity2D::SetAddedToDrawables(bool state)
{
	mbAddedToDrawables = state;
}

inline bool Stu::Engine::Entity2D::IsAddedToDrawables() const
{
	return mbAddedToDrawables;
}

inline void Stu::Engine::Entity2D::Update(float deltaTime)
{ }

inline void Stu::Engine::Entity2D::SetUpdateable(bool state)
{
	mbUpdateable = state;
}

inline bool Stu::Engine::Entity2D::IsUpdateable() const
{
	return mbUpdateable;
}

inline void Stu::Engine::Entity2D::CreateAABB(Vector3 max, Vector3 min)
{
	moMaxCoord = max;
	moMinCoord = min;
}

inline void Stu::Engine::Entity2D::OnCollision(Entity2D* other){}
