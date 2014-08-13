void inline Stu::Engine::Renderer::SetClearColor(unsigned long clearColor)
{
	mtClearColor.argb = clearColor;
}

unsigned long inline Stu::Engine::Renderer::GetClearColor()
{
	return mtClearColor.argb;
}

inline void Stu::Engine::Renderer::SetClearColor(char a, char r, char g, char b)
{
	mtClearColor.part.a = a;
	mtClearColor.part.r = r;
	mtClearColor.part.g = g;
	mtClearColor.part.b = b;
}

inline void Stu::Engine::Renderer::GetClearColor(char* a, char* r, char* g, char* b)
{
	*a = mtClearColor.part.a;
	*r = mtClearColor.part.r;
	*g = mtClearColor.part.g;
	*b = mtClearColor.part.b;
}