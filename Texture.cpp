#include "Texture.h"

Texture::Texture(SDL_Renderer * renderer, double x, double y){
	this->renderer = renderer;
	this->x = x;
	this->y = y;
}

Texture::~Texture() {

}

void Texture::Render() {

}