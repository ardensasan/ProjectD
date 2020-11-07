#ifndef TIMER_H
#define TIMER_H

const int TARGET_FPS = 60;
const int FRAMEDELAY = 1000/ TARGET_FPS;
class Timer
{
public:
	void Tick();
	static Timer* GetInstance();
private:
	Timer();
	static Timer* instance;
	int frameTime;
};
#endif