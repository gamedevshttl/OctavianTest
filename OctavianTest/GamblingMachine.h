#pragma once

#include "Texture.h"
#include "Text.h"
#include "Widget.h"
#include <memory>
#include <functional>
#include <nlohmann/json.hpp>

class SlotDrum;
class Label;
class Drum;
class Button;

class GamblingMachine: public Widget
{
public:
	GamblingMachine(Widget* parent, SDL_Renderer* gRenderer, const SDL_FPoint& pos);
	void startDrum();
	void update(float dt) override;
private:
	void calcFameRate();
	nlohmann::json gamblingMachineJson;
	float avgFPS = 0;
	Uint32 startTick = 0;
	Uint32 counterFrame = 0;
	std::shared_ptr<Label> frameRate;
	std::shared_ptr<Drum> drum;
	std::shared_ptr<Button> startButton;
};

