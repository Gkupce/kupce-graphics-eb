#include <math.h>
#include "includes\BspPlane.h"

Stu::Engine::BspPlane::BspPlane(Vector3 normal, Vector3 point)
{
	Node::Node();
	moNormal = normal;
	moPoint = point;
}

Stu::Engine::BspPlane::BspPlane(Vector3 normal, Vector3 point, const char* name)
{
	Node::Node(name);
	moNormal = normal;
	moPoint = point;
}

Stu::Engine::BspPlane::BspPlane(Vector3 normal, Vector3 point, std::string name)
{
	Node::Node(name);
	moNormal = normal;
	moPoint = point;
}

int Stu::Engine::BspPlane::checkSide(const Node* node) const
{
	//TODO get max and min position and compare both to the plane, if both are on the same side, return the side else return 0
	//TODO FML

	//int max = sign((node->moMaxCoord + moPoint).Dot(moNormal));
	//int min = sign((node->moMinCoord + moPoint).Dot(moNormal));
	return 0;
}

int Stu::Engine::BspPlane::checkSide(const BspPlane* plane) const
{
	Vector3 otherNormal = plane->moNormal.Normalized();
	Vector3 myNormal = this->moNormal.Normalized();
	if(otherNormal == myNormal || otherNormal == -myNormal)
	{//the planes are parallel
		//TODO FML get position world
		return sign( ( (plane->moPoint + plane->GetPosition()) - (moPoint + GetPosition()) ).Dot(moNormal) );
	}
	else
	{//the planes will eventually cross themselves
		return 0;
	}
}

int sign(float number)
{//TODO make a better, more optimized sign function
	if(number > 0.001f)
	{
		return 1;
	}
	else if (number < 0.001f)
	{
		return -1;
	}
	else return 0;
}