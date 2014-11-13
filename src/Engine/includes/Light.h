#ifndef	__LIGHT_H__
#define __LIGHT_H__

#include "Structs.h"
#include "Vector3.h"

namespace Stu
{
	namespace Engine
	{
		class Light
		{
		public:
			Light();
			~Light();

			void SetLightType(LightType type);
			void SetDiffuse(Color color);
			void SetSpecular(Color color);
			void SetAmbient(Color color);
			void SetPosition(Vector3 position);
			void SetDirection(Vector3 direction);
			void SetRange(float range);
			void SetSpotFalloff(float falloff);
			void SetAttenuation(Vector3 attenuation);
			void SetSpotInnerConeRad(float angle);
			void SetSpotOuterConeRad(float angle);

			LightType GetLightType();
			Color GetDiffuse();
			Color GetSpecular();
			Color GetAmbient();
			Vector3 GetPosition();
			Vector3 GetDirection();
			float GetRange();
			float GetSpotFalloff();
			Vector3 GetAttenuation();
			float GetSpotInnerConeRad();
			float GetSpotOuterConeRad();

			//Play with these functions to break everything
			unsigned long GetLightCode();
			void SetLightCode(unsigned long code);
		private:
			int mulLightCode;

			LightType meType;
			Color mtDiffuse;
			Color mtSpecular;
			Color mtAmbient;
			Vector3 moPosition;
			Vector3 moDirection;
			float mfRange;
			float mfSpotFalloff;
			Vector3 moAttenuation;//should never be (0,0,0) and always values greater than 0
			float mfSpotInnerConeRad;
			float mfSpotOuterConeRad;
		};
	}
}

/*
struct D3DLIGHT9 {
  D3DLIGHTTYPE  Type;
  D3DCOLORVALUE Diffuse;
  D3DCOLORVALUE Specular;
  D3DCOLORVALUE Ambient;
  D3DVECTOR     Position;
  D3DVECTOR     Direction;
  float         Range;
  float         Falloff;
  float         Attenuation0;
  float         Attenuation1;
  float         Attenuation2;
  float         Theta;
  float         Phi;
}
*/

#endif //__LIGHT_H__