#include "includes\XMLParser.h"

#include "includes\Importer.h"
#include "includes\Renderer.h"
#include "includes\Texture.h"
#include "includes\Game.h"
#include "includes\Structs.h"
#include "includes\Animation2D.h"
#include "includes\Tile.h"
#include "includes\Tilemap.h"

Stu::Engine::Importer::Importer(Game* game)
{
	mpoGame = game;
}

Stu::Engine::Importer::~Importer()
{
	for(std::map<std::string, Texture::Ptr>::iterator it = moTextureMap.begin(); 
		it != moTextureMap.end(); it++)
	{
		it->second.reset();
	}
	
	for(std::map<std::string, Sprite*>::iterator it = moSpriteMap.begin(); 
		it != moSpriteMap.end(); it++)
	{
		delete (it->second);
	}

	for(std::map<std::string, Tilemap*>::iterator it = moTilemapMap.begin(); 
		it != moTilemapMap.end(); it++)
	{
		delete (it->second);
	}
}

bool Stu::Engine::Importer::LoadSprite(const XMLNode& node, const char* fileName)
{
	//<Sprite Name="name" Source="sourcePath.xml" X="x" Y="y" H="h" W="w"/>
	std::string texPath = getPath(fileName);
	const char* source = node.getAttribute("Source");
	if(source[0] == '.' && (source[1] == '/' || source[1] == '\\'))
		source = source + 2;

	texPath.append(source);
	if(!moTextureMap.count(texPath))
	{
		if(LoadTexture(texPath.c_str()))
		{//fucksies
			return true;
		}
	}

	Texture::Ptr texPtr = moTextureMap[texPath];
	Sprite* sprite = NULL;
	sprite = new Sprite(texPtr, NULL,
					atoi(node.getAttribute("X")),
					atoi(node.getAttribute("Y")),
					atoi(node.getAttribute("W")),
					atoi(node.getAttribute("H")));
	if(!sprite)
	{
		return true;
	}

	moSpriteMap[node.getAttribute("Name")] = sprite;
	return false;
}

bool Stu::Engine::Importer::LoadTexture(const char* fileName)
{
	std::string path = getPath(fileName);
	XMLNode mainNode=XMLNode::openFileHelper(fileName,"Textures");

	XMLNode resNode = mainNode.getChildNode(0);//Texture node
	//std::string name = resNode.getAttribute("Name");
	unsigned int height = atoi(resNode.getAttribute("Height"));
	unsigned int width = atoi(resNode.getAttribute("Width"));
	Color col;
	
	col.part.a = atoi(resNode.getAttribute("ColorKeyA"));
	col.part.r = atoi(resNode.getAttribute("ColorKeyR"));
	col.part.g = atoi(resNode.getAttribute("ColorKeyG"));
	col.part.b = atoi(resNode.getAttribute("ColorKeyB"));

	

	const char* source = resNode.getAttribute("Path");
	if(source[0] == '.' && (source[1] == '/' || source[1] == '\\'))
	{
		source = source + 2;
	}

	/*
	int texCode = mpoGame->GetRenderer()->LoadTexture(path.append(source).c_str(), col);
	if(texCode == -1)
	{//fucksies
		return true;
	}

	Texture::Ptr texPtr(new Texture(fileName, texCode, height, width));
	moTextureMap[fileName] = texPtr;
	
	return false;*/
	return CreateTexture(path.append(source).c_str(), fileName, col, height, width);
}

bool Stu::Engine::Importer::CreateTexture(const char* path, const char* name, Color colorKey, int height, int width)
{
	int texCode = mpoGame->GetRenderer()->LoadTexture(path, colorKey);
	if(texCode == -1)
	{//fucksies
		return true;
	}

	Texture::Ptr texPtr(new Texture(name, texCode, height, width));
	moTextureMap[name] = texPtr;
	
	return false;
}

