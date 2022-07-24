#pragma once
#include <string_view>
#include <SDL.h>
#include <SDL_image.h>

class Texture
{
public:
	~Texture();
	bool loadFromFile(std::string_view path, SDL_Renderer* gRenderer);
	void free();
	void render(SDL_Renderer* gRenderer, int x = 0, int y = 0, SDL_Rect* rect = nullptr);

	void setAlpha(Uint8 alpha);

	int getWidth();
	int getHeight();

protected:
	SDL_Texture* mTexture = nullptr;
	int mWidth = 0;
	int mHeight = 0;
};

