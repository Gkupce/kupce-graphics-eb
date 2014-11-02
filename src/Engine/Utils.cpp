#include <math.h>
#include "includes\Vector3.h"
#include "includes\Utils.h"

#define S_PI 3.14159265359f
#define rad2deg(x) ((x)*(180/S_PI))

Stu::Engine::Vector3 QuatToEuler(const quat_t quat)
{
	Stu::Engine::Vector3 result;
	double sqw;
	double sqx;
	double sqy;
	double sqz;
	
	double rotxrad;
	double rotyrad;
	double rotzrad;
	
	sqw = quat.w * quat.w;
	sqx = quat.x * quat.x;
	sqy = quat.y * quat.y;
	sqz = quat.z * quat.z;
	
	rotxrad = (double)atan2l(2.0 * ( quat.y * quat.z + quat.x * quat.w ) , ( -sqx - sqy + sqz + sqw ));
	rotyrad = (double)asinl(-2.0 * ( quat.x * quat.z - quat.y * quat.w ));
	rotzrad = (double)atan2l(2.0 * ( quat.x * quat.y + quat.z * quat.w ) , (  sqx - sqy - sqz + sqw ));
	
	result.x = rad2deg(rotxrad);
	result.y = rad2deg(rotyrad);
	result.z = rad2deg(rotzrad);
	
	return result;
}