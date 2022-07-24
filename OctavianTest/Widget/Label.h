#pragma once

#include "Widget.h"
#include "Text.h"
#include <string_view>


class Label : public Widget
{
public:
	Label(Widget* parent, SDL_Renderer* gRenderer, const SDL_FPoint& pos, std::string_view initStringText);
	void render(SDL_Renderer* gRenderer) override;
	void setText(std::string_view newText);
private:
	Text text;
	std::string stringText;
	SDL_Renderer* renderer;
	SDL_Color textColor = { 0, 0, 0 };
};

