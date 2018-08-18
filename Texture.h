#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "GameConst.h"

class Texture {
public:
	Texture(SDL_Renderer * renderer, double x, double y);
	Texture() {};
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