bool Stu::Engine::Importer::LoadResource(const char* fileName)
{
	XMLNode mainNode=XMLNode::openFileHelper(fileName,"Resources");
	

	//get the first child node
	XMLNode resNode = mainNode.getChildNode(0);
	for(int i = 1; !resNode.isEmpty(); i++)
	{//loop until we get an empty node (last node + 1)
		std::string nodeName(resNode.getName());

		if(!nodeName.compare("Sprite"))
		{//Load a Sprite
			if(LoadSprite(resNode, fileName))
			{
				return true;
			}
		}
		else if(!nodeName.compare("Animation"))
		{//Load an animation
			if(LoadAnimation(resNode, fileName))
			{
				return true;
			}
		}
		/*
		else if(nodeName.compare("Sound"))
		{//Load a sound
			//if i ever get to it
		}
		*/
		resNode = mainNode.getChildNode(i);
	}


	return false;
}

std::string Stu::Engine::Importer::getPath(const char* fileName)
{
	std::string resul = fileName;

	int lastBar = resul.find_last_of("/\\");

	resul = resul.substr(0, lastBar+1);
	return resul;
}

const Stu::Engine::Sprite* Stu::Engine::Importer::GetSprite(const char* name)
{
	if(moSpriteMap.count(name))
	{
		return moSpriteMap[name];
	}
	else
	{
		return NULL;
	}
}

