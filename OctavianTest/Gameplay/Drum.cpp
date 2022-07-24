#include "Drum.h"
#include "ResourceManager.h"
#include "Slot.h"
#include "SlotDrum.h"

Drum::Drum(Widget* parent, SDL_Renderer* gRenderer, const SDL_FPoint& pos)
	: Widget(parent, gRenderer, position)
{
	drumJson = ResourceManager::loadJson("../resources/json/drum.json");

	SDL_FPoint slotPoint;
	slotPoint.x = drumJson["position"]["x"].get<float>();
	slotPoint.y = drumJson["position"]["y"].get<float>();
	float speed = drumJson["start_speed"].get<float>();
	SDL_Rect drumRect;
	drumRect.x = drumJson["rect"]["x"].get<float>();
	drumRect.y = drumJson["rect"]["y"].get<float>();
	drumRect.w = drumJson["rect"]["w"].get<float>();
	drumRect.h = drumJson["rect"]["h"].get<float>();
	SDL_FPoint drumOffset;
	drumOffset.x = drumJson["offset"]["x"].get<float>();
	drumOffset.y = drumJson["offset"]["y"].get<float>();
	int speedOffest = drumJson["speed_offset"].get<float>();

	std::vector<std::vector<std::string>> slotLabelStr;
	auto& slotLabel = drumJson["slot_label"];
	for (auto itSlot = slotLabel.begin(); itSlot != slotLabel.end(); ++itSlot)
	{
		std::vector<std::string> labelVector;
		for (auto itLabel = itSlot->begin(); itLabel != itSlot->end(); ++itLabel)
			labelVector.emplace_back(itLabel->get<std::string>());
		slotLabelStr.emplace_back(labelVector);
	}

	for (int i = 0; i < drumJson["quantity_slot"].get<int>(); ++i)
	{
		int labelVectorId = i % slotLabelStr.size();
		slotDrumVector.emplace_back(add<SlotDrum>(gRenderer, slotPoint, speed, drumRect, slotLabelStr[labelVectorId]));
		slotPoint.x += drumOffset.x;
		slotPoint.y += drumOffset.y;
		speed += speedOffest;
	}

	clipRect.x = drumJson["visible_rect"]["x"].get<int>();
	clipRect.y = drumJson["visible_rect"]["y"].get<int>();
	clipRect.w = drumJson["visible_rect"]["w"].get<int>();
	clipRect.h = drumJson["visible_rect"]["h"].get<int>();
}

void Drum::render(SDL_Renderer* gRenderer)
{
	SDL_RenderSetClipRect(gRenderer, &clipRect);
	Widget::render(gRenderer);
	SDL_RenderSetClipRect(gRenderer, nullptr);
}

void Drum::startDrum(const std::function<void()> stopDrumCallBack)
{
	stopCallBack = stopDrumCallBack;
	for (auto& slotDrum : slotDrumVector)
		slotDrum->start();

	timerId = SDL_AddTimer(drumJson["timer"].get<int>(), &Drum::stopDrumCallBack, this);
}

Uint32 Drum::stopDrumCallBack(Uint32 interval, void* param)
{
	((Drum*)param)->startStop();
	return interval;
}

void Drum::startStop()
{
	SDL_RemoveTimer(timerId);
	stopDrumSlot();
}

void Drum::stopDrumSlot()
{
	if (stopDrumId < slotDrumVector.size())
	{
		slotDrumVector[stopDrumId]->startStop([this]() {
				++stopDrumId;
				stopDrumSlot();
			});
	}
	else
	{
		stopDrumId = 0;
		if (stopCallBack)
			stopCallBack();
	}
}