#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer * renderer) {
	this->mm.push_back(new Button(renderer, "New game", 50, 50));
	this->mm.push_back(new Button(renderer, "High score", 50, 150));
	this->mm.push_back(new Button(renderer, "Exit", 50, 250));
}

MainMenu::~MainMenu() {

}

void MainMenu::Render() {
	for (size_t i = 0; i < mm.size(); i++)
		mm[i]->Render();
}

void MainMenu::Clean() {
	mm.clear();
}
