#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer * renderer) {
//	std::cout << "mainMenu constructor" << this << std::endl;
	mm.push_back(new Button(renderer, "New game", DISPLAY_WIDTH / 2.0 - BUTTON_WIDTH / 2.0, DISPLAY_HEIGHT / 4.0 - BUTTON_HEIGHT / 2.0));
	mm.push_back(new Button(renderer, "High score", DISPLAY_WIDTH / 2.0 - BUTTON_WIDTH / 2.0, DISPLAY_HEIGHT / 2.0 - BUTTON_HEIGHT / 2.0));
	mm.push_back(new Button(renderer, "Exit", DISPLAY_WIDTH / 2.0 - BUTTON_WIDTH / 2.0, DISPLAY_HEIGHT / 4.0 * 3 - BUTTON_HEIGHT / 2.0));
}

MainMenu::~MainMenu() {
//	std::cout << "mainMenu destructor" << this << std::endl;
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

size_t MainMenu::Size(){
	return mm.size();
}

Button * MainMenu::getButton(size_t i) {
	return mm[i];
}