#include "Label.h"

Label::Label(Widget* parent, SDL_Renderer* gRenderer, const SDL_FPoint& position, std::string_view initStringText)
	: Widget(parent, gRenderer, position)
	, stringText(initStringText)
	, renderer(gRenderer)
{
	text.loadFromRenderText(stringText, textColor, gRenderer);
}

void Label::render(SDL_Renderer* gRenderer)
{
	text.render(gRenderer, position.x, position.y);
}

void Label::setText(std::string_view newText)
{
	if (!renderer)
		return;

	text.loadFromRenderText(newText, textColor, renderer);
}