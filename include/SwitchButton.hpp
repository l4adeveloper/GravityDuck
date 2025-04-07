#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "Utils.hpp"
#include "RenderWindows.hpp"
#include "Player.hpp"
using namespace std;
class SwitchButton {
public:
	SwitchButton(){;}
	~SwitchButton(){;}
	void Spawn(RenderWindows* windows);
	void CheckCollision(Player* player);
	void Import(vector<ObjButton>swButton);
private:
	vector<ObjButton>allSwButton;
	float rotationAngle = 0.0f;
	float rotationSpeed = 5.0f;
	bool check[105] = {false};
};