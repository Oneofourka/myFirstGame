#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

const int DISPLAY_WIDTH = 1000;
const int DISPLAY_HEIGHT = 600;
const int MENU_WIDTH = 300;
const int MENU_HEIGHT = 350;
const int BUTTON_WIDHT = 200;
const int BUTTON_HEIGHT = 50;
const int PADDLE_WIDTH = 200;
const int PADDLE_HEIGHT = 60;
const int BALL_WIDTH = 24;
const int BALL_HEIGHT = 24;
const int NUMBER_WIDTH = 15;		//number of bricks width
const int NUMBER_HEIGHT = 15;		//number of bricks height
const double BRICK_WIDTH = DISPLAY_WIDTH / NUMBER_WIDTH;	
const double BRICK_HEIGHT = DISPLAY_HEIGHT / NUMBER_HEIGHT / 2.0; 

class Texture {
public:
	Texture(SDL_Renderer * renderer, double x, double y);
	Texture(SDL_Renderer * renderer);
	virtual ~Texture();
	virtual void Render();
	void setX(double x);
	void setY(double y);
	double getX();
	double getY();
	void setWidth(int i);
	void setHeight(int i);
	int getWidth();
	int getHeight();

protected:
	SDL_Renderer * renderer;
	double x, y, xMiddle = x + width / 2.0, yMiddle = y + height / 2.0, xEnd = x + width, yEnd = y + height;
	int width, height;
};