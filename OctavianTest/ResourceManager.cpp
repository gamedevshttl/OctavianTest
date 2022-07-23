#include "ResourceManager.h"
#include <sstream>
#include <fstream>

std::map<std::string, TTF_Font*> ResourceManager::fonts;

nlohmann::json ResourceManager::loadJson(std::string_view path)
{
	std::ifstream file(path);
	std::stringstream fileStream;
	fileStream << file.rdbuf();
	file.close();
	return nlohmann::json::parse(fileStream.str());
}

void ResourceManager::loadfont(std::string_view name, std::string_view path, int size)
{
	fonts[name.data()] = TTF_OpenFont(path.data(), size);
}

TTF_Font* ResourceManager::getFont(std::string_view name)
{
	return fonts[name.data()];
}

void ResourceManager::closeFont()
{
	for(auto& font: fonts)
		TTF_CloseFont(font.second);
}