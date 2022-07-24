#include "Button.h"
#include "Texture.h"
#include "Control.h"
#include <cmath>
#include <numbers>

Button::Button(	Widget* parent,
				SDL_Renderer* gRenderer,
				const SDL_FPoint& position,
				std::string_view pathImage,
				std::string_view pathShineImage,
				std::string_view pathPressImage,
				const std::function<void()>& initAction)
	: Widget(parent, gRenderer, position)
	, state(State::unpressed)
{
	image = std::make_shared<Texture>();
	if (image)
		image->loadFromFile(pathImage, gRenderer);

	shineImage = std::make_shared<Texture>();
	if (shineImage)
		shineImage->loadFromFile(pathShineImage, gRenderer);

	pressImage = std::make_shared<Texture>();
	if (pressImage)
		pressImage->loadFromFile(pathPressImage, gRenderer);

	action = initAction;

	rect.x = position.x;
	rect.y = position.y;
	rect.w = image->getWidth();
	rect.h = image->getHeight();
}

void Button::render(SDL_Renderer* gRenderer)
{
	if (lock)
	{
		if (pressImage)
			pressImage->render(gRenderer, position.x, position.y);
	}
	else
	{
		if (shineImage)
		{
			shineImage->render(gRenderer, position.x, position.y);
			shineImage->setAlpha(alphaSinValue);
		}

		if (image)
			image->render(gRenderer, position.x, position.y);
	}
}

void Button::setLock(bool lockButton)
{
	lock = lockButton;
	if (!lock)
	{
		alphaValue = 0.f;
		alphaSinValue = 0.f;
	}
}

bool Button::isLock() const
{
	return lock;
}

void Button::touch(int x, int y, Uint32 type)
{
	if (lock)
		return;

	SDL_Point point;
	point.x = x;
	point.y = y;
	if (!SDL_PointInRect(&point, &rect))
	{
		state = State::unpressed;
		return;
	}

	if (type == SDL_MOUSEBUTTONDOWN)
	{
		state = State::pressed;
		Control::setCapture(shared_from_this());
	}

	if (type == SDL_MOUSEBUTTONUP)
	{
		if (state == State::pressed)
		{
			state = State::unpressed;
			if (action)
				action();

			Control::removeCapture();
		}
	}
}

void Button::update(float dt)
{
	alphaValue += dt;
	if (alphaValue > M_PI)
		alphaValue = 0.f;
	alphaSinValue = std::sin(alphaValue) * 255;
}
