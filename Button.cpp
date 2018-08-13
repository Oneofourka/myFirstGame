#include "Button.h"
#include <sstream>

Button::Button(SDL_Renderer * renderer, std::string text, double x, double y) : Texture(renderer, x, y) {
	SDL_Surface* surface = IMG_Load("images/button.png");
	buttonTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	this->renderer = renderer;
	this->text = text;
	this->x = x;
	this->y = y;

	TTF_Font * font = TTF_OpenFont("ttf.ttf", 24);
	SDL_Color color = { 0, 0, 0 };
	std::stringstream s;
	s << text;
	surface = TTF_RenderText_Solid(font, s.str().c_str(), color);
	message = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

Button::~Button() {
	SDL_DestroyTexture(buttonTexture);
}

void Button::Render() {
	SDL_Rect dstRect;

	dstRect.x = int(x);
	dstRect.y = int(y);
	dstRect.w = int(BUTTON_WIDHT);
	dstRect.h = int(BUTTON_HEIGHT);

	SDL_RenderCopy(renderer, buttonTexture, 0, &dstRect);
	
	dstRect.x = int((BUTTON_WIDHT - text.size() * BUTTON_WIDHT / 10) / 2.0 + x);
	dstRect.w = int(text.size() * BUTTON_WIDHT / 10);
	SDL_RenderCopy(renderer, message, 0, &dstRect);
}

bool Button::Event(SDL_Event *event) {
	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		if (event->button.button == SDL_BUTTON_LEFT && event->button.x > x && event->button.x < x + width && event->button.y > y && event->button.y < y + height)
			return true;
	}
}