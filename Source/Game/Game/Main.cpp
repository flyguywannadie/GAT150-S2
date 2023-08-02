#include <iostream>
#include "Core/Core.h" 
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Input/InputSystem.h"
#include "Player.h"
#include "Enemy.h"
#include "Audio/AudioSystem.h"
#include "Frame/Scene.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Frame/Emitter.h"

#include "Squisher.h"

#include <vector>
#include <thread>
#include <memory>

using namespace std;
using vec2 = max::Vector2;

int main(int argc, char* argv[])
{
	INFO_LOG;

	max::MemoryTracker::Initialize();
	max::seedRandom((unsigned int)time(nullptr));
	max::setFilePath("assets");

	max::g_renderer.Initialize();
	max::g_renderer.CreateWindow("CSC196", 800, 600);

	max::g_inputSystem.Initialize();

	max::g_audioSystem.Initialize();

	// Create Game
	unique_ptr<Squisher> game = make_unique<Squisher>();
	game->Initialize();

	bool quit = false;
	while (!quit) {
		// update engine
		max::g_time.Tick();

		max::g_audioSystem.Update();
		max::g_inputSystem.Update();
		max::g_particleSystem.Update(max::g_time.GetDeltaTime());
		if (max::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		// update game
		game->Update(max::g_time.GetDeltaTime());

		// draw game
		max::g_renderer.SetColor((uint8_t)0.5f, 1, (uint8_t)0.5f, 0);
		max::g_renderer.BeginFrame();

		// draw stuff
		game->Draw(max::g_renderer);
		max::g_renderer.EndFrame();
	}
	game->Shutdown();
	max::MemoryTracker::DisplayInfo();


	return 0;
}