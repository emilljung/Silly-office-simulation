#ifndef GAMEENGINE_MAIN_H
#define GAMEENGINE_MAIN_H

#include <ctime>

#include "Timer.h"

struct lua_State;

class GameEngine_Main
{
private:
	std::pair<double, Timer> *timer;

	bool loopActive;

private:
	int runGameLoop(lua_State *l, Timer &timer);

public:
	GameEngine_Main();
	~GameEngine_Main();

	bool Tick(lua_State *l);	// Main-loopen

	void setLoopActive(bool loopActive);
	void setTimer(double t, int lua_index);	// För runGameLoop & lua_setMainLoop
};

extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#endif