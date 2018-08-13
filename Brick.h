#pragma once
#include "Texture.h"

class Brick : public Texture {
public:
	Brick(SDL_Renderer * renderer);
	~Brick() override;
	void Render();

private:
	SDL_Texture * brickTexture;
};