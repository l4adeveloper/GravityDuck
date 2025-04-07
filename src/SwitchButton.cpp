#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "RenderWindows.hpp"
#include "Utils.hpp"
#include "Player.hpp"
#include "Audio.hpp"
#include "SwitchButton.hpp"
void SwitchButton::Import(vector<ObjButton> vt) {
	allSwButton.clear();
	allSwButton = vt;
}
void SwitchButton::Spawn(RenderWindows* windows){
	rotationAngle += rotationSpeed;
	if (rotationAngle >= 360.0f) rotationAngle -= 360.0f;
	for(auto &button : allSwButton) {
		if(button.x == 0 && button.y == 0) continue;
		//cout << button.x << ' ' << button.y << '\n';
		SDL_Rect dstRect = {(int)button.x , (int)button.y , 48 , 48};
		SDL_Point center = {24 , 24};
		SDL_RenderCopyEx(windows -> getRenderer() , Img_Switch_Button, nullptr, &dstRect,	 rotationAngle, &center, SDL_FLIP_NONE);
	}
}
void SwitchButton::CheckCollision(Player* player) {
	pair<float , float>posPlayer = player -> getPos();
	int s_x = posPlayer.first;
	int s_y = posPlayer.second;
	if(player -> checkTouch() == true) {
		for(int i = 0 ; i < (int)allSwButton.size() ; i++) check[i] = false;
	}
	int i = 0;
	int aud = 0;
	for(auto &button : allSwButton) {
		if(button.x == 0 && button.y == 0) continue;
		int player_cx = s_x + PLAYER_SIZE / 2;
		int player_cy = s_y + PLAYER_SIZE / 2;
		int button_cx = button.x + 24;	
		int button_cy = button.y + 24;
		int dx = player_cx - button_cx;
		int dy = player_cy - button_cy;	
		float distance = sqrt(dx * dx + dy * dy);
		if(distance < 10) {
			if(check[i] == true) continue;
			aud = 1;
			 if(player -> getGravity() == 0) player -> updateGravity(3);
			 else if(player -> getGravity() == 1) player -> updateGravity(0);
			 else if(player -> getGravity() == 3) player -> updateGravity(2);
			 else if(player -> getGravity() == 2) player -> updateGravity(1);
			 if(player -> checkTouch() == true)  player -> updateTouch(false);
			 for(int j = 0 ; j < (int)allSwButton.size() ; j++) {
			 	check[j] = false;
			 }
			 check[i] = true;
			//cout << "touch";
		}
		i++;
	}
	if(aud) audio.playOneTime("touch");
}