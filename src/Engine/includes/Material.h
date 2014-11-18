#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "defines.h"
#include "Structs.h"

namespace Stu
{
	namespace Engine
	{
		class ENGINE_API Material
		{
		public:
			Material();
			Material(Color ambient, Color diffuse, Color emissive, Color specular, float specPow);
			~Material();

			void SetAmbient(Color color);
			void SetAmbient(unsigned long color);
			void SetAmbient(float r, float g, float b, float a);

			void SetDiffuse(Color color);
			void SetDiffuse(unsigned long color);
			void SetDiffuse(float r, float g, float b, float a);

			void SetEmissive(Color color);
			void SetEmissive(unsigned long color);
			void SetEmissive(float r, float g, float b, float a);

			void SetSpecular(Color color);
			void SetSpecular(unsigned long color);
			void SetSpecular(float r, float g, float b, float a);

			Color GetAmbient() const;
			Color GetDiffuse() const;
			Color GetEmissive() const;
			Color GetSpecular() const;

			float GetSpecPow() const;
			void SetSpecPow(float specPow);
			
			Material operator = (const Material other);
		private:
			Color mtAmbient;
			Color mtDiffuse;
			Color mtEmissive;
			Color mtSpecular;

			float mfSpecPow;
		};
	}
}

#include "Material.inl"

#endif //__MATERIAL_H__