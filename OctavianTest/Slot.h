#pragma once
#include <vector>
#include "Texture.h"
#include "Text.h"
#include "Widget.h"

struct SlotBorder
{
	int upBorder;
	int downBorder;
};

class Slot : public Widget
{
public:
	Slot(	Widget* parent,
			SDL_Renderer* gRenderer,
			const SDL_FPoint& pos,
			std::string_view initStringText,
			float drumSpeed,
			float upBorder,
			float downBorde);
	void render(SDL_Renderer* gRenderer) override;
	void update(float dt);
	void setSpeed(float speed);
private:
	SlotBorder slotBorder;

	Text text;
	std::string stringText;

	float speed = 50.f;
	float x = 100.f;
	float y = 100.f;

};

