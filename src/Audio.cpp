#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "Audio.hpp"
using namespace std;
Audio::Audio():soundEffect(NULL) {}
void Audio::playOneTime(string type){
	if(type == "dead") {
		Effect = Mix_LoadWAV("res/audio/Dead.wav");
	}
	if(type == "fly") {
		Effect = Mix_LoadWAV("res/audio/Switch.wav");
	}
	if(type == "pick") {
		Effect = Mix_LoadWAV("res/audio/Pick_Egg.wav");
	}
	if(type == "touch") {
		Effect = Mix_LoadWAV("res/audio/Touch_Switch.wav");
	}
	Mix_PlayChannel(-1 , Effect , 0);
}
void Audio::playAllTime(string type){
	if(type == "bgr") {
		soundEffect = Mix_LoadMUS("res/audio/Background.mp3");
	}
	Mix_PlayMusic(soundEffect , -1);
}
