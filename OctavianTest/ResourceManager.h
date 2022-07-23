#pragma once

#include <nlohmann/json.hpp>
#include <string_view>
#include <SDL_ttf.h>

class ResourceManager
{
public:
	static nlohmann::json loadJson(std::string_view path);
	static void loadfont(std::string_view name, std::string_view path, int size);
	static TTF_Font* getFont(std::string_view name);
	static void closeFont();
	static std::map<std::string, TTF_Font* > fonts;
};

