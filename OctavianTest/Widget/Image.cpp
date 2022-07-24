#include "Image.h"

Image::Image(Widget* parent, SDL_Renderer* gRenderer, const SDL_FPoint& position, std::string_view imagePath)
	: Widget(parent, gRenderer, position)
	, path(imagePath)
{
	image.loadFromFile(imagePath.data(), gRenderer);
}

void Image::render(SDL_Renderer* gRenderer)
{
	image.render(gRenderer, position.x, position.y);
}