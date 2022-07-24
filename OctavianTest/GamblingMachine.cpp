#include "GamblingMachine.h"
#include "Slot.h"
#include "SlotDrum.h"
#include "Drum.h"
#include "Button.h"
#include "Widget.h"
#include "Image.h"
#include "Label.h"
#include "ResourceManager.h"

GamblingMachine::GamblingMachine(Widget* parent, SDL_Renderer* gRenderer, const SDL_FPoint& position)
	: Widget(parent, gRenderer, position)
{
	gamblingMachineJson = ResourceManager::loadJson("../resources/json/gamblinng_machine.json");

	add<Image>(gRenderer, SDL_FPoint(), gamblingMachineJson["bg_image"].get<std::string>());

	SDL_FPoint labelFrameRatePoint;
	labelFrameRatePoint.x = gamblingMachineJson["frame_rate_position"]["x"].get<float>();
	labelFrameRatePoint.y = gamblingMachineJson["frame_rate_position"]["y"].get<float>();
	frameRate = add<Label>(gRenderer, labelFrameRatePoint, "");
	startTick = SDL_GetTicks();

	SDL_FPoint buttonPoint;
	buttonPoint.x = gamblingMachineJson["play_button"]["position"]["x"].get<float>();
	buttonPoint.y = gamblingMachineJson["play_button"]["position"]["y"].get<float>();

	startButton = add<Button>(gRenderer,
		buttonPoint,
		gamblingMachineJson["play_button"]["image"].get<std::string>(),
		gamblingMachineJson["play_button"]["shine_image"].get<std::string>(),
		gamblingMachineJson["play_button"]["press_image"].get<std::string>(),
		[this]() {
			startDrum();
		});

	drum = add<Drum>(gRenderer, SDL_FPoint());
}

void GamblingMachine::startDrum()
{
	if (drum)
		drum->startDrum([this]() {
			startButton->setLock(false);
		});
	startButton->setLock(true);
}

void GamblingMachine::update(float dt)
{
	Widget::update(dt);
	calcFameRate();
}

void GamblingMachine::calcFameRate()
{
	Uint32 time = SDL_GetTicks() - startTick;
	++counterFrame;
	avgFPS = counterFrame / (time / 1000.f);
	if (frameRate)
		frameRate->setText("fps:" + std::to_string(static_cast<int>(avgFPS)));
}