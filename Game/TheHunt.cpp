#include "TheHunt.h"
#include "Engine.h"

void TheHunt::Initialize()
{
	m_scene = std::make_unique<neu::Scene>();

    neu::Scene scene;

    rapidjson::Document document;
    std::vector<std::string> sceneNames = { "Scenes/Prefabs.txt", "Scenes/tilemap.txt", "Scenes/Level.txt" };

    for (auto sceneName : sceneNames)
    {
        bool success = neu::json::Load(sceneName, document);
        if (!success)
        {
            LOG("Could Not Load Scene %s", sceneName.c_str());
            continue;
        }

        bool read = m_scene->Read(document);

        if (!read)
        {
            LOG("Could Not Read Scene %s", sceneName.c_str());
            continue;
        }
    }

    m_scene->Initialize();

    
    for (int i = 0; i < 10; i++)
    {
        auto actor = neu::Factory::Instance().Create<neu::Actor>("Coin");
        actor->m_transform.position = { neu::randomf(0,800), 100.0f };
        actor->Initialize();

        m_scene->Add(std::move(actor));
    }

    neu::g_eventManager.Subscribe("EVENT_ADD_POINTS", std::bind(&TheHunt::OnAddPoints, this, std::placeholders::_1));
}

void TheHunt::Shutdown()
{
    m_scene->RemoveAll();
}

void TheHunt::Update()
{
    switch (m_gameState)
    {
    case TheHunt::gameState::titleScreen:
        if (neu::g_inputSystem.GetKeyState(neu::key_space) == neu::InputSystem::State::Pressed)
        {
            m_scene->GetActorFromName("Title")->SetActive(false);

            m_gameState = gameState::startLevel;
        }
        break;
    case TheHunt::gameState::startLevel:
        for (int i = 0; i < 10; i++)
        {
            auto actor = neu::Factory::Instance().Create<neu::Actor>("Coin");
            actor->m_transform.position = { neu::randomf(0,800), 100.0f };
            actor->Initialize();

            m_scene->Add(std::move(actor));
        }
        break;
    case TheHunt::gameState::playerDead:
        m_stateTimer -= neu::g_time.deltaTime;
        if (m_stateTimer <= 0)
        {
            m_gameState = (m_lives > 0) ? gameState::startLevel : gameState::gameOver;
        }
        break;
    }

    m_scene->Update();
}

void TheHunt::Draw(neu::Renderer& renderer)
{
    m_scene->Draw(renderer);
}

void TheHunt::OnAddPoints(const neu::Event& event)
{
    AddPoints(std::get<int>(event.data));

    std::cout << event.name << std::endl;
    std::cout << GetScore() << std::endl;
}

void TheHunt::OnPlayerDead(const neu::Event& event)
{
    m_gameState = gameState::playerDead;
    m_lives--;
    m_stateTimer = 3;
}
