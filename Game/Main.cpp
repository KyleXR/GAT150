#include "Engine.h"
#include "Renderer/Texture.h"
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

    // Create Window
    neu::g_renderer.CreateWindow("Window", 800, 600);
    neu::g_renderer.SetClearColor(neu::Color{ 50, 50, 50, 255 });

    std::shared_ptr<neu::Texture> texture = std::make_shared<neu::Texture>();
    texture->Create(neu::g_renderer, "Human.png");

    bool quit = false;
    while (!quit)
    {
        // Update (Engine)
        neu::g_time.Tick();
        neu::g_inputSystem.Update();
        neu::g_audioSystem.Update();

        if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::State::Pressed) quit = true;

        // Render
        neu::g_renderer.BeginFrame();

        neu::g_renderer.Draw(texture, { 400, 300 }, 0);

        neu::g_renderer.EndFrame();
    }

    neu::g_inputSystem.Shutdown();
    neu::g_renderer.Shutdown();
    neu::g_audioSystem.Shutdown();
    return 0;
}
