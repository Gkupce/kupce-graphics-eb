#include <assimp\scene.h>
#include "includes\AnimatedMesh.h"
//---------------------------------------------------------------------------------------
Stu::Engine::AnimatedMesh::AnimatedMesh(const char* name):Entity(name){}
Stu::Engine::AnimatedMesh::AnimatedMesh(std::string name):Entity(name){}
Stu::Engine::AnimatedMesh::AnimatedMesh(){}

Stu::Engine::AnimatedMesh::AnimatedMesh(Renderer* renderer, aiMesh* mesh, Texture::Ptr tex)
{
	IndexBuffer3D* ib = NULL;
	ib = new IndexBuffer3D();
	if(!ib)
	{
		throw "Error creating index buffer for mesh";
	}
	IndexBuffer3D::Ptr indexBuffer(ib);
	mpoIndexBuffer = indexBuffer;

	VertexBuffer3D<TexNormalAnimVertex, TEXTURE_NORMAL_VERTEX>* vb = NULL;
	vb = new VertexBuffer3D<TexNormalAnimVertex, TEXTURE_NORMAL_VERTEX>();
	if(!vb)
	{
		throw "Error creating vertex buffer for mesh";
	}
	VertexBuffer3D<TexNormalAnimVertex, TEXTURE_NORMAL_VERTEX>::Ptr vertexBuffer(vb);
	mpoVertexBuffer = vertexBuffer;

	TexNormalAnimVertex* vertexs = NULL;
	
	vertexs = new TexNormalAnimVertex[mesh->mNumVertices];
	if(!vertexs)
	{
		throw "Error creating vertex data for mesh";
	}
	for(unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		vertexs[i].x = mesh->mVertices[i].x;
		vertexs[i].y = mesh->mVertices[i].y;
		vertexs[i].z = mesh->mVertices[i].z;
		vertexs[i].nX = mesh->mNormals[i].x;
		vertexs[i].nY = mesh->mNormals[i].y;
		vertexs[i].nZ = mesh->mNormals[i].z;


		if(tex.get() != NULL)
		{
			vertexs[i].u = mesh->mTextureCoords[0][i].x;
			vertexs[i].v = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			vertexs[i].u = vertexs[i].v = 0;
		}
	}

	if(renderer->InitVertexBuffer3D(mpoVertexBuffer, false, vertexs, mesh->mNumVertices))
	{
		throw "Error initializing vertex buffer";
	}
	
	DWORD* indexs = NULL;
	indexs = new DWORD[mesh->mNumFaces*3];
	if(!indexs)
	{
		throw "Error creating index data for mesh";
	}
	for(unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		indexs[i*3] = mesh->mFaces[i].mIndices[0];
		indexs[i*3 + 1] = mesh->mFaces[i].mIndices[1];
		indexs[i*3 + 2] = mesh->mFaces[i].mIndices[2];
	}

	if(renderer->InitIndexBuffer3D(mpoIndexBuffer, false, indexs, mesh->mNumFaces * 3))
	{
		throw "Error initializing index buffer";
	}
	
	delete[] indexs;
	delete[] vertexs;
	mpoTexture = tex;
}

Stu::Engine::AnimatedMesh::~AnimatedMesh(){}

void Stu::Engine::AnimatedMesh::Clone(const Stu::Engine::Node* original)
{
	Node::Clone(original);

	const AnimatedMesh* originalAsMesh = NULL;
	originalAsMesh = dynamic_cast<const AnimatedMesh*>(original);
	if(!originalAsMesh) return;

	moMaterial = originalAsMesh->moMaterial;
	mpoIndexBuffer = originalAsMesh->mpoIndexBuffer;
	mpoVertexBuffer = originalAsMesh->mpoVertexBuffer;
	mpoTexture = originalAsMesh->mpoTexture;
}

Stu::Engine::AnimatedMesh* Stu::Engine::AnimatedMesh::Clone() const
{
	AnimatedMesh* copy = NULL;
	copy = new AnimatedMesh(GetName());
	if(!copy) return NULL;
	copy->Clone(this);

	return copy;
}

bool Stu::Engine::AnimatedMesh::Draw(Renderer* renderer)
{
	if(mpoIndexBuffer.get() == NULL) return true;
	if(!Entity::Draw(renderer))
	{
		if(mpoTexture.get())
		{
			renderer->BindTexture(mpoTexture->getTexCode());
		}
		else
		{
			renderer->UnbindTexture();
		}
		return renderer->Draw(mpoVertexBuffer, mpoIndexBuffer, TriangleList, moMaterial, NULL);//TODO
	}
	return true;
}

void Stu::Engine::AnimatedMesh::SetMaterial(const Material mat)
{
	moMaterial = mat;
}

Stu::Engine::Material Stu::Engine::AnimatedMesh::GetMaterial() const
{
	return moMaterial;
}