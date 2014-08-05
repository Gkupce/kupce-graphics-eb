#include "includes\Tilemap.h"
#include "includes\Renderer.h"
#include "includes\Tile.h"

Stu::Engine::Tilemap::Tilemap(int width, int height, int layerCount):Entity2D()
{
	miWidth = width;
	miHeight = height;
	miLayerCount = layerCount;

	mpoTiles = NULL;
	mpoTiles = new Tile*[miWidth*miHeight*miLayerCount];
	if(!mpoTiles)
	{
		throw "Not enough memory creating tilemap";
	}

	for(int i = 0; i < miWidth*miHeight*miLayerCount; i++)
	{
		mpoTiles[i] = NULL;
	}

	//new tiles[width, height]
}

Stu::Engine::Tilemap::Tilemap():Entity2D()
{
	mpoTiles = NULL;
	miWidth = 0;
	miHeight = 0;
	miLayerCount = 0;
}

Stu::Engine::Tilemap::~Tilemap()
{
	if(mpoTiles)
	{
		for(int i = 0; i < miWidth*miHeight*miLayerCount; i++)
		{
			if(mpoTiles[i])
			{
				delete mpoTiles[i];
				mpoTiles[i] = NULL;
			}
		}

		delete[] mpoTiles;
		mpoTiles = NULL;
	}
}

bool Stu::Engine::Tilemap::Clone(Tilemap* other)
{

	return false;
}

void Stu::Engine::Tilemap::SetTransformations(Stu::Engine::Renderer* renderer)
{
	renderer->Translate(GetPosition().x, GetPosition().y, GetPosition().z);
	
	renderer->RotateX(GetRotation().x);
	renderer->RotateY(GetRotation().y);
	renderer->RotateZ(GetRotation().z);

	renderer->Scale(GetScale().x, GetScale().y);
}

bool Stu::Engine::Tilemap::Draw(Renderer* renderer)
{
	for(int i = 0; i < miWidth*miHeight*miLayerCount; i++)
	{
		if(mpoTiles[i])
		{
			if(mpoTiles[i]->Draw(renderer))
			{
				return true;
			}
		}
	}

	return false;
}

void Stu::Engine::Tilemap::SetTile(int x, int y, int layer, Stu::Engine::Tile* tile)
{
	mpoTiles[x + miWidth * (y + layer * miHeight)] = tile;
	tile->SetParent(this);
}