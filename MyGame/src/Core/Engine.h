#ifndef ENGINE_H
#define ENGINE_H
#include "SDL.h"
class Engine
{
public:
	static Engine* GetInstance();
	void Init();
	inline bool IsRunning(){ return bIsRunning; };
	inline SDL_Renderer* GetRenderer() { return renderer; };
	void Quit();
	void Events();
	void Update();
	void Render();
	void Clean();
private:
	Engine();
	static Engine* instance;
	bool bIsRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif