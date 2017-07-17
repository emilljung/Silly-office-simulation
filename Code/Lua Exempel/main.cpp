#include "initLua.h"

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
