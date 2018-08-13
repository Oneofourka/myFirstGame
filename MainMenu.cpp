#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer * renderer) {
	mm.push_back(new Button(renderer, "New game", 50, 50));
	mm.push_back(new Button(renderer, "High score", 50, 150));
	mm.push_back(new Button(renderer, "Exit", 50, 250));
//	std::cout << "mainmenu constructor" << this << std::endl;
}

MainMenu::~MainMenu() {
//	std::cout << "mainmenu destructor" << this << std::endl;
}

void MainMenu::Render() {
	for (size_t i = 0; i < mm.size(); i++)
		mm[i]->Render();
}

void MainMenu::Clean() {
	for (size_t i = 0; i < mm.size(); i++) {
		delete mm[i];
	}
}
