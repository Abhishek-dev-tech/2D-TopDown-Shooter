#pragma once
#include "GameObject.h"

class DestroyedParts : public GameObject
{
public:

	DestroyedParts(const char* texturesheet, Vector _pos);
	void Despawn();

private:

};