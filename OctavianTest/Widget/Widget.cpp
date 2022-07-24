#include "Widget.h"

Widget::Widget(Widget* parentwidget, SDL_Renderer* gRenderer, const SDL_FPoint & pos)
	: parent(parentwidget)
	, position(pos)
{
}

void Widget::render(SDL_Renderer* gRenderer)
{
	for (auto&& item : child)
		item->render(gRenderer);
}

void Widget::touch(int x, int y, Uint32 type)
{
	for (auto&& item : child)
		item->touch(x, y, type);
}

void Widget::update(float dt)
{
	for (auto&& item : child)
		item->update(dt);
}

void Widget::setLock(bool lock)
{}

bool Widget::isLock() const
{
	return false;
}

SDL_FPoint Widget::getPosition()
{
	return position;
}
