#ifndef	__LIGHT_H__
#define __LIGHT_H__

#include <limits>

#include "defines.h"
#include "Structs.h"
#include "Vector3.h"

namespace Stu
{
	namespace Engine
	{
		enum LightChange
		{
			None = 0,
			Switched = 1,
			Modified = 2
		};

		class ENGINE_API Light
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
			void SwitchOn();
			void SwitchOff();

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
			bool IsOn();

			//Play with these functions to break everything
			LightChange GetChanges();
			void LightUpdated();
			unsigned long GetLightCode();
			void SetLightCode(unsigned long code);
			static unsigned long GetNewLightCode();
			static void InitLightFlags();

		private:
			typedef unsigned int LightCodeFlager;
		public:
			static const unsigned long MAX_LIGHT_AMOUNT = 512;
			static const unsigned long LIGHT_FLAGS_SIZE = sizeof(LightCodeFlager) * CHAR_BIT;
			static const unsigned long LIGHT_FLAGS_MAX_VALUE = UINT_MAX;
			static const unsigned long LIGHT_FLAGS_LENGTH = MAX_LIGHT_AMOUNT/LIGHT_FLAGS_SIZE;
			static const unsigned long LIGHT_GET_CODE_NONE = ULONG_MAX;
		private:
			static void RemoveLight(unsigned int Light);
			
			static LightCodeFlager SuiExistentLights[LIGHT_FLAGS_LENGTH];

			LightChange meChanged;
			bool mbIsOn;
			unsigned long mulLightCode;

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