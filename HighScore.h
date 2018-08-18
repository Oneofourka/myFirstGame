#pragma once
#include "SDL_ttf.h"
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include "Texture.h"
#include "Button.h"

class HighScore : public Texture {
public:
	HighScore(SDL_Renderer * renderer, double x, double y);
	~HighScore();
	void Render();
	void Push_back(int score);
	void Clean();
	Button * getButton();
	
private:
	SDL_Texture * message;
	std::vector<int> highScore;
	std::string namefile, str;
	Button * back;
};