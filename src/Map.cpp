#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "Utils.hpp"
#include "Player.hpp"
#include "RenderWindows.hpp"
#include "SwitchButton.hpp"
#include "Maps.hpp"
#include "bits/stdc++.h"
using namespace std;
void GameMap::LoadPlayerAnimation(RenderWindows* window) {
    SDL_Texture* img = window -> loadTexture("res/image/Game/Player.png");
    Img_Switch_Button = window -> loadTexture("res/image/Game/Switch.png");
    for(int i = 0 ; i < 6 ; i++) {
    	int x = Pos[i][0] , y = Pos[i][1];
    	int w = Pos[i][2] , h = Pos[i][3];
    	Img_Player_Run[2][1][i] = Crop_Image(img , window -> getRenderer() , x , y , w , h);
    	Img_Player_Run[3][0][i] = Rotate_Left(window -> getRenderer() , Img_Player_Run[2][1][i]);
    	Img_Player_Run[0][0][i] = Rotate_180(window -> getRenderer() , Img_Player_Run[2][1][i]);
    	Img_Player_Run[1][1][i] = Rotate_180(window -> getRenderer() , Img_Player_Run[3][0][i]);
    	Img_Player_Run[0][1][i] = Flip_Horizontal(window -> getRenderer() , Img_Player_Run[0][0][i]);
    	Img_Player_Run[1][0][i] = Flip_Vertical(window -> getRenderer() , Img_Player_Run[1][1][i]);
    	Img_Player_Run[2][0][i] = Flip_Horizontal(window -> getRenderer() ,Img_Player_Run[2][1][i]);
    	Img_Player_Run[3][1][i] = Flip_Vertical(window -> getRenderer() , Img_Player_Run[3][0][i]);
    }
    for(int i = 0 ; i < 8 ; i++) {
    	int x = Pos[i + 6][0] , y = Pos[i + 6][1];
    	int w = Pos[i + 6][2] , h = Pos[i + 6][3];
    	Img_Player_Spawn[2][1][i] = Crop_Image(img , window -> getRenderer() , x , y , w , h);
    	Img_Player_Spawn[3][0][i] = Rotate_Left(window -> getRenderer() , Img_Player_Spawn[2][1][i]);
    	Img_Player_Spawn[0][0][i] = Rotate_180(window -> getRenderer() , Img_Player_Spawn[2][1][i]);
    	Img_Player_Spawn[1][1][i] = Rotate_180(window -> getRenderer() , Img_Player_Spawn[3][0][i]);
    	Img_Player_Spawn[0][1][i] = Flip_Horizontal(window -> getRenderer() , Img_Player_Spawn[0][0][i]);
    	Img_Player_Spawn[1][0][i] = Flip_Vertical(window -> getRenderer() , Img_Player_Spawn[1][1][i]);
    	Img_Player_Spawn[2][0][i] = Flip_Horizontal(window -> getRenderer() ,Img_Player_Spawn[2][1][i]);
    	Img_Player_Spawn[3][1][i] = Flip_Vertical(window -> getRenderer() , Img_Player_Spawn[3][0][i]);
    }
    for(int i = 0 ; i < 4 ; i++) {
    	for(int j = 0 ; j < 2 ; j++) Img_Player_Stand[i][j] = Img_Player_Spawn[i][j][7];
    }
	SDL_DestroyTexture(img);
    Img_Player_Death = window -> loadTexture("res/image/Game/Death.png");
}
void GameMap::Reset() {
	importedPlayer = 0;
	frameDelay = 0;
	currentFrame = 0;
}
void GameMap::LoadMap(int level , Player* player , SwitchButton* swbutton){
	string filePath = "Maps/" + to_string(level) + ".txt";
	ifstream readFile(filePath);
	if(!readFile) {
		cerr << "Failed Open Map";
		return;
	}
	double s_x , s_y , s_gra , destX , destY , destGra;
	readFile >> s_x >> s_y >> s_gra >> destX >> destY >> destGra;
	if(importedPlayer == 0) {
		player -> Import(s_x , s_y, s_gra);
		importedPlayer = 1;
	}
	g_e = destGra;
	dest_x = destX;
	dest_y = destY;
	x = destX * 32;
	y = destY * 32;
	// dest.x = x;
	// dest.y = y;
	// dest.gra = g_e;
	player -> ImportEgg(destX * 32 , destY * 32 , destGra);
	for (int i = 2; i < MAX_Y_NO_PADDING; i++) {
		for(int j = 2 ; j < MAX_X_NO_PADDING ; j++) {		
			readFile >> game_map.tile[i][j];
		}
	}
	double numButton;
	readFile >> numButton;
	vector<ObjButton>vec(numButton);
	for(int i = 0 ; i < numButton ; i++) {
		readFile >> vec[i].x >> vec[i].y >> vec[i].gra;
	}
	swbutton -> Import(vec);
	readFile.close();
}
void GameMap::PickEgg(RenderWindows* window, Player* player) { 
	if(player -> getPick() == true) {
		SDL_Rect rect = {x - 16 , y - 16 , 64 , 64};
		if(currentFrame == 3) window -> RenderTexture(Img_Egg_Pick[currentFrame] , NULL , &rect);
		window -> RenderTexture(Img_Egg_Pick[currentFrame] , NULL , &rect);
	} 
}
void GameMap::Update(Player* player) {
	if(player -> getPick() == false) return;
	frameDelay++;
    if (frameDelay >= 4) { 
        currentFrame++;
       	frameDelay = 0;
       if (currentFrame > 4) {
            player -> setPicked(false);
            player -> setPickedSuccess();
            currentFrame = 0;
        }
    }
}
void GameMap::LoadEggAnimation(RenderWindows* window) {
	SDL_Texture* img = window -> loadTexture("res/image/Game/Egg.png");
	// Img_Egg_Spawn[2][0] -> Egg 
	// Img_Egg_Spawn[2][1] -> Hide Egg
	// Img_Egg_Spawn[1][0] -> down
	// Img_Egg_Spawn[1][1]
	for(int i = 0 ; i < 2 ; i++) {
		int x = posEgg[i][0] , y = posEgg[i][1];
		int w = posEgg[i][2] , h = posEgg[i][3];
		Img_Egg_Spawn[2][i] = Crop_Image(img , window -> getRenderer() , x , y , w , h);
	}
	for(int i = 2 ; i < 6 ; i++) {
		int x = posEgg[i][0] , y = posEgg[i][1];
		int w = posEgg[i][2] , h = posEgg[i][3];
		Img_Egg_Pick[i - 2] = Crop_Image(img , window -> getRenderer() , x , y , w , h);
	}
	Img_Egg_Spawn[0][0] = Rotate_180(window -> getRenderer() , Img_Egg_Spawn[2][0]);	
	Img_Egg_Spawn[0][1] = Rotate_180(window -> getRenderer() , Img_Egg_Spawn[2][1]);
	Img_Egg_Spawn[1][0] = Rotate_Left(window -> getRenderer() , Img_Egg_Spawn[2][0]);
	Img_Egg_Spawn[1][1] = Rotate_Left(window -> getRenderer() , Img_Egg_Spawn[2][1]);
	SDL_DestroyTexture(img);
}
void GameMap::SpawnEgg(RenderWindows* window , Player* player, int status) {
	SDL_Rect rect = {x , y , 32 , 32};
	if(status == 1) window -> RenderTexture(Img_Egg_Spawn[g_e][0] , NULL , &rect);
	else window -> RenderTexture(Img_Egg_Spawn[g_e][1] , NULL , &rect);
}
void GameMap::LoadTiles(RenderWindows* window) {
	SDL_Texture* img = window -> loadTexture("res/image/Game/Tiles.png");
	for(int i = 0 ; i < TILE_MAX ; i++) {
		int x = (i % 11) * TILE_SIZE;
		int y = (i / 11) * TILE_SIZE;
		imgTex[i] = Crop_Image(img , window -> getRenderer() , x , y , TILE_SIZE , TILE_SIZE);
	}
	SDL_DestroyTexture(img);
}
void GameMap::DrawMap(RenderWindows* window) {
	for(int i = 2 ; i < MAX_Y_NO_PADDING ; i++) {
		for(int j = 2 ; j < MAX_X_NO_PADDING ; j++) {
			if(game_map.tile[i][j] == -1) continue;
			SDL_Rect dstRect = {(j - 2) * TILE_SIZE , (i - 2) * TILE_SIZE , TILE_SIZE , TILE_SIZE};
			window -> RenderTexture(imgTex[game_map.tile[i][j]] , NULL , &dstRect);
		}
	}
	for(int i = 2 ; i < MAX_Y_NO_PADDING ; i++) {
		for(int j = 2 ; j < MAX_X_NO_PADDING ; j++) {
			if(game_map.tile[i][j] == -1) Mapp[i - 2][j - 2] = CL_TILE_NOTHING;
			else Mapp[i - 2][j - 2] = Tile_Mapping[game_map.tile[i][j]];
		}
	}
	Mapp[(int)dest_x][(int)dest_y] = CL_TILE_DEST;
} 