#include "GameObject.h"
#include "DestroyedParts.h"

DestroyedParts::DestroyedParts(const char* texturesheet, Vector _pos)
	:GameObject(texturesheet, _pos)
{

}

void DestroyedParts::Despawn()
{
	SetScale(Vector(lerp(GetScale().GetX(), 0, 1), lerp(GetScale().GetY(), 0, 1)));
}
