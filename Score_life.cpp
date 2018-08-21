#include "Score_life.h"

Score_Life::Score_Life(SDL_Renderer * renderer, std::string text, double x, double y) : Texture(renderer, x, y) {
//	std::cout << "score_life constructor" << this << std::endl;
	this->text = text;
	this->width = SCORE_LIFE_WIDTH;
	this->height = SCORE_LIFE_HEIGHT;
	s = text;
	font = TTF_OpenFont("ttf.ttf", 24);
	color = { 255, 0, 0 };
	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	message = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

Score_Life::~Score_Life() {
//	std::cout << "score_life destructor" << this << std::endl;
}

void Score_Life::Render() {
	SDL_Rect dstRect;

	dstRect.x = int(x);
	dstRect.y = int(y);
	dstRect.w = int(width * s.size());
	dstRect.h = int(height);

	SDL_RenderCopy(renderer, message, 0, &dstRect);
}

void Score_Life::Update(int number) {
	font = TTF_OpenFont("ttf.ttf", 24);
	color = { 255, 0, 0 };
	this->number = number;
	s = text + std::to_string(number);
	surface = TTF_RenderText_Solid(font, s.c_str(), color);
	message = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}