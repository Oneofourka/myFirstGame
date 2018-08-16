#pragma once
#include "Texture.h"

enum paddleState {
	LEFT_ANGLE,
	RIGHT_ANGLE,
	NOT_ANGLE
};
class Paddle : public Texture {
public:
	Paddle(SDL_Renderer * renderer, double x, double y);
	~Paddle() override;
	void Render();
	void Update();
	void Move();
	void setState(paddleState state);
	paddleState getState();

private:
	SDL_Texture * paddleTexture;
	bool right, left;
	paddleState state;
};