#pragma once
#include <vector>
#include <memory>
#include <SDL.h>
#include <functional>
#include <nlohmann/json.hpp>
#include "Widget.h"

class Slot;

class SlotDrum : public Widget
{
public:
	SlotDrum(Widget* parent,
		SDL_Renderer* gRenderer,
		const SDL_FPoint& pos,
		float drumSpeed,
		SDL_Rect drumRect,
		const std::vector<std::string>& lavelVector);

	void update(float dt) override;
	void start();
	void startStop(const std::function<void()>& stopDrumCallBack);
private:

	static Uint32 stopDelayCallBack(Uint32 interval, void* param);
	void startStopProcess();
	void stop();

	float speed;
	SDL_Rect rect;
	std::vector<std::shared_ptr<Slot>> slotVector;
	SDL_TimerID timerId;
	std::shared_ptr<Slot> nearUpSlot = nullptr;
	int controlLevel;
	std::function<void()> stopCallBack;
	nlohmann::json slotDrumJson;
	int delayStop;
};

