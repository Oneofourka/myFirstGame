#include "Ball.h"

Ball::Ball(SDL_Renderer * renderer, double x, double y, double plusSpeed) : Texture(renderer, x, y) {
//	std::cout << "ball constructor" << this << std::endl;
	SDL_Surface* surface = IMG_Load("images/ball.png");
	ballTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	this->plusSpeed = plusSpeed;
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
	this->dirX = BALL_SPEED * (1.0 + 0.2 * plusSpeed) * (dirX / length);
	this->dirY = BALL_SPEED * (1.0 + 0.2 * plusSpeed) * (dirY / length);
}