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
	static Input* instance;
	const Uint8* KeyState;
	void KeyUp();
	void KeyDown();
};
#endif

