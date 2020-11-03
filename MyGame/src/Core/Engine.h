#ifndef ENGINE_H
#define ENGINE_H
#include "SDL.h"
#include "GameObject.h"
#include <vector>
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
	int screenWidth, screenHeight;
	static Engine* instance;
	bool bIsRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<GameObject*> staticObjectList;
	std::vector<GameObject*> movingObjectList;
	GameObject* player;
};

#endif