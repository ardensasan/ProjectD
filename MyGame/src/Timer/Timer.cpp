#include "Timer.h"
#include <SDL.h>
Timer* Timer::instance = nullptr;
Uint32 frameStart;
Timer::Timer() {
	frameTime = 0;
}

Timer* Timer::GetInstance() {
	if (instance == nullptr) {
		instance = new Timer();
	}
	return  instance;
}
void Timer::Tick() {
	frameTime = SDL_GetTicks() - frameStart;
	if (FRAMEDELAY > frameTime) {
		SDL_Delay(FRAMEDELAY - frameTime);
	}
	frameStart = SDL_GetTicks();
}
