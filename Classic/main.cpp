#include "stdafx.h"

// Additional
#include "GameState_Menu.h"
#include "GameState_InWorld.h"
#include <ctime>

int main(int argumentCount, char* arguments[])
{
/*#ifdef _DEBUG 
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif*/

	Random::SetSeed(static_cast<unsigned long>(time(0)));

	CSettings settings;
	settings.AddDefaults();

	CWindowsPlatformFactory winPlatformFactory;

	CLog log;
	log.AddDebugOutput(winPlatformFactory.CreateDebugOutputConsole());

	CConsole console;
	console.AddCommonCommands();

	CMPQArchiveManager mpqArchiveManager;
	
	CFilesManager filesManager;

	CEngine engine(winPlatformFactory.CreateOpenGLAdapter());
	engine.SetArguments(argumentCount, arguments);

	CConsoleOpenGL openGLConsole;
	log.AddDebugOutput(&openGLConsole);

	CLoader loader;

	GameStateManager gsManager;
	gsManager.AddGameState(GameStatesNames::GAME_STATE_MENU, new GameState_Menu());
	gsManager.AddGameState(GameStatesNames::GAME_STATE_WORLD, new GameState_InWorld());
	gsManager.SetGameState(GameStatesNames::GAME_STATE_MENU);

	while (engine.Tick());

	return 0;
}
