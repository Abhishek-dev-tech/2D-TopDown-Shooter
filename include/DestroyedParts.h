#pragma once
#include "GameObject.h"

class DestroyedParts : public GameObject
{
public:

	DestroyedParts(const char* texturesheet, Vector _pos);
	void Despawn();

	bool IsActive()
	{
		return isActive;
	}
	void Renderer();

private:
	bool isActive;

};