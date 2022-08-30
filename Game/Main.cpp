#include "Engine.h"
#include "TheHunt.h"
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
    neu::g_eventManager.Initialize();

    neu::Engine::Instance().Register();

    // Create Window
    neu::g_renderer.CreateWindow("Window", 800, 600);
    neu::g_renderer.SetClearColor(neu::Color{ 50, 50, 50, 255 });

   // Create Game
    unique_ptr<TheHunt> game = make_unique<TheHunt>();
    game->Initialize();

    bool quit = false;
    while (!quit)
    {
        // Update (Engine)
        neu::g_time.Tick();
        neu::g_inputSystem.Update();
        neu::g_audioSystem.Update();
        neu::g_physicsSystem.Update();
        neu::g_eventManager.Update();

        if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::State::Pressed) quit = true;

       game->Update();

        // Render
        neu::g_renderer.BeginFrame();

        game->Draw(neu::g_renderer);

        neu::g_renderer.EndFrame();
    }

    game->Shutdown();
    game.reset();

    neu::Factory::Instance().Shutdown();

    neu::g_physicsSystem.Shutdown();
    neu::g_resources.Shutdown();
    neu::g_inputSystem.Shutdown();
    neu::g_renderer.Shutdown();
    neu::g_audioSystem.Shutdown();
    neu::g_eventManager.Shutdown();
}
