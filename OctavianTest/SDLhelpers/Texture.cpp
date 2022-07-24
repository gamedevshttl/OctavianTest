#include "Texture.h"

Texture::~Texture()
{
	free();
}

bool Texture::loadFromFile(std::string_view path, SDL_Renderer* gRenderer)
{
	free();

	SDL_Surface* loadedSurface = IMG_Load(path.data());

	if (!loadedSurface)
		return false;

	mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

	if (!mTexture)
		return false;

	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;

	SDL_FreeSurface(loadedSurface);

	return true;
}

void Texture::free()
{
	if (mTexture)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture::render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip)
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if (clip)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

void Texture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

int Texture::getWidth()
{
	return mWidth;
}

int Texture::getHeight()
{
	return mHeight;
}
