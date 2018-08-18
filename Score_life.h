#pragma once
#include "Texture.h"
#include "SDL_ttf.h"
#include <string>

class Score_Life : public Texture {
public:
	Score_Life(SDL_Renderer * renderer, std::string text, double x, double y);
	~Score_Life() override;
	void Render();
	void Update(int text);

private:
	SDL_Texture * message; 
	int number;
	std::string text, s;
};