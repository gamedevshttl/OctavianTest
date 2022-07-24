#include "SlotDrum.h"
#include "Slot.h"
#include "ResourceManager.h"
#include <SDL_timer.h>
#include <iostream>

SlotDrum::SlotDrum(	Widget* parent,
					SDL_Renderer* gRenderer,
					const SDL_FPoint& pos,
					float drumSpeed,
					SDL_Rect drumRect,
					const std::vector<std::string>& lavelVector)
	: Widget(parent, gRenderer, pos)
	, speed(drumSpeed)
	, rect(drumRect)
{
	slotDrumJson = ResourceManager::loadJson("../resources/json/slot_drum.json");

	position.x += rect.x;
	int upBorder = rect.y + position.y;
	int downBorder = rect.h + position.y;

	SDL_FPoint slotOffset;
	slotOffset.x = slotDrumJson["slot_offset"]["x"].get<int>();
	slotOffset.y = slotDrumJson["slot_offset"]["y"].get<int>();
	float offsetY = upBorder;
	for (int i = 0; i < slotDrumJson["slot_quantity"].get<int>(); ++i)
	{
		SDL_FPoint slotPoint;
		slotPoint.x = position.x;
		slotPoint.y = offsetY;

		std::string label = lavelVector[i % lavelVector.size()];
		slotVector.emplace_back(add<Slot>(gRenderer, slotPoint, label, 0.f, upBorder, downBorder));

		offsetY += slotOffset.y;
	}
	controlLevel = slotVector[slotDrumJson["control_level"].get<int>()]->getPosition().y;
	delayStop = slotDrumJson["delay_stop"].get<int>();
}

void SlotDrum::update(float dt)
{
	for (auto& slot : slotVector)
		slot->update(dt);

	if (nearUpSlot)
	{
		if (std::abs(nearUpSlot->getPosition().y - controlLevel) < 0.1f)
		{
			stop();
			if (stopCallBack)
				stopCallBack();
			stopCallBack = nullptr;
		}
	}
}

void SlotDrum::start()
{
	for (auto& slot : slotVector)
		slot->setSpeed(speed);
}

void SlotDrum::launchStop(const std::function<void()>& stopDrumCallBack)
{
	stopCallBack = stopDrumCallBack;
	timerId = SDL_AddTimer(delayStop, &SlotDrum::stopDelayCallBack, this);
}

Uint32 SlotDrum::stopDelayCallBack(Uint32 interval, void* param)
{
	((SlotDrum*)param)->stopProcess();
	return interval;
}

void SlotDrum::stopProcess()
{
	int distance = std::numeric_limits<int>::max();
	for (auto& slot : slotVector)
	{
		if (slot->getPosition().y < controlLevel)
		{
			if (distance > controlLevel - slot->getPosition().y)
			{
				distance = controlLevel - slot->getPosition().y;
				nearUpSlot = slot;
			}
		}
	}
	SDL_RemoveTimer(timerId);
}

void SlotDrum::stop()
{
	for (auto& slot : slotVector)
		slot->setSpeed(0.f);
	nearUpSlot = nullptr;
}
