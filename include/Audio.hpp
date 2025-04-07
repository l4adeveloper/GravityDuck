#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
using namespace std;

class Audio{
public:
	Audio();
	void playOneTime(string type);
	void playAllTime(string type);
private:
	Mix_Music* soundEffect;
	Mix_Chunk* Effect;
};