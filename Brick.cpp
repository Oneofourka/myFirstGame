#include "Brick.h"

Brick::Brick(SDL_Renderer * renderer) : Texture(renderer) {
	SDL_Surface* surface = IMG_Load("images/brick.png");
	brickTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

Brick::~Brick() {
	SDL_DestroyTexture(brickTexture);
}

void Brick::Render() {
	SDL_Rect dstRect;

	dstRect.x = int(x);
	dstRect.y = int(y);
	dstRect.w = int(BRICK_WIDTH);
	dstRect.h = int(BRICK_HEIGHT);

	SDL_RenderCopy(renderer, brickTexture, 0, &dstRect);
}