#include <iostream>
#include "Core/Core.h" 
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Player.h"
#include "EnemyComponent.h"
#include "Audio/AudioSystem.h"

#include "Frame/framework.h"
#include "Frame/Resource/ResourceManager.h"

#include "Squisher.h"

#include <vector>
#include <thread>
#include <memory>
#include <array>

using namespace std;
using vec2 = max::Vector2;

int main(int argc, char* argv[])
{
	INFO_LOG ("Initialize Engine");

	max::MemoryTracker::Initialize();
	max::seedRandom((unsigned int)time(nullptr));
	max::setFilePath("assets");

	rapidjson::Document document;
	max::Json::Load("Json.txt", document);
	int i1;
	max::Json::Read(document, "integer1", i1);
	std::cout << i1 << std::endl;
	int i2;
	max::Json::Read(document, "integer2", i2);
	std::cout << i2 << std::endl;
	std::string str;
	max::Json::Read(document, "string", str);
	std::cout << str << std::endl;
	bool b;
	max::Json::Read(document, "boolean", b);
	std::cout << b << std::endl;
	float f;
	max::Json::Read(document, "float", f);
	std::cout << f << std::endl;
	max::vec2 v2;
	max::Json::Read(document, "vector2", v2);
	std::cout << v2 << std::endl;

	max::g_renderer.Initialize();
	max::g_renderer.CreateWindow("CSC196", 800, 600);

	max::g_inputSystem.Initialize();

	max::g_audioSystem.Initialize();

	// Create Game
	Squisher::Instance().Initialize();

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
		Squisher::Instance().Update(max::g_time.GetDeltaTime());

		// draw game
		max::g_renderer.SetColor((uint8_t)0.5f, 1, (uint8_t)0.5f, 0);
		max::g_renderer.BeginFrame();

		// draw stuff
		Squisher::Instance().Draw(max::g_renderer);

		//max::g_renderer.DrawTexture(texture.get(), 0.0f, 0.0f, 0.0f);

		max::g_renderer.EndFrame();
	}
	Squisher::Instance().Shutdown();
	max::MemoryTracker::DisplayInfo();


	return 0;
}