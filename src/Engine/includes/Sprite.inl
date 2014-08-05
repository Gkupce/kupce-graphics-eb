inline void Stu::Engine::Sprite::SetFlipState(Stu::Engine::FlipState state)
{
	meFlipState = state;
	SetVertexs();
}

inline Stu::Engine::FlipState Stu::Engine::Sprite::GetFlipState()
{
	return meFlipState;
}