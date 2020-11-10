#include "BoxCollider.h"
#include "Engine.h"
#include "Camera.h"
BoxCollider::BoxCollider() {
	objectBox = { 0,0,0,0 };
}

void BoxCollider::Update(ObjectProperty objProp){
	if(objProp.type == "Player")
		objectBox = { int(objProp.xPosition)+5, int(objProp.yPosition)+5, objProp.width-10, objProp.height-5 };
	if(objProp.type == "Fruit")
		objectBox = { int(objProp.xPosition) + 7, int(objProp.yPosition) + 5, objProp.width - 14, objProp.height - 12 };
	if (objProp.type == "Enemy")
		objectBox = { int(objProp.xPosition), int(objProp.yPosition), objProp.width, objProp.height };
}

void BoxCollider::UpdateBoundary(ObjectProperty objProp) {
		objectBox = { int(objProp.xPosition), int(objProp.yPosition), objProp.width, objProp.height };
}

SDL_Rect BoxCollider::GetBoxCollider() {
	return objectBox;
}

void BoxCollider::Render() {
	SDL_Rect cameraView = Camera::GetInstance()->GetCameraView();
	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 200, 0, 0, 0);
	SDL_Rect dstRect = { objectBox.x - cameraView.x ,objectBox.y - cameraView.y,objectBox.w,objectBox.h };
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &dstRect);
}