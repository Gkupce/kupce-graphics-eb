#include "includes\Light.h"

Stu::Engine::Light::Light()
{
	meType = Directional;
	mtAmbient.argb = 0xffffffff;

	moDirection.SetValues(0,0,1);
	mulLightCode = 0;
}

Stu::Engine::Light::~Light(){

}



Stu::Engine::LightType Stu::Engine::Light::GetLightType()
{
	return meType;
}
Stu::Engine::Color Stu::Engine::Light::GetDiffuse()
{
	return mtDiffuse;
}
Stu::Engine::Color Stu::Engine::Light::GetSpecular()
{
	return mtSpecular;
}
Stu::Engine::Color Stu::Engine::Light::GetAmbient()
{
	return mtAmbient;
}
Stu::Engine::Vector3 Stu::Engine::Light::GetPosition()
{
	return moPosition;
}
Stu::Engine::Vector3 Stu::Engine::Light::GetDirection()
{
	return moDirection;
}
float Stu::Engine::Light::GetRange()
{
	return mfRange;
}
float Stu::Engine::Light::GetSpotFalloff()
{
	return mfSpotFalloff;
}
Stu::Engine::Vector3 Stu::Engine::Light::GetAttenuation()
{
	return moAttenuation;
}
float Stu::Engine::Light::GetSpotInnerConeRad()
{
	return mfSpotInnerConeRad;
}
float Stu::Engine::Light::GetSpotOuterConeRad()
{
	return mfSpotOuterConeRad;
}

void Stu::Engine::Light::SetLightType(Stu::Engine::LightType type)
{
	meType = type;
}
void Stu::Engine::Light::SetDiffuse(Stu::Engine::Color color)
{
	mtDiffuse = color;
}
void Stu::Engine::Light::SetSpecular(Stu::Engine::Color color)
{
	mtSpecular = color;
}
void Stu::Engine::Light::SetAmbient(Stu::Engine::Color color)
{
	mtAmbient = color;
}
void Stu::Engine::Light::SetPosition(Stu::Engine::Vector3 position)
{
	moPosition = position;
}
void Stu::Engine::Light::SetDirection(Stu::Engine::Vector3 direction)
{
	moDirection = direction;
}
void Stu::Engine::Light::SetRange(float range)
{
	mfRange = range;
}
void Stu::Engine::Light::SetSpotFalloff(float falloff)
{
	mfSpotFalloff = falloff;
}
void Stu::Engine::Light::SetAttenuation(Stu::Engine::Vector3 attenuation)
{
	moAttenuation = attenuation;
}
void Stu::Engine::Light::SetSpotInnerConeRad(float angle)
{
	mfSpotInnerConeRad = angle;
}
void Stu::Engine::Light::SetSpotOuterConeRad(float angle)
{
	mfSpotOuterConeRad = angle;
}



unsigned long  Stu::Engine::Light::GetLightCode()
{
	return mulLightCode;
}
void  Stu::Engine::Light::SetLightCode(unsigned long code)
{
	mulLightCode = code;
}