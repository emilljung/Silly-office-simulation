#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <sstream>
#include <Windows.h>

#include "GameEngine_Main.h"

typedef int lua_index;
typedef int (*lua_function)(lua_State *l);

class GameEngine
{
private:
	GameEngine_Main *main;

	bool loopActive;

	std::string m_GameEngineName;
	std::string m_GameEngineVersion;
	
private:
	int RegisterFunction(lua_State *l, std::string name, lua_function function);

	// Functions to register to Lua
	static int lua_printNameVr(lua_State *l);
	static int lua_print(lua_State *l);
	static int lua_setMainLoop(lua_State *l);
	static int lua_getInput(lua_State *l);
	static int lua_setLoopActive(lua_State *l);

	void setTimer(double t, int lua_index);
	void setLoopActive(bool loopActive);

	std::string GetName() const;
	std::string GetVersion() const;
					
public:
	GameEngine(GameEngine_Main *main);
	~GameEngine();

	void Init(std::string gameEngineName, std::string gameEngineVersion);
	void InitScriptInterface(lua_State *l);

	bool getLoopActive() const;

};

extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#endif
