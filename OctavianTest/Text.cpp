#include "Text.h"
#include "ResourceManager.h"

Text::Text()
{
	//font = TTF_OpenFont("../resources/font/lazy.ttf", 28);
	font = ResourceManager::getFont("lazy");
}

Text::~Text()
{
	free();
	//TTF_CloseFont(font);
}

SDL_Texture* Text::loadFromRenderText(std::string_view text, SDL_Color color, SDL_Renderer* gRenderer)
{
	//TTF_Font* font = TTF_OpenFont("../resources/font/lazy.ttf", 28);

	if (!font)
	{
		//printf("Failed to load font! %s", TTF_GetError());
		return nullptr;
	}

	free();
	SDL_Surface* textureSurface = TTF_RenderText_Solid(font, text.data(), color);
	if (!textureSurface)
	{
		//TTF_CloseFont(font);
		return nullptr;
	}

	mTexture = SDL_CreateTextureFromSurface(gRenderer, textureSurface);
	if (!mTexture)
		return nullptr;

	mWidth = textureSurface->w;
	mHeight = textureSurface->h;

	SDL_FreeSurface(textureSurface);
	//TTF_CloseFont(font);
	return mTexture;
}

void Text::free()
{
	if (mTexture)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

void Text::render(SDL_Renderer* gRenderer, float x, float y, double angle, SDL_Rect* clip, SDL_FPoint* center, SDL_RendererFlip flip)
{
	SDL_FRect renderQuad = { x, y, mWidth , mHeight };

	if (clip)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);

	SDL_RenderCopyExF(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}
