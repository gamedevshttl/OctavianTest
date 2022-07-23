#pragma once
#include <memory>
#include <vector>
#include <SDL.h>


enum class State
{
	none,
	pressed
};

class Widget: public std::enable_shared_from_this<Widget>
{
public:
	Widget(Widget* parentwidget, SDL_Renderer* gRenderer, const SDL_FPoint& pos);
	~Widget() {};

	template <typename Type, typename... Args>
	std::shared_ptr<Type> add(Args... args)
	{
		auto control = std::make_shared<Type>(this, std::forward<Args>(args)...);
		child.emplace_back(control);
		return control;
	}

	virtual void render(SDL_Renderer*);
	virtual void touch(int x, int y, Uint32 type);
	virtual void update(float dt);
	virtual void setLock(bool lock);
	virtual bool isLock() const;

	SDL_FPoint getPosition();
protected:
	Widget* parent;
	SDL_FPoint position;
	std::vector<std::shared_ptr<Widget>> child;
};

class System
{
public:
	static void setCapture(std::shared_ptr<Widget> captureWidget);
	static void removeCapture();
	static std::shared_ptr<Widget> getCapture();

	static void setActive(std::shared_ptr<Widget> activeWidget);
	static void resetActive();
	static std::shared_ptr<Widget> getActive();

private:
	static std::shared_ptr<Widget> capture;
	static std::shared_ptr<Widget> active;
};