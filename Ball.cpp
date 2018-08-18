#include "Ball.h"

Ball::Ball(SDL_Renderer * renderer, double x, double y) : Texture(renderer, x, y) {
//	std::cout << "ball constructor" << this << std::endl;
	SDL_Surface* surface = IMG_Load("images/ball.png");
	ballTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	width = BALL_WIDTH;
	height = BALL_HEIGHT;
	setDirection(1, -1);
}

Ball::~Ball() {
//	std::cout << "ball destructor" << this << std::endl;
	SDL_DestroyTexture(ballTexture);
}

void Ball::Render() {
	SDL_Rect dstRect;

	dstRect.x = int(x);
	dstRect.y = int(y);
	dstRect.w = int(width);
	dstRect.h = int(height);

	SDL_RenderCopy(renderer, ballTexture, 0, &dstRect);
}

void Ball::Update() {
	getSomeCoord(width, height);
	x += dirX;
	y += dirY;
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

void Ball::setDirection(double dirX, double dirY) {
	double length = sqrt(dirX * dirX + dirY * dirY);
	this->dirX = BALL_SPEED * (dirX / length);
	this->dirY = BALL_SPEED * (dirY / length);
}