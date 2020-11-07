#ifndef CAMERA_H
#define CAMERA_H
#include "SDL.h"
class Camera
{
public:
	static Camera* GetInstance();
	void Set(int width, int height);
	void Update(float xPosition, float yPosition);
	inline SDL_Rect GetCameraView() { return cameraView; };
private:
	Camera();
	int screenWidth, screenHeight;
	static Camera* instance;
	SDL_Rect cameraView;
};
#endif

