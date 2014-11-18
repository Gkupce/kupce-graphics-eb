#include "includes\Light.h"

Stu::Engine::Light::Light()
{
	meType = Directional;
	mtAmbient.argb = 0xffffffff;

	moDirection.SetValues(0,0,1);
	mulLightCode = LIGHT_GET_CODE_NONE;
	mbIsOn = true;
	meChanged = Modified;
	moAttenuation.SetValues(1,1,1);
	mfSpotFalloff = 1;
}

Stu::Engine::Light::~Light(){
	if(mulLightCode != LIGHT_GET_CODE_NONE)
	{
		//mark light as removed
		Light::RemoveLight(mulLightCode);
		mulLightCode = LIGHT_GET_CODE_NONE;
		//and remove from the renderer
	}
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
bool Stu::Engine::Light::IsOn()
{
	return mbIsOn;
}


void Stu::Engine::Light::SetLightType(Stu::Engine::LightType type)
{
	meChanged = (LightChange)(meChanged | Modified);
	meType = type;
}
void Stu::Engine::Light::SetDiffuse(Stu::Engine::Color color)
{
	meChanged = (LightChange)(meChanged | Modified);
	mtDiffuse = color;
}
void Stu::Engine::Light::SetSpecular(Stu::Engine::Color color)
{
	meChanged = (LightChange)(meChanged | Modified);
	mtSpecular = color;
}
void Stu::Engine::Light::SetAmbient(Stu::Engine::Color color)
{
	meChanged = (LightChange)(meChanged | Modified);
	mtAmbient = color;
}
void Stu::Engine::Light::SetPosition(Stu::Engine::Vector3 position)
{
	meChanged = (LightChange)(meChanged | Modified);
	moPosition = position;
}
void Stu::Engine::Light::SetDirection(Stu::Engine::Vector3 direction)
{
	meChanged = (LightChange)(meChanged | Modified);
	moDirection = direction;
}
void Stu::Engine::Light::SetRange(float range)
{
	meChanged = (LightChange)(meChanged | Modified);
	mfRange = range;
}
void Stu::Engine::Light::SetSpotFalloff(float falloff)
{
	meChanged = (LightChange)(meChanged | Modified);
	mfSpotFalloff = falloff;
}
void Stu::Engine::Light::SetAttenuation(Stu::Engine::Vector3 attenuation)
{
	meChanged = (LightChange)(meChanged | Modified);
	moAttenuation = attenuation;
}
void Stu::Engine::Light::SetSpotInnerConeRad(float angle)
{
	meChanged = (LightChange)(meChanged | Modified);
	mfSpotInnerConeRad = angle;
}
void Stu::Engine::Light::SetSpotOuterConeRad(float angle)
{
	meChanged = (LightChange)(meChanged | Modified);
	mfSpotOuterConeRad = angle;
}
void Stu::Engine::Light::SwitchOff()
{
	if(mbIsOn)
	{
		mbIsOn = false;
		meChanged = (LightChange)(meChanged | Switched);
	}
}
void Stu::Engine::Light::SwitchOn()
{
	if(!mbIsOn)
	{
		mbIsOn = true;
		meChanged = (LightChange)(meChanged | Switched);
	}
}

//-----------------------------------------------------------------------------------
//Light change
Stu::Engine::LightChange Stu::Engine::Light::GetChanges()
{
	return meChanged;
}

void Stu::Engine::Light::LightUpdated()
{
	meChanged = None;
}

//-----------------------------------------------------------------------------------
//Light codes

unsigned long  Stu::Engine::Light::GetLightCode()
{
	return mulLightCode;
}
void  Stu::Engine::Light::SetLightCode(unsigned long code)
{
	mulLightCode = code;
}

//---------------------------------------
//Static
unsigned int Stu::Engine::Light::SuiExistentLights[LIGHT_FLAGS_LENGTH];

unsigned long Stu::Engine::Light::GetNewLightCode()
{
	for(int i = 0; i < LIGHT_FLAGS_LENGTH; i++)
	{
		if (SuiExistentLights[i] != LIGHT_FLAGS_MAX_VALUE)
		{
			for(int j = 0; j < LIGHT_FLAGS_SIZE; j++)
			{
				if((SuiExistentLights[i] & (1 << j)) == 0)
				{
					return j + i * LIGHT_FLAGS_SIZE;
				}
			}
		}
	}

	return LIGHT_GET_CODE_NONE;
}

void  Stu::Engine::Light::InitLightFlags()
{
	for(int i = 0; i < LIGHT_FLAGS_LENGTH; i++)
	{
		SuiExistentLights[i] = 0;
	}
}

void  Stu::Engine::Light::RemoveLight(unsigned int light)
{
	SuiExistentLights[light / LIGHT_FLAGS_SIZE] = SuiExistentLights[light / LIGHT_FLAGS_SIZE] & ~(1 << (light % LIGHT_FLAGS_SIZE));
}