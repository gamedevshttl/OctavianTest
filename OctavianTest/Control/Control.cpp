#include "Control.h"

std::shared_ptr<Widget> Control::capture = nullptr;
std::shared_ptr<Widget> Control::active = nullptr;

void Control::setCapture(std::shared_ptr<Widget> captureWidget)
{
	capture = captureWidget;
}

void Control::removeCapture()
{
	capture = nullptr;
}

std::shared_ptr<Widget> Control::getCapture()
{
	return capture;
}

void Control::setActive(std::shared_ptr<Widget> activeWidget)
{
	active = activeWidget;
}

void Control::resetActive()
{
	active = nullptr;
}

std::shared_ptr<Widget> Control::getActive()
{
	return active;
}
