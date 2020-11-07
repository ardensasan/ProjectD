#include "Animation.h"
#include "TextureManager.h"
#include "Camera.h"
#include <iostream>
Animation::Animation(int w, int h) {
	width = w;
	height = h;
	frameRow = 0;
	frameCol = 0;
	animationDelay = 50;
}
void Animation::Update() {
	frameRow = (SDL_GetTicks() / animationDelay) % frameMaxRow;
}

void Animation::Render(int x, int y) {
	TextureManager::GetInstance()->DrawFrame(textureID, x, y, width, height, frameRow, frameCol, Camera::GetInstance()->GetCameraView(), flip);
}

void Animation::SetProperty(std::string id, SDL_RendererFlip f) {
	textureID = id;
	flip = f;
	frameMaxCol = TextureManager::GetInstance()->GetMaxFrameCols(textureID, height);
	frameMaxRow = TextureManager::GetInstance()->GetMaxFrameRows(textureID, width);
}
void Animation::Clean() {
	TextureManager::GetInstance()->Clean();
}
