#pragma once
#include "Widget.h"
#include <nlohmann/json.hpp>

class SlotDrum;

class Drum : public Widget
{
public:
	Drum(Widget* parent, SDL_Renderer* gRenderer, const SDL_FPoint& pos);
	void render(SDL_Renderer* gRenderer) override;

	void start(const std::function<void()> stopDrumCallBack);
private:
	static Uint32 stopDrumCallBack(Uint32 interval, void* param);
	void stop();
	void stopDrumSlot();
	int stopDrumId = 0;

	nlohmann::json drumJson;
	std::vector<std::shared_ptr<SlotDrum>> slotDrumVector;
	SDL_TimerID timerId;
	std::function<void()> stopCallBack;

	SDL_Rect clipRect;
	SDL_Rect displayRect;
};

