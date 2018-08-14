#pragma once
#include <vector>
#include "Button.h"

class MainMenu {
public:
	MainMenu(SDL_Renderer * renderer);
	~MainMenu();
	void Render();
	void Clean();
	size_t Size();
	Button * getButton(size_t i);
private:
	SDL_Renderer * renderer;
	std::vector<Button*> mm;
};