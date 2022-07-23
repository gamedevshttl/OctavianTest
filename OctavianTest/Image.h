#pragma once

#include "Widget.h"
#include "Texture.h"
#include <string_view>

class Image: public Widget
{
public:
	Image(Widget* parent, SDL_Renderer* gRenderer, const SDL_FPoint& pos, std::string_view path);

	void render(SDL_Renderer* gRenderer) override;
private:
	std::string path;
	Texture image;
};

