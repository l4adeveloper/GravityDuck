#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
using namespace std;

struct Button{
	SDL_Rect rect;
	SDL_Color color;
	bool isHovered;
	bool isBlinking;
	int blinkInterval;
	Uint32 lastBlinkTime;
}