#pragma once
#include "Texture.h"

class Ball : public Texture {
public:
	Ball(SDL_Renderer *renderer, double x, double y);
	~Ball() override;
	void Render() override;
	void Update();
	void setDirX(double dirX);
	void setDirY(double dirY);
	double getDirX();
	double getDirY();

private:
	SDL_Texture * ballTexture;
	double dirX, dirY;
};