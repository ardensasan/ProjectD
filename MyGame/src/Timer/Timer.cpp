#include "Timer.h"
#include <SDL.h>
Timer* Timer::instance = nullptr;
Uint32 frameStart;
Timer::Timer() {}

Timer* Timer::GetInstance() {
	if (instance == nullptr) {
		instance = new Timer();
	}
	return  instance;
}
void Timer::SetFrameStart() {
	frameStart = SDL_GetTicks();
}
void Timer::Delay() {
	frameTime = SDL_GetTicks() - frameStart;
	if (frameDelay > frameTime) {
		SDL_Delay(frameDelay - frameTime);
	}
}