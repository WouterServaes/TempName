#include "MiniginPCH.h"

#if _DEBUG
//ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "Minigin.h"
#include "TestGame.h"

int main()
{
	auto* pGame = new TestGame();
	pGame->Run();
	delete pGame;
	return 0;
}