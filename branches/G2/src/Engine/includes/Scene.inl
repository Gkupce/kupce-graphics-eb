inline bool Stu::Engine::Scene::IsUpdateable()
{
	return mbIsUpdateable;
}

inline bool Stu::Engine::Scene::IsDrawable()
{
	return mbIsDrawable;
}

inline void Stu::Engine::Scene::SetAddedToDrawables(bool state)
{
	mbIsDrawable = state;
}

inline void Stu::Engine::Scene::SetUpdateable(bool state)
{
	mbIsUpdateable = state;
}