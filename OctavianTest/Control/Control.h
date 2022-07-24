#pragma once
#include <memory>

class Widget;

class Control
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