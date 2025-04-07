#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
class RenderWindows{
public:
	RenderWindows(const char* p_title , int p_w , int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	SDL_Renderer* getRenderer();
	void cleanUp();
	void clear();
	void RenderTexture(SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect);
	void RenderBackground(SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect);
	void RenderClear();
	void display();
	void fadeOutScreen();
	void fadeInScreen();
	void init();
	void fade();
	void UpdatebgX();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};