#include <iostream>
#include <memory>
#include "RenderWindows.hpp"
#include "Utils.hpp"
#include "Audio.hpp"
#include "SwitchButton.hpp"
#include "Maps.hpp"
#include "Player.hpp"
const int FPS = 40;
const int frameDelay = 1000 / FPS;
using namespace std;
int main(int argc, char* args[]) {
    freopen("NUL", "w", stderr);
    auto window = make_unique<RenderWindows>("Gravity Duck - cloned by l4adeveloper", WIDTH, HEIGHT);
    GameMap gameMap;
    auto player = make_unique<Player>();
    auto switchbutton = make_unique<SwitchButton>();
    gameMap.LoadTiles(window.get());
    gameMap.LoadPlayerAnimation(window.get());
    gameMap.LoadEggAnimation(window.get());
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0 || Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        cerr << "Failed to initialize audio!\n";
        return -1;
    }
    SDL_Rect startRect = { 157, 277, 327, 59 };
    audio.playAllTime("bgr");
    bool running = true;
    SDL_Event e;
   // SDL_Delay(500);
    int level = 1;
    gameState = MENU;
    while (running) {
        bool isCheated = false;
        Uint32 startTime = SDL_GetTicks();
         while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            else if (e.type == SDL_KEYDOWN && gameState == MENU) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if(e.key.keysym.scancode  == SDL_SCANCODE_RETURN) {
                    gameState = PLAYING;
                    window -> fadeOutScreen();
                }
            }
            else if ((e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) && gameState == PLAYING) {
                if(e.key.keysym.sym == SDLK_d) isCheated = true;
                else if(e.key.keysym.scancode  == SDL_SCANCODE_ESCAPE) {
                    gameState = MENU;
                    level = 1;
                    player -> Reset();
                    gameMap.Reset();
                    window -> fadeOutScreen();
                }
                else player -> HandlePlayer(e);
            }
        }
        window->init();
        if(isCheated == true) {
            player -> setPicked(true);
        }
        if(gameState == MENU) {
            backGround = window->loadTexture("res/image/Menu/BG.png");
            mainMenu = window->loadTexture("res/image/Menu/Main.png");
            window->UpdatebgX();
            window->RenderBackground(backGround, NULL, NULL);
            window->RenderTexture(mainMenu, NULL, NULL);
        }
        if (gameState == PLAYING) {
            SDL_DestroyTexture(mainMenu);
            SDL_DestroyTexture(backGround);
            SDL_Texture* backGroundInGame = window->loadTexture("res/image/Game/BG.png");
            window->RenderTexture(backGroundInGame, NULL, NULL);
            gameMap.LoadMap(level, player.get() , switchbutton.get());
            gameMap.DrawMap(window.get());
            gameMap.SpawnEgg(window.get() , player.get(), 0);
            switchbutton -> Spawn(window.get());
            if(player -> checkPicked() == true) {
                gameMap.Update(player.get());
                gameMap.PickEgg(window.get() , player.get());
                isSpawning = true;
                if(player -> checkPickedSucces() == true) {
                    level++;
                    player -> Reset();
                    gameMap.Reset();
                    window -> fadeOutScreen();
                    continue; 
                }
            }
            else {
                gameMap.Update(player.get());
                gameMap.SpawnEgg(window.get() , player.get() , 1);
            }
            if (isSpawning && player -> checkPicked() == false) {
                player -> Update();
                player -> loadPlayer(window.get());
            }  
            else if(isSpawning && player -> checkPicked() == true) {
                player -> Update();
                player -> hidePlayer(window.get());
            }   
            else{
                player -> doPlayer();
                player -> showPlayer(window.get());
                switchbutton -> CheckCollision(player.get());
            }
        }
        if(player -> checkLive() == false) {
            isSpawning = true;
            player -> Reset();
            window -> fadeOutScreen();
        }
        window->display();
        Uint32 frameTime = SDL_GetTicks() - startTime;
        if (frameTime < frameDelay) SDL_Delay(frameDelay - frameTime);
    }
    window->cleanUp();
    SDL_Quit();
    return 0;
}
