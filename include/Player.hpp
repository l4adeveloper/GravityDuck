#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "Utils.hpp"
#include "RenderWindows.hpp"
class Player{
	public:
		// float s_x, s_y, x, y, vx = 0, vy = 0, gx = 0, gy = 0, Alpha;
	 //    float dest_x , dest_y;
  //   	int s_Gra, Gra, Drt, Stt, Is_Run, Is_Jump;
  //   	int currentFrame  = 0, frameDelay = 0;
		Player(){;}
		~Player(){;}
		//void Init(double x , double y , double gra,  double destX , double destY , double destGra);
		void Import(int xx , int yy , int Gra);
		void Update();
		bool checkInv();
		void updateInv(bool value);
		bool playGame();
		void loadPlayer(RenderWindows* window);
		void hidePlayer(RenderWindows* window);
		void doPlayer();
		void updateGravity(int newGra);
		int getGravity();
		void showPlayer(RenderWindows* window);
		void HandlePlayer(SDL_Event events);
		pair<float , float>getPos();
		void ImportEgg(float pos_x , float pos_y , int destGra);
		bool checkPickedSucces();
		void setPickedSuccess();
		void CheckCollision();
		void updateTouch(bool value);
		bool checkTouch();
		bool checkPicked();
		bool getPick();
		void setPicked(bool status);
		bool checkLive();
		void Reset();
	private: 
	    float s_x, s_y, x, y, vx = 0, vy = 0, gx = 0, gy = 0, Alpha;
	    float dest_x , dest_y;
    	int s_Gra = 0, Gra, Drt, Stt, Is_Run, Is_Jump;
    	int dest_Gra = 0;
    	int input_type_left = -1 , input_type_right = -1;
    	int input_type_down = -1 , input_type_up = -1;
    	bool on_ground = 0;
    	int currentFrame  = 0, frameDelay = 0;
    	bool isPick = false;
    	int frameX = 1;
    	int frameMove = 0;
    	int fallDistance = 0;
    	int isTrap = 0;
    	bool isPicked = false;
    	bool gravityInverted = false;
    	bool canTouch = false;
    	bool canInv = false;
    	float GRAVITY = 0.38f;
    	float GRAVITY_X = 0.0f;
    	bool isFallingTrap = false;
    	bool died = false;
    	struct Dest{
    		int x , y , gra;
    	}dest;
};