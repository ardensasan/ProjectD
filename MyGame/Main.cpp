#include "Engine.h"
#include "Timer.h"
int main(int argc, char* argv[]) {
	Engine::GetInstance()->Init();
	while (Engine::GetInstance()->IsRunning()) {
		Timer::GetInstance()->SetFrameStart();
		Engine::GetInstance()->Events();
		Engine::GetInstance()->Update();
		Engine::GetInstance()->Render();
		Timer::GetInstance()->Delay();
	}
	Engine::GetInstance()->Clean();
	return 0;
}