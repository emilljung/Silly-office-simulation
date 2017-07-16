#include "initLua.h"

// Lua-stacken �r ett gemensamt lagringsutrymme f�r C/C++ & lua.
// Helt enkelt, via C/C++ s� kan jag pusha in en int i stacken och sedan
// mha av en egendefinierad funktion i lua h�mta int-v�rdet fr�n stacken.
// Liknande g�r f�rst�s att g�ra �t andra h�llet.

//##########################################################################
//#
//#  Det ska vara l�tt att...
//#  * l�gga till ny lua-fil och koppla den till ett C++-objekt
//#  * anpassa biblioteken efter vad lua-filerna beh�ver (om det g�r)
//#  * anpassa vilka GameEngine-funktioner som ska anv�ndas i varje lua-fil (potentiellt kandidatarbete?)
//#  * 
//#
//##########################################################################

// - L�gg �ver ALLT som har med spelmotorn att g�ra i GameEngine (timer mm)
// - GameEngine m�ste definieras innan callLuaFile(..) k�rs
// - G�r om GameEngine_Main till en slags MainLoop-klass
// - G�r ett C++ objekt f�r varje karakt�r osv i Lua och fixa kommunikation mellan dessa
// - L�gg till Frank D Lunas time-klass
// - Ordna s� att all kommunikation INTE m�ste g� igenom en slags loop-fil i Lua 


int main()
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	initLua lua;
	if (lua.callLuaFile("GameLoop.lua") != 1) // 1 inneb�r att filen inte hittades
		lua.mainLoop();

	return 0;
}