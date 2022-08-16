#include "Engine.h"
#include <iostream>

using namespace std; 

class A {};
class B : public A{};
class C : public B{};

A* Create(const string& id)
{
    if (id == "B") return new B();
    if (id == "C") return new C();

    return nullptr;
}

int main()
{



    neu::InitializeMemory();
    neu::SetFilePath("../Assets");

    // Initialize Systems
    neu::g_renderer.Initialized();
    neu::g_inputSystem.Initialized();
    neu::g_audioSystem.Initialize();
    neu::g_resources.Initialize();

    neu::Engine::Instance().Register();

    // Create Window
    neu::g_renderer.CreateWindow("Window", 800, 600);
    neu::g_renderer.SetClearColor(neu::Color{ 50, 50, 50, 255 });

    //Load Assets
    std::shared_ptr<neu::Texture> texture = neu::g_resources.Get<neu::Texture>("Sprites/DarkGrayPlayer.png", &neu::g_renderer);

    {

        auto font = neu::g_resources.Get<neu::Font>("fonts/arcadeclassic.ttf", 10);
    }

    neu::g_audioSystem.AddAudio("Laser", "Laser_Shoot2.wav");
    // Create Actors
    neu::Scene scene;


    neu::Transform transform{ {400, 300}, 90, {1, 1 } };
   // std::unique_ptr<neu::Actor> actor = std::make_unique <neu::Actor>(transform);
    unique_ptr<neu::Actor> actor = neu::Factory::Instance().Create<neu::Actor>("Actor");
    actor->m_transform = transform;

    std::unique_ptr<neu::Component> pcomponent = neu::Factory::Instance().Create<neu::Component>("PlayerComponent");
    actor->AddComponent(std::move(pcomponent));

    std::unique_ptr<neu::ModelComponent> mcomponent = std::make_unique <neu::ModelComponent>();
    mcomponent->m_model = neu::g_resources.Get<neu::Model>("Sprites/DarkGrayPlayer.png");
    actor->AddComponent(std::move(mcomponent));

   /* std::unique_ptr<neu::SpriteComponent> scomponent = std::make_unique <neu::SpriteComponent>();
    scomponent->m_texture = texture;
    actor->AddComponent(std::move(scomponent));*/

    std::unique_ptr<neu::AudioComponent> acomponent = std::make_unique <neu::AudioComponent>();
    acomponent->m_SoundName = "Laser";
    actor->AddComponent(std::move(acomponent));

    std::unique_ptr<neu::Component> phcomponent = neu::Factory::Instance().Create<neu::Component>("PhysicsComponent");
    actor->AddComponent(std::move(phcomponent));

    // Child Actor
    neu::Transform transformC{ {10, 10}, 90, {1, 1 } };
    std::unique_ptr<neu::Actor> child = std::make_unique <neu::Actor>(transformC);

    std::unique_ptr<neu::ModelComponent> mcomponentC = std::make_unique <neu::ModelComponent>();
    mcomponentC->m_model = neu::g_resources.Get<neu::Model>("Sprites/DarkGrayPlayer.png");
    actor->AddComponent(std::move(mcomponentC));

    actor->AddChild(std::move(child));

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

        // Update Scene
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
