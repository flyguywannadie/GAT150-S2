#include <iostream>
#include "Core/Core.h" 
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"

#include "Frame/framework.h"
#include "Frame/Resource/ResourceManager.h"
#include "Physics/PhysicsSystem.h"

#include "Blaster.h"

#include <vector>
#include <thread>
#include <memory>
#include <array>
#include <functional>

using namespace std;
using vec2 = max::Vector2;

int main(int argc, char* argv[])
{


	INFO_LOG("Initialize Engine");

	max::MemoryTracker::Initialize();
	max::seedRandom((unsigned int)time(nullptr));
	max::setFilePath("assets");

	max::g_renderer.Initialize();
	max::g_renderer.CreateWindow("CSC196", 800, 600);

	max::g_inputSystem.Initialize();

	max::g_audioSystem.Initialize();

	max::PhysicsSystem::Instance().Initialize();

	// Create Game
	Blaster::Instance().Initialize();


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

		max::PhysicsSystem::Instance().Update(max::g_time.GetDeltaTime());

		// update game
		Blaster::Instance().Update(max::g_time.GetDeltaTime());

		// draw game
		max::g_renderer.SetColor((uint8_t)0.5f, 1, (uint8_t)0.5f, 0);
		max::g_renderer.BeginFrame();

		// draw stuff
		Blaster::Instance().Draw(max::g_renderer);

		//max::g_renderer.DrawTexture(texture.get(), 0.0f, 0.0f, 0.0f);

		max::g_renderer.EndFrame();
	}
	Blaster::Instance().Shutdown();
	max::MemoryTracker::DisplayInfo();


	return 0;
}