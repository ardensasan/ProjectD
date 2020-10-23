#include "Input.h"
#include "Engine.h"
Input* Input::instance = nullptr;
Input::Input() {

}
Input* Input::GetInstance() {
	if (instance == nullptr)
		instance = new Input();
	return instance;
}

void Input::Listen() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			Engine::GetInstance()->Quit();
			break;
		case SDL_KEYDOWN:
			KeyDown();
			break;
		case SDL_KEYUP:
			KeyUp();
			break;
		}
	}
}

bool Input::GetKeyDown(SDL_Scancode key) {
	return (KeyState[key]);
}

void Input::KeyDown() {
	KeyState = SDL_GetKeyboardState(NULL);
}

void Input::KeyUp() {
	KeyState = SDL_GetKeyboardState(NULL);
}