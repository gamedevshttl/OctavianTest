#include "Application.h"
#include <SDL.h>
#include <iostream>
#include <chrono>
#include "GamblingMachine.h"
#include "ResourceManager.h"

bool Application::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	else
	{
		int windowWidth = 850;
		int windowHeight = 768;

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;;
			return false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (!gRenderer)
			{
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
				return false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);

				//Initialize PNG loading
				int imgFlag = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlag) & imgFlag))
				{
					std::cout<<"SDL_image could not initialize. SDL_image error " << IMG_GetError() <<std::endl;
					return false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
					return false;
				}
			}
		}
	}

	ResourceManager::loadfont("lazy", "../resources/font/lazy.ttf", 28);

	gamblingMachine = std::make_shared<GamblingMachine>(nullptr, gRenderer, SDL_FPoint());
	System::setActive(gamblingMachine);
	return true;
}

void Application::run()
{
	bool quit = false;
	SDL_Event event;

	auto starTime = std::chrono::system_clock::now();
	auto endTime = std::chrono::system_clock::now();

	while (!quit)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
			{
				int touchX, touchY;
				SDL_GetMouseState(&touchX, &touchY);

				if (System::getCapture())
				{
					System::getCapture()->touch(touchX, touchY, event.type);
				}
				else
				{
					if (gamblingMachine)
						gamblingMachine->touch(touchX, touchY, event.type);
				}

				if (event.type == SDL_MOUSEBUTTONUP)
					System::removeCapture();
			}
		}

		{
			endTime = std::chrono::system_clock::now();
			std::chrono::duration<double> deltaTime = endTime - starTime;
			double dt = deltaTime.count();

			if (gamblingMachine)
				gamblingMachine->update(dt);
			starTime = endTime;
		}

		{
			SDL_RenderClear(gRenderer);
			if (gamblingMachine)
				gamblingMachine->render(gRenderer);
			SDL_RenderPresent(gRenderer);
		}
	}

	stop();
}

void Application::stop()
{
	ResourceManager::closeFont();

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;
	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
}