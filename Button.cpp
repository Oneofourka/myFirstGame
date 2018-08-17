#include "Button.h"

Button::Button(SDL_Renderer * renderer, std::string text, double x, double y) : Texture(renderer, x, y) {
//	std::cout << "button constructor" << this << std::endl;
	SDL_Surface* surface = IMG_Load("images/button.png");
	buttonTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	this->text = text;
	this->width = BUTTON_WIDTH;
	this->height = BUTTON_HEIGHT;

	TTF_Font * font = TTF_OpenFont("ttf.ttf", 24);
	SDL_Color color = { 0, 0, 0 };
	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	message = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

Button::~Button() {
//	std::cout << "button destructor" << this << std::endl;
	SDL_DestroyTexture(buttonTexture);
}

void Button::Render() {
	SDL_Rect dstRect;

	dstRect.x = int(x);
	dstRect.y = int(y);
	dstRect.w = int(width);
	dstRect.h = int(height);

	SDL_RenderCopy(renderer, buttonTexture, 0, &dstRect);
	
	dstRect.x = int((width - text.size() * width / 10) / 2.0 + x);
	dstRect.w = int(text.size() * width / 10);
	SDL_RenderCopy(renderer, message, 0, &dstRect);
}

bool Button::Event(SDL_Event *event) {
	bool success = false;
	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		if (event->button.button == SDL_BUTTON_LEFT && event->button.x > x && event->button.x < x + width && event->button.y > y && event->button.y < y + height)
			success = true;
		else success = false;
	}
	else success = false;
	return success;
}