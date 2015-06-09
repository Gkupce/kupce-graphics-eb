#include <d3d9.h>
#include <d3dx9.h>

#include "includes/Node.h"
#include "includes/BspPlane.h"

//-------------------------------------------------------------------------------
//When the Collision master is a proper object, remove this line
using namespace Stu::Engine;
//-------------------------------------------------------------------------------


D3DXMATRIX GetFinalPosition(const Node* node)
{//TODO
	D3DXMATRIX matrix, tempMat;

	if(node->GetParent() == NULL)
	{//Base case
		D3DXMatrixIdentity(&matrix);
	}
	else
	{//Recursion!
		matrix = GetFinalPosition(node->GetParent());
	}

	//Translate
	D3DXMatrixTranslation(&tempMat,
							node->GetPosition().x,
							node->GetPosition().y,
							node->GetPosition().z);
	D3DXMatrixMultiply(&matrix, &matrix, &tempMat);
	//Scale
	D3DXMatrixScaling(&tempMat,
						node->GetScale().x,
						node->GetScale().y,
						node->GetScale().z);
	D3DXMatrixMultiply(&matrix, &matrix, &tempMat);
	//Rotate
	D3DXQUATERNION quaternion(	node->GetBaseRotation().x,
								node->GetBaseRotation().y,
								node->GetBaseRotation().z,
								node->GetBaseRotation().w);
	D3DXMatrixRotationQuaternion(&tempMat, &quaternion);
	D3DXMatrixMultiply(&matrix, &matrix, &tempMat);
	
	D3DXMatrixRotationX(&tempMat, node->GetRotation().x);
	D3DXMatrixMultiply(&matrix, &matrix, &tempMat);
	
	D3DXMatrixRotationY(&tempMat, node->GetRotation().y);
	D3DXMatrixMultiply(&matrix, &matrix, &tempMat);
	
	D3DXMatrixRotationZ(&tempMat, node->GetRotation().z);
	D3DXMatrixMultiply(&matrix, &matrix, &tempMat);

	return matrix;
}

bool NodeCollisions(const Node* first, const Node* second)
{//TODO
	return false;
}

int NodePlaneCollisions(const Node* node, const BspPlane* plane)
{//TODO
	return 0;
}

int PlaneCollisions(const BspPlane* first, const BspPlane* second)
{//TODO
	return 0;
}
