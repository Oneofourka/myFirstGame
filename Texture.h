#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

const int DISPLAY_WIDTH = 1000;
const int DISPLAY_HEIGHT = 600;
const int MENU_WIDTH = 300;
const int MENU_HEIGHT = 350;
const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 75;
const int PADDLE_WIDTH = 200;
const int PADDLE_HEIGHT = 60;
const double BALL_SPEED = 1;
const int BALL_WIDTH = 24;
const int BALL_HEIGHT = 24;
const int NUMBER_WIDTH = 1;		//number of bricks width
const int NUMBER_HEIGHT = 1;		//number of bricks height
const double BRICK_WIDTH = DISPLAY_WIDTH / NUMBER_WIDTH;	
const double BRICK_HEIGHT = DISPLAY_HEIGHT / NUMBER_HEIGHT / 2.0; 

class Texture {
public:
	Texture(SDL_Renderer * renderer, double x, double y);
	virtual ~Texture();
	void setX(double x);
	void setY(double y);
	void setWidth(int i);
	void setHeight(int i);
	double getX();
	double getY();
	int getWidth();
	int getHeight();
	double getXMiddle();
	double getYMiddle();
	double getXEnd();
	double getYEnd();
	void getSomeCoord(double width, double height);

protected:
	SDL_Renderer * renderer;
	double x, y, xMiddle, yMiddle, xEnd, yEnd;
	int width, height;
};