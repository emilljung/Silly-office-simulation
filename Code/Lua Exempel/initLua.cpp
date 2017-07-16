#include "initLua.h"

initLua::initLua()
{
	this->lpLua = lua_open(); // Öppna Lua
	OpenLuaLibs(this->lpLua); // Ladda in lua-biblioteken

	this->main = new GameEngine_Main();

	this->gameEngine = new GameEngine(this->main);
	this->gameEngine->Init("BTH_ENGINE", "Emil Ljung Edition");
	this->gameEngine->InitScriptInterface(this->lpLua);	// Registrera funktionerna i gameengine_functions till Lua
}

initLua::~initLua()
{
	delete this->main;
	delete this->gameEngine;

	// Rensa minnet innan programmet stängs av
	lua_close(this->lpLua);
}

void initLua::mainLoop()
{
	while (this->gameEngine->getLoopActive()) 
	{ 
		this->main->Tick(this->lpLua); 
	}
}

void initLua::OpenLuaLibs(lua_State *l)
{
	// Öppna Lua-biblioteken i "lualibs".

	const luaL_reg *lpLib;

	for (lpLib = lualibs; lpLib->func != NULL; lpLib++)
	{
		lua_pushcfunction(l, lpLib->func);
		lua_pushstring(l, LUA_LOADLIBNAME);
		lua_call(l, 1, 0);
	}
}

int initLua::PrintLuaError()
{
	// Skriv ut lua errors.

	std::cout << "Lua error message:" << std::endl;
	std::cout << lua_tostring(this->lpLua, -1) << "\n\n";
	lua_pop(this->lpLua, 1); //Poppa bort error meddelandet från stacken
	return 1;
}

int initLua::callLuaFile(std::string fileName)
{
	// Anropa luafil.

	int rv = luaL_dofile(this->lpLua, fileName.c_str()), value = 0;
	if (rv != 0)
		value = this->PrintLuaError();

	return value;
}