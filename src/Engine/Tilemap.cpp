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

bool Stu::Engine::Tilemap::Clone(const Tilemap* other)
{
	miWidth = other->miWidth;
	miHeight = other->miHeight;
	miLayerCount = other->miLayerCount;

	mpoTiles = new Tile*[miWidth * miHeight * miLayerCount];
	if(!mpoTiles)
	{
		return true;
	}

	for(int i = 0; i < miWidth * miHeight * miLayerCount; i++)
	{
		if(other->mpoTiles[i] != NULL)
		{
			Tile* tile = NULL;
			tile = new Tile();
			if(!tile)
			{
				return true;
			}
			tile->Clone(other->mpoTiles[i]);
			mpoTiles[i] = tile;
			tile->SetParent(this);
		}
		else
		{
			mpoTiles[i] = NULL;
		}
	}

	return false;
}

void Stu::Engine::Tilemap::SetTransformations(Stu::Engine::Renderer* renderer)
{
	Entity2D::Draw(renderer);
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