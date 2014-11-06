inline const Stu::Engine::Vector3 Stu::Engine::Node::GetPosition() const
{
	return moPosition;
}

inline void Stu::Engine::Node::SetPosition(Stu::Engine::Vector3 position)
{
	moPosition = position;
}

inline const Stu::Engine::Vector3 Stu::Engine::Node::GetRotation() const
{
	return moRotation;
}

inline void Stu::Engine::Node::SetRotation(Stu::Engine::Vector3 rotation)
{
	moRotation = rotation;
}

inline const Stu::Engine::Vector3 Stu::Engine::Node::GetScale() const
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

inline void Stu::Engine::Node::SetAddedToDrawables(bool state)
{
	mbAddedToDrawables = state;
}

inline bool Stu::Engine::Node::IsAddedToDrawables() const
{
	return mbAddedToDrawables;
}

//-----------------------------------------------------------------------------------------------
//Parentage methods
//-----------------------------------------------------------------------------------------------
inline Stu::Engine::Node* Stu::Engine::Node::GetParent()
{
	return mpoParent;
}

inline Stu::Engine::Node* Stu::Engine::Node::GetChild(int child)
{
	if(child < moChildren.size() && child >= 0)
		return moChildren[child];
	else
		return NULL;
}

inline void Stu::Engine::Node::SetParent(Stu::Engine::Node* parent)
{
	if(mpoParent != NULL)
	{
		mpoParent->RemoveChildInt(this);
	}
	SetParentInt(parent);
	parent->AddChildInt(this);
}

inline void Stu::Engine::Node::AddChild(Stu::Engine::Node* child)
{
	AddChildInt(child);
	child->SetParentInt(this);
}

inline int Stu::Engine::Node::GetChildCount() const
{
	return moChildren.size();
}

//----------------------------
//-Internal parentage methods-
//----------------------------
//these methods only change the internal values of the calling node

inline void Stu::Engine::Node::RemoveChildInt(Stu::Engine::Node* child)
{
	for(std::vector<Node*>::iterator it = moChildren.begin(); it != moChildren.end(); it++)
	{
		if((*it) == child)
		{//found it!
			moChildren.erase(it);
			break;//no need to keep on looping
		}
	}
}

inline void Stu::Engine::Node::SetParentInt(Stu::Engine::Node* parent)
{
	mpoParent = parent;
}

inline void Stu::Engine::Node::AddChildInt(Stu::Engine::Node* child)
{
	moChildren.push_back(child);
}


inline void Stu::Engine::Node::SetName(const std::string name)
{
	moName = name;
}

inline void Stu::Engine::Node::SetName(const char *name)
{
	moName = name;
}

inline const std::string Stu::Engine::Node::GetName() const
{
	return moName;
}

//------------------------------------------------------------------
//Quaternion
//------------------------------------------------------------------
inline const Stu::Engine::Quaternion Stu::Engine::Node::GetBaseRotation() const
{
	return moBaseRotation;
}

inline void Stu::Engine::Node::SetBaseRotation(Stu::Engine::Quaternion baseRotation)
{
	moBaseRotation.x = baseRotation.x;
	moBaseRotation.y = baseRotation.y;
	moBaseRotation.z = baseRotation.z;
	moBaseRotation.w = baseRotation.w;
}