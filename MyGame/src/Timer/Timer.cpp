#include "Timer.h"
#include <SDL.h>
Timer* Timer::instance = nullptr;

Timer::Timer() {}

Timer* Timer::GetInstance() {
	if (instance == nullptr) {
		instance = new Timer();
	}
	return  instance;
}

void Timer::Tick() {
	deltaTime = (SDL_GetTicks() - lastTime) * FPS / 1000.0f;
	if (deltaTime > DELTATIME) { deltaTime = 1.5f; }
	lastTime = float(SDL_GetTicks());
}