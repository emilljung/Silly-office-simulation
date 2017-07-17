#ifndef INITLUA_H
#define INITLUA_H

#include "GameEngine.h"
#include "GameEngine_Main.h"

class initLua
{
	private:
		GameEngine *gameEngine;
		GameEngine_Main *main;
		lua_State *lpLua;

	public:	
		initLua();
		~initLua();
	
		void mainLoop();
		int callLuaFile(std::string fileName);

	private:
		static void OpenLuaLibs(lua_State *l);
		int PrintLuaError();

};

extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

// All the libraries which are to be used with Lua
static const luaL_reg lualibs[] =
{
	{ "base", luaopen_base },
	{ "math", luaopen_math },
	{ "os", luaopen_os },
	{ "table", luaopen_table },
	{ "package", luaopen_package },
	{ NULL, NULL }
};

#endif
