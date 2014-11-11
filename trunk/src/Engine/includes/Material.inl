inline Stu::Engine::Material::Material()
{
	mtAmbient.argb = mtDiffuse.argb = mtEmissive.argb = 0;
	mtSpecular.argb = 0xffffffff;
	mfSpecPow = 1;
}

inline Stu::Engine::Material::Material(Color ambient, Color diffuse, Color emissive, Color specular, float specPow)
{
	mtAmbient.argb = ambient.argb;
	mtDiffuse.argb = diffuse.argb;
	mtEmissive.argb = emissive.argb;
	mtSpecular.argb = specular.argb;
	mfSpecPow = specPow;
}

inline Stu::Engine::Material::~Material() {}

inline void Stu::Engine::Material::SetAmbient(Color color)
{
	mtAmbient.argb = color.argb;
}

inline void Stu::Engine::Material::SetAmbient(unsigned long color)
{
	mtAmbient.argb = color;
}

inline void Stu::Engine::Material::SetAmbient(float r, float g, float b, float a)
{
	mtAmbient.part.a = a;
	mtAmbient.part.r = r;
	mtAmbient.part.g = g;
	mtAmbient.part.b = b;
}

inline Stu::Engine::Color Stu::Engine::Material::GetAmbient() const
{
	return mtAmbient;
}

inline void Stu::Engine::Material::SetDiffuse(Color color)
{
	mtDiffuse.argb = color.argb;
}

inline void Stu::Engine::Material::SetDiffuse(unsigned long color)
{
	mtDiffuse.argb = color;
}

inline void Stu::Engine::Material::SetDiffuse(float r, float g, float b, float a)
{
	mtDiffuse.part.a = a;
	mtDiffuse.part.r = r;
	mtDiffuse.part.g = g;
	mtDiffuse.part.b = b;
}

inline Stu::Engine::Color Stu::Engine::Material::GetDiffuse() const
{
	return mtDiffuse;
}

inline void Stu::Engine::Material::SetEmissive(Color color)
{
	mtEmissive.argb = color.argb;
}

inline void Stu::Engine::Material::SetEmissive(unsigned long color)
{
	mtEmissive.argb = color;
}

inline void Stu::Engine::Material::SetEmissive(float r, float g, float b, float a)
{
	mtEmissive.part.a = a;
	mtEmissive.part.r = r;
	mtEmissive.part.g = g;
	mtEmissive.part.b = b;
}

inline Stu::Engine::Color Stu::Engine::Material::GetEmissive() const
{
	return mtEmissive;
}

inline void Stu::Engine::Material::SetSpecular(Color color)
{
	mtSpecular.argb = color.argb;
}

inline void Stu::Engine::Material::SetSpecular(unsigned long color)
{
	mtSpecular.argb = color;
}

inline void Stu::Engine::Material::SetSpecular(float r, float g, float b, float a)
{
	mtSpecular.part.a = a;
	mtSpecular.part.r = r;
	mtSpecular.part.g = g;
	mtSpecular.part.b = b;
}

inline Stu::Engine::Color Stu::Engine::Material::GetSpecular() const
{
	return mtSpecular;
}

inline float Stu::Engine::Material::GetSpecPow() const
{
	return mfSpecPow;
}
inline void Stu::Engine::Material::SetSpecPow(float specPow)
{
	mfSpecPow = specPow;
}

inline Stu::Engine::Material Stu::Engine::Material::operator = (const Stu::Engine::Material other)
{
	mfSpecPow = other.mfSpecPow;
	mtAmbient.argb = other.mtAmbient.argb;
	mtDiffuse.argb = other.mtDiffuse.argb;
	mtEmissive.argb = other.mtEmissive.argb;
	mtSpecular.argb = other.mtSpecular.argb;
	return *this;
}