#include "Engine.h"
#include <iostream>

using namespace std; 

int main()
{

    neu::InitializeMemory();
    neu::SetFilePath("../Assets");

    // Initialize Systems
    neu::g_renderer.Initialized();
    neu::g_inputSystem.Initialized();
    neu::g_audioSystem.Initialize();
    neu::g_resources.Initialize();
    neu::g_physicsSystem.Initialize();

    neu::Engine::Instance().Register();

    // Create Window
    neu::g_renderer.CreateWindow("Window", 800, 600);
    neu::g_renderer.SetClearColor(neu::Color{ 50, 50, 50, 255 });

    neu::Scene scene;

    rapidjson::Document document;
    bool success = neu::json::Load("level.txt", document);

    scene.Read(document);
    scene.Initialize();

    bool quit = false;
    while (!quit)
    {
        // Update (Engine)
        neu::g_time.Tick();
        neu::g_inputSystem.Update();
        neu::g_audioSystem.Update();
        neu::g_physicsSystem.Update();

        if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::State::Pressed) quit = true;

        // Update Scene
       scene.Update();

        // Render
        neu::g_renderer.BeginFrame();

        scene.Draw(neu::g_renderer);

        neu::g_renderer.EndFrame();
    }

    neu::g_inputSystem.Shutdown();
    neu::g_renderer.Shutdown();
    neu::g_audioSystem.Shutdown();
    return 0;
}
