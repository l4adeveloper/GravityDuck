#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "RenderWindows.hpp"
#include "Utils.hpp"
int bgX = 0;
const int SCROLL_SPEED = 1;
using namespace std;
RenderWindows::RenderWindows(const char* p_title , int p_w , int p_h)
	:window(NULL), renderer(NULL)
 {
	window = SDL_CreateWindow(p_title , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED, p_w , p_h , SDL_WINDOW_SHOWN);
	if(window == NULL) {
		std::cout << "Fail";
	}
	renderer = SDL_CreateRenderer(window , -1 , SDL_RENDERER_ACCELERATED);
}
SDL_Texture* RenderWindows::loadTexture(const char* path){
 	SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        std::cout << "Failed to load image: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
SDL_Renderer* RenderWindows::getRenderer() {
    return renderer;
}
void RenderWindows::cleanUp(){
	SDL_DestroyWindow(window);
}
void RenderWindows::clear(){
	SDL_RenderClear(renderer); 
}
void RenderWindows::RenderTexture(SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect) {
	SDL_RenderCopy(renderer , texture , srcrect , dstrect);
}
void RenderWindows::UpdatebgX(){
	bgX -= SCROLL_SPEED; 
    if (bgX <= -640) {
        bgX = 0;
    }
}
void RenderWindows::init() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer); 
}
void RenderWindows::RenderBackground(SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect) {
	SDL_Rect bg1 = { bgX, 0, 640, 480 };
    SDL_RenderCopy(renderer, texture, nullptr, &bg1);
    SDL_Rect bg2 = { bgX + 640, 0, 640, 480 };
    SDL_RenderCopy(renderer, texture, nullptr, &bg2);
}
void RenderWindows::fadeOutScreen(){
    int speed =  5;
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); 
    Uint8 alpha = 0;
    while (alpha < 255) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha); 
        SDL_RenderFillRect(renderer, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
        alpha += speed;
        if (alpha > 255) alpha = 255;
    }
}
void RenderWindows::fadeInScreen() {
    int speed = 5;
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    Uint8 alpha = 255;
    
    while (alpha > 0) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
        SDL_RenderFillRect(renderer, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
        alpha -= speed;
        if (alpha < 0) alpha = 0;
    }
}
void RenderWindows::fade()
{

}

// };
void RenderWindows::display() {
	SDL_RenderPresent(renderer);
}