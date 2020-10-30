#ifndef INPUT_H
#define INPUT_H
#include "SDL.h"
class Input
{
public:
	static Input* GetInstance();
	void Listen();
	bool GetKeyDown(SDL_Scancode key);
private:
	Input();
	SDL_Scancode lastKey;
	static Input* instance;
	const Uint8* KeyState;
	bool jumpReleased;
	void KeyUp();
	void KeyDown();
};
#endif

