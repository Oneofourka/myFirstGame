#pragma once
#include "Texture.h"

class Paddle : public Texture {
public:
	Paddle(SDL_Renderer * renderer, double x, double y);
	~Paddle() override;
	void Render();
	void Update();
	void Move();

private:
	SDL_Texture * paddleTexture;
	bool right, left;
};