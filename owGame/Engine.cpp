#include "stdafx.h"

// Include
#include "GameState.h"

// General
#include "Engine.h"

// Additional
#include "ConsoleOpenGL.h"
#include "GameState_Empty.h"

bool Engine::Init(vector<string>& _argumentQueue) {
	// Add debug outputs
	Debug::AddDebugOutput(new DebugOutput_ConsoleWindows);
	Debug::AddDebugOutput(new DebugOutput_Log);

	// Load graphics
	_ModulesMgr->LoadModule(_GLFW, true);

	Debug::Green("Engine[]: Loading.");

	// Arguments
	Debug::Print("Engine[]: Arguments count: [%d]", _argumentQueue.size());
	for (auto it = _argumentQueue.begin(); it != _argumentQueue.end(); ++it)
		Debug::Print("Engine[]: Argument: [%s]", (*it).c_str());

	// Load static classes
	Debug::Init();
	Random::SetSeed(static_cast<unsigned long>(GetTicks()));

	// Load modules
	_ModulesMgr->LoadModule(_Render, true);
	//_ModulesMgr->LoadModule(_FileSystem, true);
	_ModulesMgr->LoadModule(_TexturesMgr, true);
	_ModulesMgr->LoadModule(_FontsMgr, true);
	_ModulesMgr->LoadModule(_Input, true);
	_ModulesMgr->LoadModule(_UIMgr, true);

	// Add OpenGL console
	consoleOpenGL = new ConsoleOpenGL;
	Debug::AddDebugOutput(consoleOpenGL);

	// Add listener
	_Input->AddInputListener(consoleOpenGL);
	_Input->AddInputListener(_UIMgr);

	needExit = false;
	currentGameState = nullptr;

	framesCounter = 0;
	framesPerSecond = 0;
	framesTimer = 0;

	t = 0;

	return true;
}

void Engine::Destroy() {
	Debug::Green("Engine[]: Destroy engine.");

	if (currentGameState != nullptr)
		currentGameState->Destroy();

	_ModulesMgr->DestroyAllModules();
}

bool Engine::SetGameState(GameState* _newGameState) {
	Debug::Print("Engine[]: Setting new GameState.");

	if (_newGameState == nullptr) {
		Debug::Error("Engine[]: New GameState in null.");
		return false;
	}

	if (currentGameState != nullptr) {
		currentGameState->Destroy();
		delete currentGameState;
		Debug::Print("Engine[]: Current GameState destroyed.");
	}

	currentGameState = _newGameState;
	if (!currentGameState->IsInited()) {
		Debug::Warn("Engine[]: New GameState in not inited. Initializating.");
		currentGameState->Init();
	}

	return true;
}

bool Engine::Tick() {
	if (currentGameState == nullptr) {
		Debug::Warn("Current game state is null. Set empty GameState.");
		this->SetGameState(new GameState_Empty);
	}

	last_t = t;
	t = GetTicks();
	uint32_t dt = t - last_t;
	time += dt;
	ftime = static_cast<float>(time) / 1000.0f;

	// Input
	if (currentGameState != nullptr)
		currentGameState->InputPhase(ftime, static_cast<double>(dt) / 1000.0);

	// Update
	if (currentGameState != nullptr)
		currentGameState->UpdatePhase(ftime, static_cast<double>(dt) / 1000.0);
	_UIMgr->Update();

	// Render world
	_Render->Set3D();
	if (currentGameState != nullptr)
		currentGameState->RenderPhase(ftime, static_cast<double>(dt) / 1000.0);

	// Render UI
	_Render->Set2D();
	if(currentGameState != nullptr)
		currentGameState->RenderUIPhase(ftime, static_cast<double>(dt) / 1000.0);

	_UIMgr->Render();
	consoleOpenGL->Render();

	// Swap buffers
	if(!_GLFW->SwapWindowBuffers())
		if(!needExit) {
			Debug::Green("Engine[]: Need exit.");
			needExit = true;
			return false;
		}

	// Caclulate FPS
	double currentTime = _GLFW->GetTime();
	double delta = currentTime - framesTimer;
	framesCounter++;
	if(delta > 1.0) {
		framesPerSecond = static_cast<int>(static_cast<double>(framesCounter) / delta);
		framesTimer = currentTime;
		framesCounter = 0;

		_GLFW->SetWindowTitle("FPS: " + to_string(framesPerSecond));
	}

	return true;
}

//---------------------------------------------------------

unsigned long long Engine::GetTicks() const {
	return static_cast<unsigned long long>(_GLFW->GetTime() * 1000.0);
}

//---------------------------------------------------------