#pragma once
#include "Texture.h"

class Brick : public Texture {
public:
	Brick() {};
	Brick(SDL_Renderer * renderer, double x, double y);
	~Brick() override;
	void Render();
	void setState(bool state);
	bool getState();

private:
	SDL_Texture * brickTexture;
	bool state;
};