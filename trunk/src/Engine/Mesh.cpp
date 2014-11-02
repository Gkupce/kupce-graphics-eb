#include <assimp\scene.h>
#include "includes\Mesh.h"

//-------------------------------------------------------------------------------

//TEMPORARY AUXILIAR FUNCTIONS
void GenerateCubeVertexData(Stu::Engine::ColorVertex* vertexs)
{
	//top left front
	vertexs[0].x = 0.5f;
	vertexs[0].y = 0.5f;
	vertexs[0].z = 0.5f;
	vertexs[0].color.argb = 0xff0000ff;

	//top right front
	vertexs[1].x = -0.5f;
	vertexs[1].y = 0.5f;
	vertexs[1].z = 0.5f;
	vertexs[1].color.argb = 0xff0000ff;

	//bot left front
	vertexs[2].x = 0.5f;
	vertexs[2].y = -0.5f;
	vertexs[2].z = 0.5f;
	vertexs[2].color.argb = 0xff00ff00;

	//bot right front
	vertexs[3].x = -0.5f;
	vertexs[3].y = -0.5f;
	vertexs[3].z = 0.5f;
	vertexs[3].color.argb = 0xff00ff00;

	//top left back
	vertexs[4].x = 0.5f;
	vertexs[4].y = 0.5f;
	vertexs[4].z = -0.5f;
	vertexs[4].color.argb = 0xffff0000;

	//top right back
	vertexs[5].x = -0.5f;
	vertexs[5].y = 0.5f;
	vertexs[5].z = -0.5f;
	vertexs[5].color.argb = 0xffff0000;

	//bot left back
	vertexs[6].x = 0.5f;
	vertexs[6].y = -0.5f;
	vertexs[6].z = -0.5f;
	vertexs[6].color.argb = 0xffff00ff;

	//bot right back
	vertexs[7].x = -0.5f;
	vertexs[7].y = -0.5f;
	vertexs[7].z = -0.5f;
	vertexs[7].color.argb = 0xffff00ff;
}

void GenerateCubeIndexData(DWORD* indexs)
{
	indexs[0] = 0;indexs[1] = 1;indexs[2] = 2;
	indexs[3] = 1;indexs[4] = 2;indexs[5] = 3;
	indexs[6] = 1;indexs[7] = 7;indexs[8] = 3;
	indexs[9] = 1;indexs[10] = 7;indexs[11] = 5;
	indexs[12] = 4;indexs[13] = 5;indexs[14] = 6;
	indexs[15] = 5;indexs[16] = 6;indexs[17] = 7;
	indexs[18] = 0;indexs[19] = 4;indexs[20] = 6;
	indexs[21] = 0;indexs[22] = 6;indexs[23] = 2;
	indexs[24] = 2;indexs[25] = 6;indexs[26] = 3;
	indexs[27] = 6;indexs[28] = 3;indexs[29] = 7;
	indexs[30] = 0;indexs[31] = 4;indexs[32] = 1;
	indexs[33] = 4;indexs[34] = 1;indexs[35] = 5;
}

//---------------------------------------------------------------------------------------
Stu::Engine::Mesh::Mesh(const char* name):Entity(name){}
Stu::Engine::Mesh::Mesh(std::string name):Entity(name){}
Stu::Engine::Mesh::Mesh(){}

Stu::Engine::Mesh::Mesh(Renderer* renderer, aiMesh* mesh, Texture::Ptr tex)
{
	
	IndexBuffer3D* ib = NULL;
	ib = new IndexBuffer3D();
	if(!ib)
	{
		throw "Error creating index buffer for mesh";
	}
	IndexBuffer3D::Ptr indexBuffer(ib);
	mpoIndexBuffer = indexBuffer;

	VertexBuffer3D<TexVertex, TEXTURE_VERTEX>* vb = NULL;
	vb = new VertexBuffer3D<TexVertex, TEXTURE_VERTEX>();
	if(!vb)
	{
		throw "Error creating vertex buffer for mesh";
	}
	VertexBuffer3D<TexVertex, TEXTURE_VERTEX>::Ptr vertexBuffer(vb);
	mpoVertexBuffer = vertexBuffer;

	TexVertex* vertexs = NULL;
	
	vertexs = new TexVertex[mesh->mNumVertices];
	if(!vertexs)
	{
		throw "Error creating vertex data for mesh";
	}
	for(unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		vertexs[i].x = mesh->mVertices[i].x;
		vertexs[i].y = mesh->mVertices[i].y;
		vertexs[i].z = mesh->mVertices[i].z;
		
		vertexs[i].u = mesh->mTextureCoords[0][i].x;
		vertexs[i].v = mesh->mTextureCoords[0][i].y;
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

Stu::Engine::Mesh::~Mesh(){}

void Stu::Engine::Mesh::Clone(const Stu::Engine::Node* original)
{
	Node::Clone(original);

	const Mesh* originalAsMesh = NULL;
	originalAsMesh = dynamic_cast<const Mesh*>(original);
	if(!originalAsMesh) return;

	mpoIndexBuffer = originalAsMesh->mpoIndexBuffer;
	mpoVertexBuffer = originalAsMesh->mpoVertexBuffer;
	mpoTexture = originalAsMesh->mpoTexture;
}

Stu::Engine::Mesh* Stu::Engine::Mesh::Clone() const
{
	Mesh* copy = NULL;
	copy = new Mesh(GetName());
	if(!copy) return NULL;
	copy->Clone(this);

	return copy;
}

bool Stu::Engine::Mesh::Draw(Renderer* renderer)
{
	if(mpoIndexBuffer.get() == NULL) return true;
	if(!Entity::Draw(renderer))
	{
		renderer->BindTexture(mpoTexture->getTexCode());
		return renderer->Draw(mpoVertexBuffer, mpoIndexBuffer, TriangleList);
	}
	return true;
}