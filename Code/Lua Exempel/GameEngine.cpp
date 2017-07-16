#include "GameEngine.h"

GameEngine *g_GameEngine = NULL;

// { <Funktionsnamnet i Lua>, <vilken funktion i C++ som kopplas till funktionsnamnet i Lua> }{ "Print", GameEngine_Print },
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
	// Registrera funktionerna i gameengine_functions till GameEngine i Lua.
	luaL_register(l, "GameEngine", gameengine_functions);
	lua_settop(l, 0); // �terst�ll stacken, det kan h�nda att vi f�r skr�pv�rden ifall detta inte g�rs
	
	// Skapa en globalvariabel i Lua som heter GameEngine
	lua_getglobal(l, "GameEngine");

	// Registrera f�ljande GameEngine-funktioner till variabeln GameEngine i Lua
	this->RegisterFunction(l, "PrintNameVr", GameEngine::lua_printNameVr);
	this->RegisterFunction(l, "Print", GameEngine::lua_print);
	this->RegisterFunction(l, "SetMainLoop", GameEngine::lua_setMainLoop);
	this->RegisterFunction(l, "GetInput", GameEngine::lua_getInput);
	this->RegisterFunction(l, "SetLoopActive", GameEngine::lua_setLoopActive);

	lua_settop(l, 0); // �terst�ll stacken
}

int GameEngine::RegisterFunction(lua_State *l, std::string name, lua_function function)
{
	lua_pushstring(l, name.c_str());		// Vad funktionen ska heta i Lua.
	lua_pushlightuserdata(l, (void*)this);	// Pekare till GameEngine-klassen.
	lua_pushcclosure(l, function, 1);		// Funktionen fr�n C++.
	lua_settable(l, -3);					// Os�ker p� exakt varf�r det ska vara -3.
	return 0;
}

// Dessa funktioner definierar funktionerna i Lua, t.ex GameEngine.Print("Hej")
//----------------------------------------------------------------------------------------------
int GameEngine::lua_printNameVr(lua_State *l)
{
	std::string out;
	int args = lua_gettop(l);

	// Kolla om antalet argument �r 0
	if (args != 0) luaL_error(l, "PrintNameVr needs no arguments");

	// out inneh�ller nu argumenten som skickades till GameEngine.Print(...) i lua
	std::cout << g_GameEngine->GetName() + ": " + g_GameEngine->GetVersion() << "\n";
	return 0; // Antal return v�rden
}

int GameEngine::lua_print(lua_State *l)
{
	std::string out;
	int args = lua_gettop(l);

	for (int i = 1; i <= args; ++i)
		out += lua_tostring(l, i);	// Sj�lva v�rdet i argumentet/argumenten

	// out inneh�ller nu argumenten som skickades till GameEngine.Print(...) i lua
	std::cout << out << std::endl;
	return 0; // Antal return v�rden
}

int GameEngine::lua_setMainLoop(lua_State *l)
{
	int argc = lua_gettop(l);

	// Kolla om antalet argument �r 2
	if(argc != 2) luaL_error(l, "notify needs two arguments");

	// Parameter nr1 m�ste vara ett nummer
	if(!lua_isnumber(l, 1))
		luaL_error(l, "first parameter is not a number");

	// Parameter nr2 m�ste vara en funktion
	if(!lua_isfunction(l, 2))
		luaL_error(l, "second parameter is not a function");
	
	int refID = luaL_ref(l, LUA_REGISTRYINDEX); // refID �r ID:t till GameLoop() i lua
		
	g_GameEngine->setTimer(lua_tonumber(l, 1), refID);

	return 1;
}

int GameEngine::lua_getInput(lua_State *l)
{
	// Skicka inmatningv�rdet (true/false) till lua

	int args = lua_gettop(l);

	// Kolla s� att antalet argument till GameEngine.GetInput(...) �r 1
	if (args != 0)
		luaL_error(l, "GetInput takes no argument: %i given", lua_gettop(l));
	
	if (GetAsyncKeyState('Q'))
		lua_pushboolean(l, false);
	else
		lua_pushboolean(l, true);

	// Antal argument att returnera (tror jag)
	return 1;
}

int GameEngine::lua_setLoopActive(lua_State *l)
{
	int args = lua_gettop(l);

	// Kolla om antalet argument till GameEngine.SetLoopActive(...) i lua �r 1
	if (args != 1)
		luaL_error(l, "SetLoopActive takes 1 argument: %i was given", lua_gettop(l));

	// Kolla om det f�rsta argumentet �r en void-pekare
	if (!lua_isboolean(l, 1))
		luaL_error(l, "SetLoopActive wants a boolean");

	// Om v�rdet fr�n Lua �r skilt fr�n 0 s� s�tts loopActive till true, annars false.
	g_GameEngine->setLoopActive(lua_toboolean(l, 1) != 0);

	return 0;
}
//----------------------------------------------------------------------------------------------

void GameEngine::setTimer(double t, int lua_index)
{
	// S�tt ett nytt v�rde till multimap<double, Timer>
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