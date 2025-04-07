#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "RenderWindows.hpp"
#include "Utils.hpp"
#include "Player.hpp"
#include "Audio.hpp"
inline int FRAME_DELAY_MOVE = 40;
inline int lastFrameTime = 0;
void Player::Import(int xx , int yy , int Gra) {
    s_x = xx;
    s_y = yy;
    x = xx;
    y = yy; 
    s_Gra = 2;
};

bool Player::checkPicked() {
    return isPick;
}
int Player::getGravity() {
    return s_Gra;
}
pair<float , float> Player::getPos() {
    return {s_x , s_y};
}
void Player::doPlayer() {
    if (s_Gra == 2) { 
        vx = 0;
        vy += GRAVITY;
        if (vy > MAX_VELOCITY) vy = MAX_VELOCITY;
        if (input_type_left == 1) vx -= PLAYER_SPEED;
        else if (input_type_right == 1) vx += PLAYER_SPEED;
    }
    else if (s_Gra == 0) { // Gravity lên
        vx = 0;
        vy -= GRAVITY;
        if (vy < -MAX_VELOCITY) vy = -MAX_VELOCITY;
        if (input_type_left == 1) vx -= PLAYER_SPEED;
        else if (input_type_right == 1) vx += PLAYER_SPEED;
    }
    else if (s_Gra == 3) { 
        vy = 0;
        vx += GRAVITY;
        if (vx > MAX_VELOCITY) vx = MAX_VELOCITY;
        if (input_type_up == 1) vy -= PLAYER_SPEED;     
        else if (input_type_down == 1) vy += PLAYER_SPEED; 
    }
    else if (s_Gra == 1) { 
        vy = 0;
        vx -= GRAVITY;
        if (vx < -MAX_VELOCITY) vx =-MAX_VELOCITY;
        if (input_type_up == 1) vy -= PLAYER_SPEED;
        else if (input_type_down == 1) vy += PLAYER_SPEED;
    }

    CheckCollision();
}
void Player::Reset() {
    s_x = x;
    s_y = y;
    frameMove = 0;
    frameX = 1;
    isFallingTrap = false;
    fallDistance = 0;
    currentFrame = 0;
    s_Gra = 2;
    frameDelay = 0;
    vx = 0;
    vy = 0;
    gravityInverted  = false;
    GRAVITY = 0.38f;
    input_type_left = -1;
    input_type_right = -1;
    on_ground = 0;
    isPicked = false;
    died = false;
}
bool Player::checkLive() {
    return !died;
}
void Player::ImportEgg(float x , float y, int destGra) {
    dest_x = x;
    dest_y = y;
    dest_Gra = destGra;
}
void Player::CheckCollision() {
    int x1 = (s_x + vx) / TILE_SIZE;
    int x2 = (s_x + vx + PLAYER_SIZE - 1) / TILE_SIZE;
    int y1 = s_y / TILE_SIZE;
    int y2 = (s_y + PLAYER_SIZE - 1) / TILE_SIZE;
    int y1_p = (s_y + 4) / TILE_SIZE;
    int x1_p = (s_x + vx + 4) / TILE_SIZE;
    int x2_p = (s_x + vx + PLAYER_SIZE / 2 + 4) / TILE_SIZE;
    int y2_p = (s_y + PLAYER_SIZE / 2 + 4) / TILE_SIZE;
    if (isFallingTrap == true) {
        const int fallSpeed = 4;
        if (fallDistance == 0) {
            audio.playOneTime("dead");
        }
        if (gravityInverted == true && fallDistance < 16 && (isTrap == 6 || isTrap == 7)) {
            s_y -= fallSpeed;
            fallDistance += fallSpeed;
        }
        else if (fallDistance < 16 && (s_Gra == 3 || s_Gra == 2) && (isTrap == 6 || isTrap == 7)) {
            s_y += fallSpeed;
            fallDistance += fallSpeed;
        }
        else if (fallDistance < 16 && (isTrap == 3 || isTrap == 4)) {
            s_x -= fallSpeed;
            fallDistance += fallSpeed;
        }
        else if (fallDistance < 16 && isTrap == 9) {
            s_x += fallSpeed;
            fallDistance += fallSpeed;
        }
        else {
            gravityInverted = false;
            died = true;
        }
        return;
    }
    if(s_x + 32 > WIDTH || s_y + 32 > HEIGHT || s_x < 0 || s_y < 0) {
        isFallingTrap = true;
        isTrap = 3;
    }
    if (Mapp[x2][y1] == CL_TILE_DEST && ((s_Gra == dest_Gra) || (s_Gra == 1 && dest_Gra == 3) || (s_Gra == 3 && dest_Gra == 1))) isPick = true;
    if (x1 >= 0 && x2 < MAX_X_NO_PADDING && y1 >= 0 && y2 < MAX_Y_NO_PADDING) {
        if (vx > 0 && (Mapp[y1_p][x2] != CL_TILE_NOTHING || Mapp[y2_p][x2] != CL_TILE_NOTHING)) {
            canInv = true;
            canTouch = true;
           // cout << "1";
            s_x = x2 * TILE_SIZE - PLAYER_SIZE;
            vx = 0;
            if (Mapp[y1_p][x2_p] == CL_TILE_TRAP) {
                isFallingTrap = true;
                isTrap = 9;
            }
            if (Mapp[y2_p][x2_p] == CL_TILE_TRAP) {
                isFallingTrap = true;
                isTrap = 9;
            }
            if (Mapp[y1_p][x2] == CL_TILE_TRAP && Mapp[y2_p][x2] == CL_TILE_TRAP) {
                isFallingTrap = true;
                isTrap = 9;
            }
        } else if (vx < 0 && (Mapp[y1][x1] != CL_TILE_NOTHING || Mapp[y2][x1] != CL_TILE_NOTHING)) {
            canInv = true;
            canTouch = true;
           // cout << "2";
            s_x = (x1 + 1) * TILE_SIZE;
            vx = 0;
            int newx1_p = (s_x + vx + 2) / TILE_SIZE;
            if(Mapp[y2_p][x1] == CL_TILE_TRAP && Mapp[y1_p][x1] == CL_TILE_TRAP) {
               // cout << "This1";
              //  cout << "HERE"
                isFallingTrap = true;
                isTrap = 3;
            }
            if (Mapp[y1][x1_p] == CL_TILE_TRAP) {
                isFallingTrap = true;
                isTrap = 3;
            }
            if (Mapp[y2][x1_p] == CL_TILE_TRAP) {
                isFallingTrap = true;
                isTrap = 4;
            }
        }
    }
    x1 = s_x / TILE_SIZE;
    x2 = (s_x + PLAYER_SIZE - 1) / TILE_SIZE;
    y1 = (s_y + vy) / TILE_SIZE;
    y2 = (s_y + vy + PLAYER_SIZE + 1) / TILE_SIZE;
    x2_p = (s_x + PLAYER_SIZE / 2 + 5) / TILE_SIZE;
    y2_p = (s_y + vy + PLAYER_SIZE) / TILE_SIZE;
    y1_p = (s_y + vy - 1) / TILE_SIZE;
    x1_p = (s_x + 4) / TILE_SIZE;
    if (Mapp[x2][y1] == CL_TILE_DEST && ((s_Gra == dest_Gra) || (s_Gra == 1 && dest_Gra == 3) || (s_Gra == 3 && dest_Gra == 1))) isPick = true;
    if (x1 >= 0 && x2 < MAX_X_NO_PADDING && y1 >= 0 && y2 < MAX_Y_NO_PADDING) {
        if (vy > 0 && (Mapp[y2][x1] != CL_TILE_NOTHING || Mapp[y2][x2] != CL_TILE_NOTHING)) {
          //  cout << "3";
           // cout << "Here1";
            canInv = true;
            canTouch = true;
            s_y = y2 * TILE_SIZE - PLAYER_SIZE;
            vy = 0;
            on_ground = 1;
            if (Mapp[y2_p][x2_p] == CL_TILE_TRAP) {
                isFallingTrap = true;
                isTrap = 6;
            }
        } else if (vy < 0 && (Mapp[y1][x1] != CL_TILE_NOTHING || Mapp[y1][x2] != CL_TILE_NOTHING)) {
           // cout << "4";
            canInv = true;
            canTouch = true;
            s_y = (y1 + 1) * TILE_SIZE;
            vy = 0;
            if (Mapp[y1_p][x1_p] == CL_TILE_TRAP && Mapp[y1_p][x2_p] == CL_TILE_TRAP) {
                isFallingTrap = true;
                isTrap = 7;
            }
        } else {
            on_ground = 0;
        }
    }
    s_x += vx;
    s_y += vy;
    if (isPick == true) audio.playOneTime("pick");
}
bool Player::checkTouch() {
    return canTouch;
}
void Player::updateInv(bool value) {
    canInv = value;
}
void Player::setPickedSuccess() {
    isPicked = true;
}
bool Player::checkInv() {
    return canInv;
}
bool Player::getPick() {
    return isPick;
}
bool Player::checkPickedSucces() {
    return isPicked;
}
void Player::setPicked(bool value) {
    isPick = value;
}
void Player::updateGravity(int value) {
    s_Gra = value;
}
void Player::updateTouch(bool value) {
    canTouch = value;
}
void Player::HandlePlayer(SDL_Event events) {
    if (events.type == SDL_KEYDOWN) {
        switch (events.key.keysym.sym) {
        case SDLK_RIGHT:
            input_type_left = 0;
            input_type_up = 0;
            input_type_down = 0;
            input_type_right = 1;
            frameX = 1;
            break;
        case SDLK_LEFT:
            input_type_left = 1;
            input_type_right = 0;
            input_type_up = 0;
            input_type_down = 0;
            frameX = 0;
            break;
        case SDLK_UP:
            input_type_left = 0;
            input_type_right = 0;
            input_type_up = 1;
            input_type_down = 0;
            frameX = 0;
            break;
        case SDLK_DOWN:
            input_type_left = 0;
            input_type_right = 0;
            input_type_up = 0;
            input_type_down = 1;
            frameX = 1;
            break;
        case SDLK_SPACE:
            if (canInv == true) {
                if(s_Gra == 2) s_Gra = 0;
                else if(s_Gra == 1) s_Gra = 3;
                else if(s_Gra == 0) s_Gra = 2;
                else if(s_Gra == 3) s_Gra = 1;
                audio.playOneTime("fly");
                canInv = false;
            }
            break;
        default:
            break;
        }
    } else if (events.type == SDL_KEYUP) {
        switch (events.key.keysym.sym) {
        case SDLK_RIGHT:
            input_type_right = 0;
            vx = 0;
            frameMove = 0;
            break;
        case SDLK_LEFT:
            input_type_left = 0;
            frameMove = 0;
            vx = 0;
            break;
        case SDLK_UP:
            input_type_up = 0;
            frameMove = 0;
            vy = 0;
            break;
        case SDLK_DOWN:
            input_type_down = 0;
            frameMove = 0;
            vy = 0;
            break;
        default:
            break;
        }
    }
}
// 2 default
// 0 gia toc < 0
// 1 gia toc theo x < 0
// 3 gia toc theo x > 0
void Player::showPlayer(RenderWindows* window) {
    int currentTime = SDL_GetTicks();
    bool isMoving = (input_type_left == 1 || input_type_right == 1 || input_type_up == 1 || input_type_down == 1);
    if (isMoving) {
        if (currentTime - lastFrameTime > FRAME_DELAY_MOVE) {
            frameMove = (frameMove + 1) % 7;
            lastFrameTime = currentTime;
        }
    } else {
        frameMove = 0;
    }
    SDL_Rect dest = {(int)s_x , (int)s_y , 32 , 32};
    if (died == true) {
        window->RenderTexture(Img_Player_Death, NULL, &dest);
    }
    else {
        if (frameMove == 0) {
            dest = {(int)s_x , (int)s_y , 32 , 32};
            window->RenderTexture(Img_Player_Spawn[s_Gra][frameX][7], NULL, &dest);
        }
        else {
            window->RenderTexture(Img_Player_Run[s_Gra][frameX][frameMove - 1], NULL, &dest);
        }
    }
}
void Player::Update() {
    if (isSpawning) {
        frameDelay++;
        if (frameDelay >= 4) {
            currentFrame++;
            frameDelay = 0;
            if (currentFrame > 6) {
                isSpawning = false;
            }
        }
    }
}
void Player::loadPlayer(RenderWindows* window) {
    if (!isSpawning) return;
    SDL_Rect destRect = {(int)s_x , (int)s_y , 32 , 32};
    window->RenderTexture(Img_Player_Spawn[s_Gra][frameX][currentFrame], NULL, &destRect);
}
void Player::hidePlayer(RenderWindows* window) {
    if (!isSpawning) return;
    SDL_Rect destRect = {(int)s_x , (int)s_y , 32 , 32};
    window->RenderTexture(Img_Player_Spawn[s_Gra][frameX][5 - currentFrame], NULL, &destRect);
}
