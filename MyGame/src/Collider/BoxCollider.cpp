#include "BoxCollider.h"
#include "SDL.h"
#include "Engine.h"
BoxCollider::BoxCollider() {
}

void BoxCollider::Update(float x, float y, int w, int h){
	objectBox = { int(x)+5, int(y)+5, w-10, h-5 };
}

void BoxCollider::Render(){
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &objectBox);
}