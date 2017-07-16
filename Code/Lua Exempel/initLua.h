#ifndef INITLUA_H
#define INITLUA_H

#include "GameEngine.h"
#include "GameEngine_Main.h"

class initLua
{
	private:	// Variabler
		GameEngine *gameEngine;
		GameEngine_Main *main;
		lua_State *lpLua;

	public:		// Funktioner
		initLua();
		~initLua();
	
		void mainLoop();						// Går till GameEngine_Main::Tick
		int callLuaFile(std::string fileName);	// Anropa luafil.

	private:	// Funktioner
		static void OpenLuaLibs(lua_State *l);	// Öppna Lua-biblioteken i "lualibs".
		int PrintLuaError();					// Skriv ut lua errors.

};

extern "C" //<--- Behövs för att få lua att funka med C++
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

// Alla bibliotek som ska användas med Lua
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