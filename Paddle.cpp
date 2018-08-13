#include "Paddle.h"

Paddle::Paddle(SDL_Renderer * renderer, double x, double y) : Texture(renderer, x, y) {
	SDL_Surface* surface = IMG_Load("images/paddle.png");
	paddleTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	this->renderer = renderer;
	this->x = x;
	this->y = y;
	this->height = PADDLE_HEIGHT;
	this->width = PADDLE_WIDTH;
//	std::cout << "paddle constructor" << this << std::endl;
}

Paddle::~Paddle() {
	SDL_DestroyTexture(paddleTexture);
//	std::cout << "paddle destructor" << this << std::endl;
}

void Paddle::Render() {
	SDL_Rect dstRect;

	dstRect.x = int(x);
	dstRect.y = int(y);
	dstRect.w = int(PADDLE_WIDTH);
	dstRect.h = int(PADDLE_HEIGHT);

	SDL_RenderCopy(renderer, paddleTexture, 0, &dstRect);
}

void Paddle::Move() {
	const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
	if (keyboardState[SDL_SCANCODE_LEFT])
	{
		if (x <= 0)
			x = 0;
		else x -= 5;
	}
	else if (keyboardState[SDL_SCANCODE_RIGHT])
	{
		if (xEnd >= DISPLAY_WIDTH)
			x = DISPLAY_WIDTH - PADDLE_WIDTH;
		else x += 5;
	}
}