#include "Timer.h"
#include <SDL.h>
Timer* Timer::instance = nullptr;
Timer::Timer() {
	flLastTime = 0;
	flDeltaTime = 1.5f;
}
#include <iostream>
Timer* Timer::GetInstance() {
	if (instance == nullptr) {
		instance = new Timer();
	}
	return  instance;
}
void Timer::Tick() {
	flDeltaTime = (SDL_GetTicks() - flLastTime)*(TARGET_FPS/1000.0f);
	if (flDeltaTime > TARGET_DELTATIME) {
		flDeltaTime = TARGET_DELTATIME;
	}
	flLastTime = SDL_GetTicks();
}
