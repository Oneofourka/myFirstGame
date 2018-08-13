#include "Texture.h"

Texture::Texture(SDL_Renderer * renderer, double x, double y){
	this->renderer = renderer;
	this->x = x;
	this->y = y;
//	std::cout << "texture constructor" << this << std::endl;
}

Texture::Texture(SDL_Renderer * renderer) {
	this->renderer = renderer;
}

Texture::~Texture() {
//	std::cout << "texture destructor" << this << std::endl;
}

void Texture::Render() {

}

void Texture::setX(double x) {
	this->x = x;
}

void Texture::setY(double y) {
	this->y = y;
}

double Texture::getX() {
	return x;
}

double Texture::getY() {
	return y;
}

void Texture::setWidth(int width) {
	this->width = width;
}

void Texture::setHeight(int height) {
	this->height = height;
}

int Texture::getWidth() {
	return width;
}

int Texture::getHeight() {
	return height;
}