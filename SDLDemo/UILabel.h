#pragma once

#include "ECS.h"
#include "AssetManager.h"
#include "Game.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UILabel : public Component {
public:
	UILabel(int xPos, int yPos, std::string text, std::string font, SDL_Color& color) : text(text), font(font), color(color) {
		position.x = xPos;
		position.y = yPos;

		SetLabelText(text, font);
	}
	~UILabel() {}

	void SetLabelText(std::string newText, std::string font) {
		text = newText;
		SDL_Surface* surface = TTF_RenderText_Blended(Game::assets->GetFont(font), text.c_str(), color);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surface);
		SDL_FreeSurface(surface);

		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}

	void draw() override {
		SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
	}

	void SetTextColor(SDL_Color& newColor) {
		color = newColor;
		SetLabelText(text, font);
	}

private:
	SDL_Rect position;
	std::string text;
	std::string font;
	SDL_Color color;
	SDL_Texture* labelTexture;
};
