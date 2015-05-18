#include <fstream>
#include <sstream>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "includes\XMLParser.h"

#include "includes\Importer.h"
#include "includes\Renderer.h"
#include "includes\Texture.h"
#include "includes\Game.h"
#include "includes\Structs.h"
#include "includes\Animation2D.h"
#include "includes\Tile.h"
#include "includes\Tilemap.h"
#include "includes\Mesh.h"

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

	for(std::map<std::string, Node*>::iterator it = moNodeMap.begin(); 
		it != moNodeMap.end(); it++)
	{
		delete (it->second);
	}

	for(std::map<std::string, Mesh*>::iterator it = moMeshMap.begin(); 
		it != moMeshMap.end(); it++)
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
	return CreateTexture(path.append(source).c_str(), fileName, col, height, width);
}

bool Stu::Engine::Importer::CreateTexture(const char* path, const char* name, Color colorKey, int height, int width)
{
	unsigned int fW, fH;//fake width and height
	int texCode = mpoGame->GetRenderer()->LoadTexture(path, colorKey, fW, fH);
	if(texCode == -1)
	{//fucksies
		return true;
	}

	Texture::Ptr texPtr(new Texture(name, texCode, height, width));
	moTextureMap[name] = texPtr;
	
	return false;
}

bool Stu::Engine::Importer::CreateTexture(const char* path, const char* name, Color colorKey)
{
	unsigned int height = 0;
	unsigned int width = 0;
	int texCode = mpoGame->GetRenderer()->LoadTexture(path, colorKey, width, height);
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
		else if(!nodeName.compare("Mesh"))
		{
			if(LoadScene(resNode, fileName))
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
	anim = new Animation2D((float)atof(node.getAttribute("frameTime")));
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
//Tiled flip flags
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
	std::stringstream stringBuilder;
	

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
		fgids.insert(it, fgid);//must be kept in sync
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
		
		int l = 0;
		for(int k = margin; k + tileHeight <= imgHeight;k += tileHeight + spacing)
		{
			for(int j = margin; j + tileWidth <= imgWidth;j += tileWidth + spacing)
			{
				Sprite* sprite = NULL;
				sprite = new Sprite(texPtr, NULL, j, k, tileWidth, tileHeight);
				if(!sprite)
				{
					return true;
				}
				stringBuilder.str(std::string());
				stringBuilder << imgName << l;
				moSpriteMap[stringBuilder.str()] = sprite;
				l++;
			}
		}
		resNode = mainNode.getChildNode("tileset", i);
	}
	
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
			unsigned int j = 0;
			for(; j < fgids.size();j++)
			{
				if((unsigned long)fgids[j] <= tileId)
				{	
					fgid = fgids[j];
				}
				else
				{
					break;
				}
			}
			Tile* tile = NULL;
			tile = new Tile();
			if(!tile) return true;

			tileId -= fgid;

			stringBuilder.str(std::string());
			stringBuilder << tilesetNames[j-1] << tileId;
			tile->Clone((Tile*)GetSprite(stringBuilder.str().c_str()));
			tile->SetFlipState(flipState);
			tile->SetPosition((float)(-i % width), (float)(-i/width), (float)(h*10));
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

Stu::Engine::Node* Stu::Engine::Importer::GetMesh(const char* name)
{//TODO
	if(moNodeMap.count(name))
	{
		return moNodeMap[name];
	}
	else return NULL;
}

bool Stu::Engine::Importer::LoadScene(const XMLNode& xmlNode, const char* fileName)
{//TODO
	std::string meshPath = getPath(fileName);
	std::stringstream stringBuilder;

	const char* source = xmlNode.getAttribute("Source");
	if(source[0] == '.' && (source[1] == '/' || source[1] == '\\'))
		source = source + 2;
	meshPath.append(source);
	
	std::ifstream fin(meshPath.c_str());
    if(!fin.fail()) {
        fin.close();
    }
    else{
        printf("Couldn't open file: %s\n", meshPath.c_str());
        return true;
    }

	std::string nodeName = xmlNode.getAttribute("Name");

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(meshPath.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
	if(!scene)
	{
		return true;
	}
	
	LoadSceneTextures(scene, nodeName, fileName);

	for(unsigned int i = 0; i < scene->mNumMeshes; i++)
	{
		stringBuilder.str(std::string());
		stringBuilder << nodeName << "_" << i;

		aiMesh* mesh = scene->mMeshes[i];
		if(LoadMesh(mesh, stringBuilder.str(), nodeName))
		{
			return true;
		}
	}

	const char* bspBaseName = NULL;

	if(xmlNode.isAttributeSet("bspBaseName"))
	{
		bspBaseName = xmlNode.getAttribute("bspBaseName");
	}

	Stu::Engine::Node* resultNode = LoadNodeStructure(scene->mRootNode, nodeName, bspBaseName);
	if(!resultNode) return true;
	moNodeMap[nodeName] = resultNode;

	return false;
}

bool Stu::Engine::Importer::LoadSceneTextures(const aiScene* scene, std::string name, const char* fileName)
{
	std::ostringstream stringBuilder;
	std::string basePath = getPath(fileName);

	aiString* texFileName = NULL;
	texFileName = new aiString();
	if(!texFileName) return true;
	
	for(unsigned int i = 0; i < scene->mNumMaterials; i++)
	{
		//std::string texName = name;
		/*char num[33];
		sprintf(num, "_TEX_%i", i);
		texName.append(num);*/
		stringBuilder.str(std::string());
		stringBuilder << name << "_TEX_" << i;
		if(moTextureMap.count(stringBuilder.str()) > 0)
		{//does it already exist?
			continue;
		}

		aiMaterial* mat = scene->mMaterials[i];
		//------------------------
		//Texture
		if(mat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			Color colKey;
			colKey.argb = 0;
			mat->GetTexture(aiTextureType_DIFFUSE, 0, texFileName);
			
			std::string texPath = "";
			texPath.append(basePath);
			texPath.append(texFileName->C_Str());

			if(CreateTexture(texPath.c_str(), stringBuilder.str().c_str(), colKey))
			{
				delete texFileName;
				return true;
			}
		}
		//------------------------
		//Material
		/*texName = name;
		sprintf(num, "_MAT_%i", i);
		texName.append(num);*/
		stringBuilder.str(std::string());
		stringBuilder << name << "_MAT_" << i;

		Material material;
		aiColor3D col;
		if(mat->Get(AI_MATKEY_COLOR_AMBIENT, col) == AI_SUCCESS)
		{//material contains color ambient
			material.SetAmbient(col.r, col.g, col.b, 1);
		}

		if(mat->Get(AI_MATKEY_COLOR_DIFFUSE, col) == AI_SUCCESS)
		{//material contains color diffuse
			material.SetDiffuse(col.r, col.g, col.b, 1);
		}
		if(mat->Get(AI_MATKEY_COLOR_EMISSIVE, col) == AI_SUCCESS)
		{//material contains color emissive
			material.SetEmissive(col.r, col.g, col.b, 1);
		}
		float specPow = 1;
		if(mat->Get(AI_MATKEY_SHININESS_STRENGTH, specPow) == AI_SUCCESS)
		{//material contains color specular
			material.SetSpecPow(specPow);
		}
		moMatMap[stringBuilder.str()] = material;
	}
	delete texFileName;
	return false;
}

bool Stu::Engine::Importer::LoadMesh(aiMesh* mesh, std::string meshName, std::string nodeName)
{
	if(moMeshMap.count(meshName)) return true;//mesh already loaded
	std::ostringstream stringBuilder;
	stringBuilder << nodeName << "_TEX_" << (int)(mesh->mMaterialIndex);
	Texture::Ptr tex;
	if(moTextureMap.count(stringBuilder.str()) != 0)
	{
		tex = moTextureMap[stringBuilder.str()];
	}
	
	Mesh* myMesh = NULL;
	myMesh = new Mesh(mpoGame->GetRenderer(), mesh, tex);
	if(!myMesh)
	{
		return true;
	}
	stringBuilder.str(std::string());
	stringBuilder << nodeName << "_MAT_" << mesh->mMaterialIndex;
	if(moMatMap.count(stringBuilder.str()) == 0)
	{
		//return true;
		Material defMat;
		defMat.SetAmbient(1,1,1,1);
		defMat.SetDiffuse(1,1,1,1);
		defMat.SetSpecular(1,1,1,1);
		defMat.SetEmissive(0,0,0,0);
		defMat.SetSpecPow(1);
		myMesh->SetMaterial(defMat);
	}
	else
	{
		myMesh->SetMaterial(moMatMap[stringBuilder.str()]);
	}
	moMeshMap[meshName] = myMesh;
	return false;
}

Stu::Engine::Node* Stu::Engine::Importer::LoadNodeStructure(const aiNode* node, std::string name, const char* bspBaseName)
{
	//TODO check for bsp plane
	Stu::Engine::Node* current = NULL;
	if(node->mNumMeshes > 0)
	{
		std::stringstream stringBuilder;
		if(node->mNumMeshes == 1)
		{
			current = new Mesh(node->mName.C_Str());
			if(!current) return NULL;

			stringBuilder.str(std::string());
			stringBuilder << name << "_" << node->mMeshes[0];
			if(moMeshMap.count(stringBuilder.str()) == 1)
				((Mesh*)current)->Clone(moMeshMap[stringBuilder.str()]);
		}
		else
		{
			current = new Node(node->mName.C_Str());
			if(!current) return NULL;

			for(unsigned int i = 0; i < node->mNumMeshes; i++)
			{
				Stu::Engine::Mesh* currentMesh = NULL;
				
				stringBuilder.str(std::string());
				stringBuilder << node->mName.C_Str() << "_" << i;
				
				currentMesh = new Mesh(stringBuilder.str());
				if(!currentMesh)
				{
					delete current;
					return NULL;
				}

				stringBuilder.str(std::string());
				stringBuilder << node->mMeshes[0] << "_" << i;
				
				if(moMeshMap.count(stringBuilder.str()) == 1)
					currentMesh->Clone(moMeshMap[stringBuilder.str()]);
			}
		}
	}
	else
	{
		current = new Node(node->mName.C_Str());
	}

	aiVector3D pos, scale;
	aiQuaternion rot;
	node->mTransformation.Decompose(scale, rot, pos);

	current->SetPosition(pos.x, pos.y, pos.z);
	current->SetScale(scale.x, scale.y, scale.z);
	
	Quaternion quat(rot.x,rot.y,rot.z,rot.w);
	/*qRot.w = rot.w;
	qRot.x = rot.x;
	qRot.y = rot.y;
	qRot.z = rot.z;*/
	current->SetBaseRotation(quat);

	for(unsigned int i = 0; i < node->mNumChildren; i++)
	{
		Stu::Engine::Node* child = LoadNodeStructure(node->mChildren[i], name);
		if(!child) 
		{
			delete current;
			return NULL;
		}
		current->AddChild(child);
	}
	return current;
}