#include "GameObject.h"
#include <iostream>
#include "DestroyedParts.h"

DestroyedParts::DestroyedParts(const char* texturesheet, Vector _pos)
	:GameObject(texturesheet, _pos)
{
	isActive = false;
}

void DestroyedParts::Despawn()
{
	SetScale(Vector(lerp(GetScale().GetX(), 0, .5), lerp(GetScale().GetY(), 0, 1)));
	SetPos(Vector(-10, -10));
	isActive = false;
}

void DestroyedParts::Renderer()
{
	RenderEx(0);
}