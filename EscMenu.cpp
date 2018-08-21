#include "EscMenu.h"

EscMenu::EscMenu(SDL_Renderer * renderer) {
//	std::cout << "mainMenu constructor" << this << std::endl;
	em.push_back(new Button(renderer, "Restart", DISPLAY_WIDTH / 2.0 - BUTTON_WIDTH / 2.0, DISPLAY_HEIGHT / 4.0 - BUTTON_HEIGHT / 2.0));
	em.push_back(new Button(renderer, "MainMenu", DISPLAY_WIDTH / 2.0 - BUTTON_WIDTH / 2.0, DISPLAY_HEIGHT / 2.0 - BUTTON_HEIGHT / 2.0));
	em.push_back(new Button(renderer, "Exit", DISPLAY_WIDTH / 2.0 - BUTTON_WIDTH / 2.0, DISPLAY_HEIGHT / 4.0 * 3 - BUTTON_HEIGHT / 2.0));
}

EscMenu::~EscMenu() {
//	std::cout << "mainMenu destructor" << this << std::endl;
}

void EscMenu::Render() {
	for (size_t i = 0; i < em.size(); ++i)
		em[i]->Render();
}

void EscMenu::Clean() {
	for (size_t i = 0; i < em.size(); ++i) {
		delete em[i];
	}
}

size_t EscMenu::Size() {
	return em.size();
}

Button * EscMenu::getButton(size_t i) {
	return em[i];
}