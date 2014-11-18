inline bool Stu::Engine::Scene::IsDrawable()
{
	return mbIsDrawable;
}

inline void Stu::Engine::Scene::SetAddedToDrawables(bool state, Renderer* render)
{
	mbIsDrawable = state;
	mpoRender = render;
}