bool Stu::Engine::Importer::LoadAnimation(const XMLNode& node, const char* fileName)
{
	std::string texPath = getPath(fileName);
	const char* source = node.getAttribute("Source");
	if(source[0] == '.' && (source[1] == '/' || source[1] == '\\'))
		source = source + 2;

	texPath.append(source);
	if(!moTextureMap.count(texPath))
	{
		if(LoadTexture(texPath.c_str()))
		{//fucksies
			return true;
		}
	}

	XMLNode frameNode = node.getChildNode(0);
	
	if(frameNode.isEmpty())
	{
		return true;
	}
	
	Texture::Ptr texPtr = moTextureMap[texPath];
	Animation2D* anim = NULL; 
	anim = new Animation2D(atof(node.getAttribute("frameTime")));
	if(!anim)
	{
		return true;
	}

	unsigned int x = atoi(frameNode.getAttribute("X"));
	unsigned int y = atoi(frameNode.getAttribute("Y"));
	unsigned int w = atoi(frameNode.getAttribute("W"));
	unsigned int h = atoi(frameNode.getAttribute("H"));

	anim->AddFrame(x,y,w,h);

	frameNode = node.getChildNode(1);

	for(int i = 2; !frameNode.isEmpty(); i++)
	{
		anim->AddFrame(atoi(frameNode.getAttribute("X")),
						atoi(frameNode.getAttribute("Y")),
						atoi(frameNode.getAttribute("W")),
						atoi(frameNode.getAttribute("H")));

		frameNode = node.getChildNode(i);
	}
	
	Sprite* sprite = NULL;
	sprite = new Sprite(texPtr, anim,x,y,w,h);
	if(!sprite) return true;

	moSpriteMap[node.getAttribute("Name")] = sprite;
	
	return false;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
#define FLIPPED_HORIZONTALLY_FLAG 0x80000000
#define FLIPPED_VERTICALLY_FLAG 0x40000000
#define FLIPPED_DIAGONALLY_FLAG 0x20000000
#define TILE_NUMBER_FLAG 0x1FFFFFFF

bool Stu::Engine::Importer::LoadTileMap(const char* fileName)
{/**/
	if(moTilemapMap.count(fileName))
	{
		return false;
	}

	Tilemap* tilemap = NULL;
	XMLNode mainNode=XMLNode::openFileHelper(fileName,"Map");
	int width = atoi(mainNode.getAttribute("width"));
	int height = atoi(mainNode.getAttribute("height"));
	int layerCount = mainNode.nChildNode("layer");
	std::vector<int> fgids;
	std::vector<std::string> tilesetNames;
	
	

	//get the first child node
	XMLNode resNode = mainNode.getChildNode("tileset", 0);
	for(int i = 1; !resNode.isEmpty(); i++)//tileset
	{
		int margin = 0;
		int spacing = 0;
		Color colKey;
		
		int fgid = atoi(resNode.getAttribute("firstgid"));
		
		int tileWidth = atoi(resNode.getAttribute("tilewidth"));
		int tileHeight = atoi(resNode.getAttribute("tileheight"));
		
		if(resNode.isAttributeSet("spacing") != 0)
			spacing = atoi(resNode.getAttribute("spacing"));
		if(resNode.isAttributeSet("margin") != 0)
			margin = atoi(resNode.getAttribute("margin"));

		//<image>
		XMLNode imgNode = resNode.getChildNode("image", 0);
		const char* imgName = imgNode.getAttribute("source");

		std::vector<int>::iterator it = fgids.begin();
		std::vector<std::string>::iterator sit = tilesetNames.begin();
		for(; it != fgids.end(); it++)
		{
			if(*it > fgid)
				break;
			sit++;
		}
		fgids.insert(it, fgid);//must be keept in sync
		tilesetNames.insert(sit, imgName);

		if(imgNode.isAttributeSet("trans") != 0)
		{
			colKey.argb = strtoul(imgNode.getAttribute("trans"), NULL, 16);
		}
		else
		{
			colKey.argb = 0;
			colKey.part.a = 255;
		}
		int imgWidth = atoi(imgNode.getAttribute("width"));
		int imgHeight = atoi(imgNode.getAttribute("height"));
		std::string path = getPath(fileName);
		if(CreateTexture(path.append(imgName).c_str(), imgName, colKey, imgHeight, imgWidth))
		{
			return true;
		}
		Texture::Ptr texPtr = moTextureMap[imgName];
		//int tileCols = (imgWidth - margin)/(tileWidth + spacing);
		//int tileRows = (imgHeight - margin)/(tileHeight + spacing);

		char buffer[33];//buffer for itoa
		int l = 0;
		for(int k = margin; k + tileHeight <= imgHeight;k += tileHeight + spacing)
		{
			for(int j = margin; j + tileWidth <= imgWidth;j += tileWidth + spacing)
			{
				std::string imgNameStr(imgName);
				Sprite* sprite = NULL;
				sprite = new Sprite(texPtr, NULL, j, k, tileWidth, tileHeight);
				if(!sprite)
				{
					return true;
				}
				moSpriteMap[imgNameStr.append(itoa(l, buffer, 10))] = sprite;
				l++;
			}
		}
		resNode = mainNode.getChildNode("tileset", i);
	}

	

	//TODO load tileset proper
	
	tilemap = new Tilemap(width, height, layerCount);
	if(!tilemap)
	{
		return true;
	}

	resNode = mainNode.getChildNode("layer", 0);
	for(int h = 0; !resNode.isEmpty(); h++)//layers
	{
		resNode = resNode.getChildNode("data");
		
		for(int i = 0; i < height * width; i++)//tiles
		{
			const char* gid = resNode.getChildNode("tile", i).getAttribute("gid");
			unsigned long tileId = strtoul(gid,NULL,10);
			if(tileId == 0)
			{
				continue;//there is no tile here
			}

			FlipState flipState = ((tileId & FLIPPED_HORIZONTALLY_FLAG)?horizontal:none) | 
									((tileId & FLIPPED_VERTICALLY_FLAG)?vertical:none) |
									((tileId & FLIPPED_DIAGONALLY_FLAG)?diagonal:none);
			tileId = tileId & TILE_NUMBER_FLAG;//remove extra value due to ratation
			
			int fgid = 0;
			int j = 0;
			for(; j < fgids.size();j++)
			{
				if(fgids[j] <= tileId)
				{	
					fgid = fgids[j];
				}
				else
				{
					break;
				}
			}
			char buffer[30];
			Tile* tile = NULL;
			tile = new Tile();
			if(!tile) return true;

			tileId -= fgid;
			std::string tileName(tilesetNames[j-1]);
			tileName.append(ltoa(tileId, buffer, 10));
			tile->Clone((Tile*)GetSprite(tileName.c_str()));
			tile->SetFlipState(flipState);
			tile->SetPosition(-i % width, -i/width, h*10);
			tilemap->SetTile(i % width, i/width, h, tile);
					
		}
		resNode = mainNode.getChildNode("layer", h+1);
	}
	
	moTilemapMap[fileName] = tilemap;

	/**/
	return false;
}

const Stu::Engine::Tilemap* Stu::Engine::Importer::GetTileMap(const char* name)
{
	if(moTilemapMap.count(name))
	{
		return moTilemapMap[name];
	}
	else return NULL;
}

Stu::Engine::Mesh* Stu::Engine::Importer::GetMesh()
{
	return new Mesh(mpoGame->GetRenderer());
}