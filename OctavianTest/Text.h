#pragma once

#include <string_view>
#include <SDL.h>
#include <SDL_ttf.h>

class Text
{
public:
	Text();
	~Text();
	SDL_Texture* loadFromRenderText(std::string_view text, SDL_Color color, SDL_Renderer* gRenderer);
	void free();
	void render(SDL_Renderer* gRenderer, float x, float y, double angle = 0.0, SDL_Rect* clip = nullptr, SDL_FPoint* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
protected:
	SDL_Texture* mTexture = nullptr;
	int mWidth = 0;
	int mHeight = 0;
	TTF_Font* font;
};

