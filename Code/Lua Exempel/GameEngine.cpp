#include "GameEngine.h"

GameEngine *g_GameEngine = NULL;

// { <The function name in Lua>, <The function in C++ which connects to the function in Lua> }{ "Print", GameEngine_Print },
static const luaL_reg gameengine_functions[] =
{
	{ NULL, NULL }
};

GameEngine::GameEngine(GameEngine_Main *main)
{
	this->m_GameEngineName = "Unknown";
	this->m_GameEngineVersion = "Unknwown";
	this->loopActive = true;
	this->main = main;
}

GameEngine::~GameEngine()
{
	g_GameEngine = NULL;
}

void GameEngine::Init(std::string gameEngineName, std::string gameEngineVersion)
{
	this->m_GameEngineName = gameEngineName;
	this->m_GameEngineVersion = gameEngineVersion;

	std::cout << this->m_GameEngineName << "\n";
	std::cout << this->m_GameEngineVersion << "\n";

	g_GameEngine = this;
}

void GameEngine::InitScriptInterface(lua_State *l)
{
	// Register the functions in gameengine_functions to GameEngine in Lua
	luaL_register(l, "GameEngine", gameengine_functions);
	lua_settop(l, 0); // Reset the stack. 
	
	// Create a global variable in Lua named GameEngine.
	lua_getglobal(l, "GameEngine");

	// Register the following functions to the variable GameEngine in Lua.
	this->RegisterFunction(l, "PrintNameVr", GameEngine::lua_printNameVr);
	this->RegisterFunction(l, "Print", GameEngine::lua_print);
	this->RegisterFunction(l, "SetMainLoop", GameEngine::lua_setMainLoop);
	this->RegisterFunction(l, "GetInput", GameEngine::lua_getInput);
	this->RegisterFunction(l, "SetLoopActive", GameEngine::lua_setLoopActive);

	lua_settop(l, 0);
}

int GameEngine::RegisterFunction(lua_State *l, std::string name, lua_function function)
{
	lua_pushstring(l, name.c_str());		// Name of the function in Lua.
	lua_pushlightuserdata(l, (void*)this);		// Pointer to the GameEngine class.
	lua_pushcclosure(l, function, 1);		// The function from C++.
	lua_settable(l, -3);
	return 0;
}

// These C++ functions defines the functions in Lua, for instance GameEngine.Print("Hello")
//----------------------------------------------------------------------------------------------
int GameEngine::lua_printNameVr(lua_State *l)
{
	std::string out;
	int args = lua_gettop(l);

	// Check if the argument is 0
	if (args != 0) luaL_error(l, "PrintNameVr needs no arguments");

	std::cout << g_GameEngine->GetName() + ": " + g_GameEngine->GetVersion() << "\n";
	return 0; // Zero return values to Lua
}

int GameEngine::lua_print(lua_State *l)
{
	std::string out;
	int args = lua_gettop(l);

	for (int i = 1; i <= args; ++i)
		out += lua_tostring(l, i);	// The arugment from Print(x) in Lua

	// The variable out now contains the arguments which were sent to GameEngine.Print(...) in Lua
	std::cout << out << std::endl;
	return 0;
}

int GameEngine::lua_setMainLoop(lua_State *l)
{
	int argc = lua_gettop(l);

	if(argc != 2) luaL_error(l, "notify needs two arguments");

	// The first parameter must be a number
	if(!lua_isnumber(l, 1))
		luaL_error(l, "first parameter is not a number");

	// The second parameter must be a function
	if(!lua_isfunction(l, 2))
		luaL_error(l, "second parameter is not a function");
	
	int refID = luaL_ref(l, LUA_REGISTRYINDEX); // refID is the ID to GameLoop() in Lua
		
	g_GameEngine->setTimer(lua_tonumber(l, 1), refID);

	return 1;
}

int GameEngine::lua_getInput(lua_State *l)
{
	int args = lua_gettop(l);

	if (args != 0)
		luaL_error(l, "GetInput takes no argument: %i given", lua_gettop(l));
	
	// Return false to Lua if the Q key is pressed
	if (GetAsyncKeyState('Q'))
		lua_pushboolean(l, false);
	else
		lua_pushboolean(l, true);

	return 1;
}

int GameEngine::lua_setLoopActive(lua_State *l)
{
	int args = lua_gettop(l);

	if (args != 1)
		luaL_error(l, "SetLoopActive takes 1 argument: %i was given", lua_gettop(l));

	// Check if the first argument is a void pointer
	if (!lua_isboolean(l, 1))
		luaL_error(l, "SetLoopActive wants a boolean");

	// If the value from Lua isn't 0, then loopActive is set to true, otherwise false.
	g_GameEngine->setLoopActive(lua_toboolean(l, 1) != 0);

	return 0;
}
//----------------------------------------------------------------------------------------------

void GameEngine::setTimer(double t, int lua_index)
{
	// New value to multimap<double, Timer>
	this->main->setTimer(t, lua_index);
}

void GameEngine::setLoopActive(bool loopActive)
{
	this->loopActive = loopActive;
}

bool GameEngine::getLoopActive() const
{
	return this->loopActive;
}

std::string GameEngine::GetName() const
{
	return this->m_GameEngineName;
}

std::string GameEngine::GetVersion() const
{
	return this->m_GameEngineVersion;
}
