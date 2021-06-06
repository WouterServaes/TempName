#include "MiniginPCH.h"

#if _DEBUG
//ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "Minigin.h"
#include "QBertGame.h"

int main()
{
	auto* pGame = new QBertGame();
	pGame->Run();
	delete pGame;
	return 0;
}