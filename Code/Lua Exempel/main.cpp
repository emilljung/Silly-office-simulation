#include "initLua.h"

// Lua-stacken är ett gemensamt lagringsutrymme för C/C++ & lua.
// Helt enkelt, via C/C++ så kan jag pusha in en int i stacken och sedan
// mha av en egendefinierad funktion i lua hämta int-värdet från stacken.
// Liknande går förstås att göra åt andra hållet.

//##########################################################################
//#
//#  Det ska vara lätt att...
//#  * lägga till ny lua-fil och koppla den till ett C++-objekt
//#  * anpassa biblioteken efter vad lua-filerna behöver (om det går)
//#  * anpassa vilka GameEngine-funktioner som ska användas i varje lua-fil (potentiellt kandidatarbete?)
//#  * 
//#
//##########################################################################

// - Lägg över ALLT som har med spelmotorn att göra i GameEngine (timer mm)
// - GameEngine måste definieras innan callLuaFile(..) körs
// - Gör om GameEngine_Main till en slags MainLoop-klass
// - Gör ett C++ objekt för varje karaktär osv i Lua och fixa kommunikation mellan dessa
// - Lägg till Frank D Lunas time-klass
// - Ordna så att all kommunikation INTE måste gå igenom en slags loop-fil i Lua 


int main()
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	initLua lua;
	if (lua.callLuaFile("GameLoop.lua") != 1) // 1 innebär att filen inte hittades
		lua.mainLoop();

	return 0;
}