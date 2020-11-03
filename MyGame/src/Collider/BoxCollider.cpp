#include "BoxCollider.h"
#include "Engine.h"
BoxCollider::BoxCollider() {
}

void BoxCollider::Update(float x, float y, int w, int h,std::string type){
	if(type == "Player")
		objectBox = { int(x)+5, int(y)+5, w-10, h-5 };
	if(type == "Fruit")
		objectBox = { int(x) + 7, int(y) + 5, w - 14, h - 12 };
}

void BoxCollider::Render(){
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &objectBox);
}