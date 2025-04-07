#pragma once
#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include "Audio.hpp"
#define WIDTH 640
#define HEIGHT 480
#define INTERVAL 25
#define MAX_X 24
#define MAX_Y 19
#define MAX_X_NO_PADDING 22
#define MAX_Y_NO_PADDING 17
#define RADIAN 57.2958f
#define MAX_VELOCITY 13.0f
#define MENU_BG_MAX_OFFSET 128
#define PLAYER_SIZE 30
#define PLAYER_SIZE_HALF 16
#define TILE_SIZE 32
#define PLAYER_SPEED 5.5f
#define TILE_SIZE_HALF 16
#define PLAY_SIZE_TRAP 28
#define TILE_MAX 44
#define SWITCH_MAX 10
#define SWITCH_SIZE 20
using namespace std;
inline int ANIMATION_FRAMES_SPAWN = 7;
const int TARGET_FPS = 100;
const int FRAME_DELAY = 1000 / TARGET_FPS;
enum GameState { MENU, TRANSITION_OUT, LOADING, TRANSITION_IN, PLAYING };
enum COLLISION_TILE {
    CL_TILE_WALL,
    CL_TILE_NOTHING,
    CL_TILE_TRAP,
    CL_TILE_DEST
};
inline int Tile_Mapping[] = {CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL,
                      CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL,
                      CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL,
                      CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL,
                      CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL, CL_TILE_WALL,
                      CL_TILE_TRAP, CL_TILE_TRAP, CL_TILE_TRAP, CL_TILE_TRAP};
inline GameState gameState = MENU;
inline int Mapp[MAX_Y][MAX_X];
inline SDL_Texture* backGround;
inline SDL_Texture* mainMenu;
struct Map{
	int startX;
	int startY;
	int maxX;
	int maxY;
	int tile[105][105];
	char* file_name;
};
struct Rect {
    float Left, Right, Bottom, Top;
};
struct ObjButton{
    float x , y , gra;
};
struct Pos {
    float x, y;
};

struct Point {
    int x, y;
};
inline bool isSpawning = true;
inline Audio audio;
inline SDL_Texture* Img_Player_Spawn[4][2][8];
inline SDL_Texture* Img_Player_Run[4][2][6];
inline SDL_Texture* Img_Player_Stand[4][2]; 
inline SDL_Texture* Img_Player_Jump[4][2]; 
inline SDL_Texture* Img_Player_Death;
inline SDL_Texture* Img_Egg_Spawn[4][4];
inline SDL_Texture* Img_Egg_Pick[12];
inline SDL_Texture* Img_Egg_Gra0;
inline SDL_Texture* Img_Switch_Button;
inline int Pos[][4] = {
        {0, 0, 32, 32},
        {32, 0, 32, 32},
        {64, 0, 32, 32},
        {96, 0, 32, 32},
        {128, 0, 32, 32},
        {160, 0, 32, 32},
        {192, 0, 32, 32},
        {0, 32, 32, 32},
        {32, 32, 32, 32},
        {64, 32, 32, 32},
        {96, 32, 32, 32},
        {128, 32, 32, 32},
        {160, 32, 32, 32},
        {192, 32, 32, 32}};
inline int posEgg[][6] = {
        {0, 0, 32, 32},
        {0, 32, 32, 32},
        {32, 0, 64, 64},
        {96, 0, 64, 64},
        {160, 0, 64, 64},
        {224, 0, 64, 64}
};
SDL_Texture* Crop_Image(SDL_Texture* source,  SDL_Renderer* renderer , int x, int y, int w, int h);
SDL_Texture* Rotate_Left(SDL_Renderer *renderer, SDL_Texture *srcTexture);
SDL_Texture* Rotate_180(SDL_Renderer *renderer, SDL_Texture *srcTexture);
SDL_Texture* Flip_Horizontal(SDL_Renderer *renderer, SDL_Texture *srcTexture);
SDL_Texture* Flip_Vertical(SDL_Renderer *renderer, SDL_Texture *srcTexture);

