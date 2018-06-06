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
		SetLabelText(labelText, labelFont);
	}
	~UILabel() {
		SDL_DestroyTexture(labelTexture);
	}

	void SetLabelText(std::string text, std::string font) {
		labelFont = font;
		SetLabelText(text);
	}

	void SetLabelText(std::string text) {
		if (labelTexture != NULL)
			SDL_DestroyTexture(labelTexture);
		SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(labelFont), text.c_str(), textColor);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);
		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}

	void SetLabelText(std::string text, std::string font, SDL_Color& newCol) {
		textColor = newCol;
		SetLabelText(text, font);
	}

	void SetLabelPos(int newX, int newY) {
		position.x = newX;
		position.y = newY;
	}

	void SetLabelText(std::string text, std::string font, SDL_Color& newCol, int newX, int newY) {
		position.x = newX;
		position.y = newY;
		textColor = newCol;
		SetLabelText(text, font);
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