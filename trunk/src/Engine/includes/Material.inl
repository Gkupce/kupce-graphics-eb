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
	mtAmbient.part.a = (unsigned char)(a * 255);
	mtAmbient.part.r = (unsigned char)(r * 255);
	mtAmbient.part.g = (unsigned char)(g * 255);
	mtAmbient.part.b = (unsigned char)(b * 255);
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
	mtDiffuse.part.a = (unsigned char)(a * 255);
	mtDiffuse.part.r = (unsigned char)(r * 255);
	mtDiffuse.part.g = (unsigned char)(g * 255);
	mtDiffuse.part.b = (unsigned char)(b * 255);
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
	mtEmissive.part.a = (unsigned char)(a * 255);
	mtEmissive.part.r = (unsigned char)(r * 255);
	mtEmissive.part.g = (unsigned char)(g * 255);
	mtEmissive.part.b = (unsigned char)(b * 255);
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
	mtSpecular.part.a = (unsigned char)(a * 255);
	mtSpecular.part.r = (unsigned char)(r * 255);
	mtSpecular.part.g = (unsigned char)(g * 255);
	mtSpecular.part.b = (unsigned char)(b * 255);
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