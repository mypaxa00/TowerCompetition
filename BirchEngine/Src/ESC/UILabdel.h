#pragma once

#include "ESC.h"
#include "../AssetManager.h"
#include "../Game.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UILabel : public Component
{
public:
	SDL_Rect position;
	UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color color = { 255, 255, 255, 255 }) :
		labelText(text), labelFont(font), textColor(color)
	{
		position.x = xpos;
		position.y = ypos;
		upd();
	}
	~UILabel() {
		SDL_DestroyTexture(labelTexture);
	}

	void upd() {
		if (labelTexture != NULL)
			SDL_DestroyTexture(labelTexture);
		SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(labelFont), labelText.c_str(), textColor);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);
		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}

	void SetLabelColor(SDL_Color color) {
		textColor = color;
	}

	void SetLabelPos(int newX, int newY) {
		position.x = newX;
		position.y = newY;
	}

	void SetLabelFont(std::string font) {
		labelFont = font;
	}

	void SetLabelText(std::string text) {
		labelText = text;
	}

	Vector2D pos() {
		return Vector2D(position.x, position.y);
	}

	void draw() {
		SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
	}

private:
	
	std::string labelText;
	std::string labelFont;
	SDL_Color textColor;
	SDL_Texture* labelTexture = NULL;

};