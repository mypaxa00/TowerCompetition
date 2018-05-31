#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName) {
	SDL_Surface * tempSurf = IMG_Load(fileName);
	SDL_Texture * tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurf);
	SDL_FreeSurface(tempSurf);

	return tex;
}

void TextureManager::Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest,
					SDL_RendererFlip flip, double angle, SDL_Point* center)
{
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, angle, center, flip);
}
