#include "Animation.h"
#include "TextureManager.h"
#include <iostream>
Animation::Animation() {
	frameRow = 0;
	frameCol = 0;
}
void Animation::Update() {
	frameRow = (SDL_GetTicks() / animationDelay) % frameMaxRow;
}

void Animation::Draw(int x, int y, int width, int height) {
	TextureManager::GetInstance()->DrawFrame(textureID, x, y, width, height, frameRow, frameCol, flip);
}

void Animation::SetProperty(std::string id, int width, int height, int animationdelay, SDL_RendererFlip f) {
	textureID = id;
	animationDelay = animationdelay;
	flip = f;
	frameMaxCol = TextureManager::GetInstance()->GetMaxFrameCols(textureID, height);
	frameMaxRow = TextureManager::GetInstance()->GetMaxFrameRows(textureID, width);
}
void Animation::Clean() {
	TextureManager::GetInstance()->Clean();
}
