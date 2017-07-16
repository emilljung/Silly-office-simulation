#include "Timer.h"

Timer::Timer() {}

Timer::Timer(double time, int luaID)
{
	this->time = time;
	this->luaID = luaID;
}

Timer::~Timer() {}

double Timer::getTime() const
{
	return this->time;
}

int Timer::getLuaID() const
{
	return this->luaID;
}