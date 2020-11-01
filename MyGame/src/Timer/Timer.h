#ifndef TIMER_H
#define TIMER_H

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.5f;
class Timer
{
public:
	void Tick();
	static Timer* GetInstance();
	inline float GetDeltaTime() { return flDeltaTime; }
private:
	Timer();
	static Timer* instance;
	float flDeltaTime;
};
#endif