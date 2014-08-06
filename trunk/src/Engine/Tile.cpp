#include "includes\Tile.h"
#include "includes\Tilemap.h"
#include "includes\Renderer.h"

#define VERTEX_AMNT 4

Stu::Engine::Tile::Tile(Texture::Ptr texture, Animation2D* animator, 
						unsigned int x, unsigned int y, 
						unsigned int width, unsigned int height):
Sprite(texture, animator, x, y, width, height)
{
	mpoParent = NULL;
}

Stu::Engine::Tile::Tile()
{
	mpoParent = NULL;
}

Stu::Engine::Tile::~Tile()
{

}

void Stu::Engine::Tile::Clone(const Stu::Engine::Tile* copyFrom)
{
	Sprite::Clone(copyFrom);
	
	SetPosition(copyFrom->GetPosition());
	SetRotation(copyFrom->GetRotation());
	SetScale(copyFrom->GetScale());
}

bool Stu::Engine::Tile::Draw(Stu::Engine::Renderer* renderer)
{
	if(!mpoParent)
	{
		return true;
	}
	mpoParent->SetTransformations(renderer);
	
	renderer->Translate(GetPosition().x, GetPosition().y, GetPosition().z);
	
	renderer->RotateX(GetRotation().x);
	renderer->RotateY(GetRotation().y);
	renderer->RotateZ(GetRotation().z);

	renderer->Scale(GetScale().x, GetScale().y);

	

	if(renderer->BindTexture(mpoTexture->getTexCode()))
	{
		return true;
	}
	return renderer->Draw(mptVertexs, VERTEX_AMNT, DrawPrimitives::TriangleStrip);
}

void Stu::Engine::Tile::SetParent(Stu::Engine::Tilemap* parent)
{
	mpoParent = parent;
}
