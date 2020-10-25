#ifndef TIMER_H
#define TIMER_H

const int FPS = 60;
const float DELTATIME = 1.5f;
class Timer
{
public:
	void Tick();
	inline float GetDeltaTime() { return deltaTime; };
	static Timer* GetInstance();
private:
	Timer();
	static Timer* instance;
	float deltaTime;
	float lastTime;
};
#endif