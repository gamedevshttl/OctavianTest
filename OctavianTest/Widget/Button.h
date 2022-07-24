#pragma once

#include "Widget.h"
#include <memory>
#include <string_view>
#include <functional>

enum class State
{
	unpressed,
	pressed
};

class Texture;
class Button : public Widget
{
public:
	Button(	Widget* parent,
			SDL_Renderer* gRenderer,
			const SDL_FPoint& pos,
			std::string_view pathImage,
			std::string_view pathShineImage,
			std::string_view pathPressImage,
			const std::function<void()>& initAction
	);

	void render(SDL_Renderer* gRenderer) override;
	void touch(int x, int y, Uint32 type) override;
	void update(float dt) override;
	void setLock(bool lockButton) override;
	bool isLock() const override;

private:
	std::shared_ptr<Texture> image;
	std::shared_ptr<Texture> shineImage;
	std::shared_ptr<Texture> pressImage;

	SDL_Rect rect;
	State state;

	std::function<void()> action;

	float alphaValue = 0.f;
	float alphaSinValue = 0.f;
	bool lock = false;
};

