#include <d3d9.h>
#include <d3dx9.h>

#include "includes/Node.h"
#include "includes/BspPlane.h"

D3DXMATRIX GetFinalPosition(const Node* node)
{//TODO
	D3DXMATRIX matrix, tempMat;

	if(node->GetParent() == null)
	{//Base case
		D3DXMatrixIdentity(&matrix);
	}
	else
	{
		matrix = GetFinalPosition(node->GetParent());
	}

	//Translate
	D3DXMatrixTranslation(&tempMat,
							node->GetPosition().x,
							node->GetPosition().y,
							node->GetPosition().z);
	//Scale
	D3DXMatrixScaling(&tempMat,
						node->GetScale().x,
						node->GetScale().y,
						node->GetScale().z);
	//Rotate
	D3DXQUATERNION quaternion(	node->GetBaseRotation().x,
								node->GetBaseRotation().y,
								node->GetBaseRotation().z,
								node->GetBaseRotation().w);
	D3DXMatrixRotationQuaternion(&tempMat, &quaternion);
	//D3DXMatrixMultiply(out, in1, in2);
	D3DXMatrixRotationX(&tempMat, node->GetRotation().x);
	D3DXMatrixRotationY(&tempMat, node->GetRotation().y);
	D3DXMatrixRotationZ(&tempMat, node->GetRotation().z);

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
