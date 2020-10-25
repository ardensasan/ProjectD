#ifndef TIMER_H
#define TIMER_H

const int FPS = 60;
const float DELTATIME = 1.5f;
class Timer
{
public:
	void SetFrameStart();
	void Delay();
	static Timer* GetInstance();
private:
	Timer();
	static Timer* instance;
	int frameTime;
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
};
#endif