#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "Player.hpp"
#include "SwitchButton.hpp"
#include "Utils.hpp"
#include "RenderWindows.hpp"
class TileMat {
public:
	TileMat() {;}
	~TileMat() {;}
};
class GameMap {
public:
	GameMap(){;}
	~GameMap() {;}
	void LoadMap(int level , Player* player ,  SwitchButton* swbutton);
	void LoadTiles(RenderWindows* window);
	void ImportEgg(int _g_e , int _x , int _y);
	void LoadPlayerAnimation(RenderWindows* window);
	void Update(Player* player);
	void Reset();
	void PickEgg(RenderWindows* window, Player* player);
	void LoadEggAnimation(RenderWindows* window);
	void SpawnEgg(RenderWindows* window, Player* player, int status);
	void DrawMap(RenderWindows* window);
private: 
	Map game_map;
	Map mapp;
	SDL_Texture* imgTex[105];
	int currentFrame = 0;
	int frameDelay = 0;
	int g_e = 2, x = 0 , y = 0;
	int switch_x = 0 , switch_y = 0;
	int dest_x , dest_y;
	int importedPlayer = 0 , importedDest = 0;
	TileMat tile_mat[TILE_MAX]; // number of different texture
};