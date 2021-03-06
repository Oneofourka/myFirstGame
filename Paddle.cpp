#include "Paddle.h"

Paddle::Paddle(SDL_Renderer * renderer, double x, double y) : Texture(renderer, x, y) {
//	std::cout << "paddle constructor" << this << std::endl;
	SDL_Surface* surface = IMG_Load("images/paddle.png");
	paddleTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	this->height = PADDLE_HEIGHT;
	this->width = PADDLE_WIDTH;
}

Paddle::~Paddle() {
//	std::cout << "paddle destructor" << this << std::endl;
	SDL_DestroyTexture(paddleTexture);
}

void Paddle::Render() {
	SDL_Rect dstRect;

	dstRect.x = int(x);
	dstRect.y = int(y);
	dstRect.w = int(width);
	dstRect.h = int(height);

	SDL_RenderCopy(renderer, paddleTexture, 0, &dstRect);
}

void Paddle::Update() {
	getSomeCoord(width, height);
	Move();
}

void Paddle::Move() {
	const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
	if (keyboardState[SDL_SCANCODE_LEFT])
	{
		if (x <= 0)
			x = 0;
		else x -= PADDLE_SPEED;
	}
	else if (keyboardState[SDL_SCANCODE_RIGHT])
	{
		if (xEnd >= DISPLAY_WIDTH)
			x = DISPLAY_WIDTH - width;
		else x += PADDLE_SPEED;
	}
}

void Paddle::setState(paddleState state) {
	this->state = state;
}
	
paddleState Paddle::getState() {
	return state;
}