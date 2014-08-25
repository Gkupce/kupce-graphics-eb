inline Stu::Engine::Vector3 Stu::Engine::Entity::GetPosition() const
{
	return moPosition;
}

inline void Stu::Engine::Entity::SetPosition(Stu::Engine::Vector3 position)
{
	moPosition = position;
}

inline Stu::Engine::Vector3 Stu::Engine::Entity::GetRotation() const
{
	return moRotation;
}

inline void Stu::Engine::Entity::SetRotation(Stu::Engine::Vector3 rotation)
{
	moRotation = rotation;
}

inline Stu::Engine::Vector3 Stu::Engine::Entity::GetScale() const
{
	return moScale;
}

inline void Stu::Engine::Entity::SetScale(Stu::Engine::Vector3 scale)
{
	moScale = scale;
}

inline void Stu::Engine::Entity::SetPosition(float x, float y, float z)
{
	moPosition = Vector3(x,y,z);
}

inline void Stu::Engine::Entity::SetRotation(float x, float y, float z)
{
	moRotation = Vector3(x,y,z);
}

inline void Stu::Engine::Entity::SetScale(float x, float y, float z)
{
	moScale = Vector3(x,y,z);
}

inline void Stu::Engine::Entity::SetAddedToDrawables(bool state)
{
	mbAddedToDrawables = state;
}

inline bool Stu::Engine::Entity::IsAddedToDrawables() const
{
	return mbAddedToDrawables;
}

inline void Stu::Engine::Entity::Update(float deltaTime)
{ }

inline void Stu::Engine::Entity::SetUpdateable(bool state)
{
	mbUpdateable = state;
}

inline bool Stu::Engine::Entity::IsUpdateable() const
{
	return mbUpdateable;
}

inline void Stu::Engine::Entity::CreateAABB(Vector3 max, Vector3 min)
{
	moMaxCoord = max;
	moMinCoord = min;
}

inline void Stu::Engine::Entity::OnCollision(Entity* other){}
