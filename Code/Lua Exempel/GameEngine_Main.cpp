#include "GameEngine_Main.h"

GameEngine_Main::GameEngine_Main()
{
	this->timer = new std::pair<double, Timer>;
	this->loopActive = true;
}

GameEngine_Main::~GameEngine_Main()
{
	delete this->timer;
}

bool GameEngine_Main::Tick(lua_State *l)
{
	// Själva main-loopen. Programmet har kommit från void initLua::mainLoop()

	double timeout = double(time(0));
	while (this->timer->first < timeout)
	{
		this->runGameLoop(l, this->timer->second);
	}

	return this->loopActive;
}

int GameEngine_Main::runGameLoop(lua_State *l, Timer &timer)
{
	// Kalla på GameLoop() i lua
	lua_rawgeti(l, LUA_REGISTRYINDEX, timer.getLuaID());

	// Kolla om referensindexet är till en funktion
	if (!lua_isfunction(l, -1))
		luaL_error(l, "callback is not a function!");

	if (lua_pcall(l, 0, LUA_MULTRET, 0) != 0)
		luaL_error(l, "error running callback: %s", lua_tostring(l, -1));

	// Antalet returvärden
	int retvals = lua_gettop(l);

	// Kolla om antalet returvärd en är mer än 0 och är nummer
	if (retvals > 0 && lua_isnumber(l, 1))
	{
		int retrigger = lua_tointeger(l, 1);

		// Ställ om timern till 0
		if (retrigger != 0)
			this->setTimer(timer.getTime(), timer.getLuaID());
	}

	// Poppa antalet returvärden
	lua_pop(l, retvals);
	return 0;
}

void GameEngine_Main::setTimer(double t, int lua_index)
{
	this->timer->first = double(time(0)) + t;
	this->timer->second = Timer(t, lua_index);
}

void GameEngine_Main::setLoopActive(bool loopActive)
{
	this->loopActive = loopActive;
}