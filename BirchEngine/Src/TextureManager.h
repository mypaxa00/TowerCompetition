#pragma once
#include "Game.h"

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest,
		SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = NULL, SDL_Point* center = NULL);
};

