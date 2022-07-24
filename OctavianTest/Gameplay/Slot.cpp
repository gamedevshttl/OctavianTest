#include "Slot.h"

Slot::Slot(	Widget* parent,
			SDL_Renderer* gRenderer,
			const SDL_FPoint& position,
			std::string_view initStringText,
			float drumSpeed,
			float upBorder,
			float downBorder)
	: Widget(parent, gRenderer, position)
	, stringText(initStringText)
	, speed(drumSpeed)
{
	SDL_Color textColor = { 0, 0, 0 };
	text.loadFromRenderText(stringText, textColor, gRenderer);

	slotBorder.upBorder = upBorder;
	slotBorder.downBorder = downBorder;
}

void Slot::render(SDL_Renderer* gRenderer)
{
	text.render(gRenderer, position.x, position.y);
}

void Slot::update(float dt)
{
	position.y += speed * dt;

	if (position.y > slotBorder.downBorder)
		position.y = slotBorder.upBorder;
}

void Slot::setSpeed(float drumSpeed)
{
	speed = drumSpeed;
}
