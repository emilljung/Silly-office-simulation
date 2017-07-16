#ifndef TIMER_H
#define TIMER_H

#include <iostream>

class Timer
{
private:
	double time;
	int luaID;

public:
	Timer();
	Timer(double time, int luaID);
	~Timer();

	double getTime() const;
	int getLuaID() const;

};

#endif