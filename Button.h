#pragma once
#include "Texture.h"
#include "SDL_ttf.h"
#include <string>

class Button : public Texture {
public:
	Button(SDL_Renderer * renderer, std::string text, double x, double y);
	~Button() override;
	void Render();
	bool Event(SDL_Event *event);

private:
	SDL_Texture * buttonTexture;
	SDL_Texture * message;
	std::string text;
};