#include "initLua.h"

initLua::initLua()
{
	this->lpLua = lua_open(); // Open Lua
	OpenLuaLibs(this->lpLua); // Load the lua libraries

	this->main = new GameEngine_Main();

	this->gameEngine = new GameEngine(this->main);
	this->gameEngine->Init("BTH_ENGINE", "Emil Ljung Edition");
	this->gameEngine->InitScriptInterface(this->lpLua); // Register the functions in gameengine_functions to Lua
}

initLua::~initLua()
{
	delete this->main;
	delete this->gameEngine;

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
	// Open the lua libraries in "lualibs".

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
	// Print lua errors.

	std::cout << "Lua error message:" << std::endl;
	std::cout << lua_tostring(this->lpLua, -1) << "\n\n";
	lua_pop(this->lpLua, 1); // Pop the error message from the lua stack.
	return 1;
}

int initLua::callLuaFile(std::string fileName)
{
	// Open a lua file.

	int rv = luaL_dofile(this->lpLua, fileName.c_str()), value = 0;
	if (rv != 0)
		value = this->PrintLuaError();

	return value;
}
