#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* _texturesheet, Vector _pos)
	:Vector(_pos.GetX(), _pos.GetY())
{
	texturesheet = _texturesheet;

	position = _pos;
	position = _pos;

	srcRect.x = 0;
	srcRect.y = 0;
}

void GameObject::RenderEx(float angle)
{
	SDL_GetMouseState(&mouseX, &mouseY);


	destRect.x = position.GetX();
	destRect.y = position.GetY();
	destRect.w = srcRect.w * scale.GetX();
	destRect.h = srcRect.h * scale.GetY();

	SDL_RenderCopyEx(renderer, objTexture, &srcRect, &destRect, angle * 180/3.14 , NULL, SDL_FLIP_NONE);
}

void GameObject::SetRenderer(SDL_Renderer* _renderer)
{
	renderer = _renderer;

	objTexture = TextureManager::LoadTexture(texturesheet, renderer);

	SDL_QueryTexture(objTexture, NULL, NULL, &srcRect.w, &srcRect.h);
}

SDL_Renderer* GameObject::GetRenderer()
{
	return renderer;
}


Vector GameObject::GetPos() 
{
	return position;
}

void GameObject::SetPos(Vector value)
{
	position = value;
}

Vector GameObject::GetScale()
{
	return scale;
}

void GameObject::SetScale(Vector value)
{
	scale = value;
}

SDL_Rect GameObject::GetRect()
{
	return destRect;
}

SDL_Texture* GameObject::GetTexture()
{
	return objTexture;
}

int GameObject::GetMousePosX()
{
	return mouseX;
}

int GameObject::GetMousePosY()
{
	return mouseY;
}

