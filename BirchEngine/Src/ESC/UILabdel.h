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
	UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& color) : 
		labelText(text), labelFont(font), textColor(color)
	{
		position.x = xpos;
		position.y = ypos;
		SetLabelText(labelText, labelFont);
	}
	~UILabel() {
		SDL_DestroyTexture(labelTexture);
	}

	void SetLabelText(std::string text, std::string font) {
		if(labelTexture != NULL)
			SDL_DestroyTexture(labelTexture);
		SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(font), text.c_str(), textColor);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);
		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}

	void SetLabelText(std::string text, std::string font, SDL_Color& newCol, int newX, int newY) {
		position.x = newX;
		position.y = newY;
		textColor = newCol;
		SetLabelText(text, font);
	}

	void draw() {
		SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
	}

private:
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	SDL_Color textColor;
	SDL_Texture* labelTexture = NULL;

};