#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Utils.hpp"
#include "Player.hpp"
#include "RenderWindows.hpp"
#include "Maps.hpp"
#include <bits/stdc++.h>
SDL_Texture* Crop_Image(SDL_Texture* source, SDL_Renderer* renderer, int x, int y, int w, int h) {
    SDL_Texture* target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
    SDL_SetTextureBlendMode(target, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, target);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_Rect srcRect = { x, y, w, h };
    SDL_Rect dstRect = { 0, 0, w, h };
    SDL_RenderCopy(renderer, source, &srcRect, &dstRect);
    SDL_SetRenderTarget(renderer, NULL);
    return target;
}
SDL_Texture* CreateTargetTexture(SDL_Renderer* renderer, SDL_Texture* srcTexture) {
    int width, height;
    SDL_QueryTexture(srcTexture, nullptr, nullptr, &width, &height);
    SDL_Texture* target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetTextureBlendMode(target, SDL_BLENDMODE_BLEND);
    return target;
}
SDL_Texture* Rotate_Left(SDL_Renderer *renderer, SDL_Texture *srcTexture) {
    SDL_Texture *rotatedTexture = CreateTargetTexture(renderer, srcTexture);
    SDL_SetRenderTarget(renderer, rotatedTexture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderCopyEx(renderer, srcTexture, nullptr, nullptr, 270, nullptr, SDL_FLIP_NONE);
    SDL_SetRenderTarget(renderer, nullptr);
    return rotatedTexture;
}
SDL_Texture* Rotate_180(SDL_Renderer *renderer, SDL_Texture *srcTexture) {
    SDL_Texture *rotatedTexture = CreateTargetTexture(renderer, srcTexture);
    SDL_SetRenderTarget(renderer, rotatedTexture);
   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderCopyEx(renderer, srcTexture, nullptr, nullptr, 180, nullptr, SDL_FLIP_NONE);
    SDL_SetRenderTarget(renderer, nullptr);
    return rotatedTexture;
}
SDL_Texture* Flip_Horizontal(SDL_Renderer *renderer, SDL_Texture *srcTexture) {
    SDL_Texture *flippedTexture = CreateTargetTexture(renderer, srcTexture);
    SDL_SetRenderTarget(renderer, flippedTexture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderCopyEx(renderer, srcTexture, nullptr, nullptr, 0, nullptr, SDL_FLIP_HORIZONTAL);
    SDL_SetRenderTarget(renderer, nullptr);
    return flippedTexture;
}
SDL_Texture* Flip_Vertical(SDL_Renderer *renderer, SDL_Texture *srcTexture) {
    SDL_Texture *flippedTexture = CreateTargetTexture(renderer, srcTexture);
    SDL_SetRenderTarget(renderer, flippedTexture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderCopyEx(renderer, srcTexture, nullptr, nullptr, 0, nullptr, SDL_FLIP_VERTICAL);
    SDL_SetRenderTarget(renderer, nullptr);
    return flippedTexture;
}
