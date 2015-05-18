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
	return 0;
}

int Stu::Engine::BspPlane::checkSide(const BspPlane* plane) const
{
	Vector3 otherNormal = plane->moNormal.Normalized();
	Vector3 myNormal = this->moNormal.Normalized();
	if(otherNormal == myNormal || otherNormal == -myNormal)
	{//the planes are parallel
		return 1;
	}
	else
	{//the planes will eventually cross themselves
		return 0;
	}
}