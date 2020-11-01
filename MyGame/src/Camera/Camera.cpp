#include "Camera.h"
#include "MapParser.h"
Camera* Camera::instance = nullptr;
Camera::Camera() {
	cameraView = { 0,0,0,0 };
};
Camera* Camera::GetInstance() {
	if (instance == nullptr) {
		instance = new Camera();
	}
	return instance;
}

void Camera::Set(int width, int height) {
	screenWidth = width;
	screenHeight = height;
	cameraView.w = width / 2;
	cameraView.h = height / 2;
}

void Camera::Update(float xPosition, float yPosition) {
	cameraView.x = int(xPosition - cameraView.w);
	cameraView.y = int(yPosition - cameraView.h);
	if (cameraView.x < 0)
		cameraView.x = 0;
	if (cameraView.y < 0)
		cameraView.y = 0;

	std::vector <TileMap> tilemaps = MapParser::GetInstance()->GetMapLayers();
	for (unsigned int i = 0; i < tilemaps.size();i++) {
		if (tilemaps[i].layerName == "Background") {
			int mapWidth = tilemaps[i].rowCount * tilemaps[i].tileWidth;
			int mapHeight = tilemaps[i].colCount * tilemaps[i].tileHeight;
			if (cameraView.x + screenWidth > mapWidth) {
				cameraView.x = mapWidth - screenWidth;
			}
			if (cameraView.y + screenHeight > mapHeight) {
				cameraView.y = mapHeight - screenHeight;
			}
			break;
		}
	}
}