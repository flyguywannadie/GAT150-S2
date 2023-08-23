#include <iostream>
#include "Core/Core.h" 
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Player.h"
#include "Enemy.h"
#include "Audio/AudioSystem.h"

#include "Frame/framework.h"
#include "Frame/Resource/ResourceManager.h"
#include "Physics/PhysicsSystem.h"

#include "Squisher.h"

#include <vector>
#include <thread>
#include <memory>
#include <array>
#include <functional>

using namespace std;
using vec2 = max::Vector2;

void print(int i) {
	cout << i << endl;
}

int add(int i1, int i2) {
	return i1 + i2;
}

int sub(int i1, int i2) {
	return i1 - i2;
}

class A
{
public:
	int add(int i1, int i2) {
		return i1 + i2;
	}
};

union Data
{
	int i;
	bool b;
	char c[6];
};

int main(int argc, char* argv[])
{
	Data data;
	data.b = true;

	cout << data.b << endl;

	void (*func_ptr)(int) = &print;

	func_ptr(5);

	int (*op_ptr)(int, int);

	op_ptr = &add;
	func_ptr(op_ptr(3, 4));

	op_ptr = &sub;
	func_ptr(op_ptr(3, 4));

	std::function<int(int, int)> op;
	op = add;
	cout << op(5, 6) << endl;

	A a;
	op = std::bind(&A::add, &a, std::placeholders::_1, std::placeholders::_2);
	func_ptr(op(6,6));





	INFO_LOG ("Initialize Engine");

	max::MemoryTracker::Initialize();
	max::seedRandom((unsigned int)time(nullptr));
	max::setFilePath("assets");

	max::g_renderer.Initialize();
	max::g_renderer.CreateWindow("CSC196", 800, 600);

	max::g_inputSystem.Initialize();

	max::g_audioSystem.Initialize();

	max::PhysicsSystem::Instance().Initialize();

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