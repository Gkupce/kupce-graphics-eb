inline Stu::Engine::Vector3 Stu::Engine::Node::GetPosition() const
{
	return moPosition;
}

inline void Stu::Engine::Node::SetPosition(Stu::Engine::Vector3 position)
{
	moPosition = position;
}

inline Stu::Engine::Vector3 Stu::Engine::Node::GetRotation() const
{
	return moRotation;
}

inline void Stu::Engine::Node::SetRotation(Stu::Engine::Vector3 rotation)
{
	moRotation = rotation;
}

inline Stu::Engine::Vector3 Stu::Engine::Node::GetScale() const
{
	return moScale;
}

inline void Stu::Engine::Node::SetScale(Stu::Engine::Vector3 scale)
{
	moScale = scale;
}

inline void Stu::Engine::Node::SetPosition(float x, float y, float z)
{
	moPosition = Vector3(x,y,z);
}

inline void Stu::Engine::Node::SetRotation(float x, float y, float z)
{
	moRotation = Vector3(x,y,z);
}

inline void Stu::Engine::Node::SetScale(float x, float y, float z)
{
	moScale = Vector3(x,y,z);
}

inline void Stu::Engine::Node::CreateAABB(Vector3 max, Vector3 min)
{
	moMaxCoord = max;
	moMinCoord = min;
}

inline void Stu::Engine::Node::OnCollision(Node* other){}

inline void Stu::Engine::Node::Update(float deltaTime)
{ }

inline void Stu::Engine::Node::SetUpdateable(bool state)
{
	mbUpdateable = state;
}

inline bool Stu::Engine::Node::IsUpdateable() const
{
	return mbUpdateable;
}

