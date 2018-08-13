#include "Ball.h"

Ball::Ball(SDL_Renderer * renderer, double x, double y) : Texture(renderer, x, y) {
	SDL_Surface* surface = IMG_Load("images/ball.png");
	ballTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	this->renderer = renderer;
	this->x = x;
	this->y = y;
	this->height = BALL_HEIGHT;
	this->width = BALL_WIDTH;
	dirX = 1;
	dirY = -1;
//	std::cout << "ball constructor" << this << std::endl;
}

Ball::~Ball() {
	SDL_DestroyTexture(ballTexture);
//	std::cout << "ball destructor" << this << std::endl;
}

void Ball::Update() {
	x += dirX;
	y += dirY;
}

void Ball::Render() {
	SDL_Rect dstRect;

	dstRect.x = int(x);
	dstRect.y = int(y);
	dstRect.w = int(BALL_WIDTH);
	dstRect.h = int(BALL_HEIGHT);

	SDL_RenderCopy(renderer, ballTexture, 0, &dstRect);
}

void Ball::setDirX(double dirX) {
	this->dirX = dirX;
}

void Ball::setDirY(double dirY) {
	this->dirY = dirY;
}

double Ball::getDirX() {
	return dirX;
}

double Ball::getDirY() {
	return dirY;
}