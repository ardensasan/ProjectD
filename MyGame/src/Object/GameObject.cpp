#include "GameObject.h"
void GameObject::SetProperties(std::string id,int w, int h) {
	textureID = id;
	width = w;
	height = h;
}