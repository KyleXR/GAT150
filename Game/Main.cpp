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

    // Create Window
    neu::g_renderer.CreateWindow("Window", 800, 600);
    neu::g_renderer.SetClearColor(neu::Color{ 50, 50, 50, 255 });

    std::shared_ptr<neu::Texture> texture = std::make_shared<neu::Texture>();
    texture->Create(neu::g_renderer, "Sprites/SpaceShip.png");

    neu::g_audioSystem.AddAudio("Laser", "Laser_Shoot2.wav");
    // Create Actors
    neu::Scene scene;


    neu::Transform transform{ {400, 300}, 90, {1, 1 } };
    std::unique_ptr<neu::Actor> actor = std::make_unique <neu::Actor>(transform);
    std::unique_ptr<neu::PlayerComponent> pcomponent = std::make_unique <neu::PlayerComponent>();
    actor->AddComponent(std::move(pcomponent));

    std::unique_ptr<neu::SpriteComponent> scomponent = std::make_unique <neu::SpriteComponent>();
    scomponent->m_texture = texture;
    actor->AddComponent(std::move(scomponent));

    std::unique_ptr<neu::AudioComponent> acomponent = std::make_unique <neu::AudioComponent>();
    acomponent->m_SoundName = "Laser";
    actor->AddComponent(std::move(acomponent));

    std::unique_ptr<neu::PhysicsComponent> phcomponent = std::make_unique <neu::PhysicsComponent>();
    actor->AddComponent(std::move(phcomponent));

    scene.Add(std::move(actor));

    float angle = 0;

    bool quit = false;
    while (!quit)
    {
        // Update (Engine)
        neu::g_time.Tick();
        neu::g_inputSystem.Update();
        neu::g_audioSystem.Update();

        if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::State::Pressed) quit = true;

       angle += 180.0f * neu::g_time.deltaTime;
       scene.Update();

        // Render
        neu::g_renderer.BeginFrame();

        scene.Draw(neu::g_renderer);
        //neu::g_renderer.Draw(texture, { 400, 300 }, angle, { 2 ,2 }, { 0.5f, 0.5f });
        //neu::g_playerComponent.Update();

        neu::g_renderer.EndFrame();
    }

    neu::g_inputSystem.Shutdown();
    neu::g_renderer.Shutdown();
    neu::g_audioSystem.Shutdown();
    return 0;
}
