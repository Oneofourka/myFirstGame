#pragma once
#include <vector>
#include "Button.h"

class EscMenu {
public:
	EscMenu(SDL_Renderer * renderer);
	~EscMenu();
	void Render();
	void Clean();
	size_t Size();
	Button * getButton(size_t i);
private:
	SDL_Renderer * renderer;
	std::vector<Button*> em;
};