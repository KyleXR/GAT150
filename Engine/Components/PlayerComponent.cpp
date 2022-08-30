#include "PlayerComponent.h"
#include "Engine.h"
#include < iostream>

void neu::PlayerComponent::Initialize()
{
    auto component = m_owner->GetComponent<CollisionComponent>();
    if (component)
    {
        component->SetCollisionEnter(std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1));
        component->SetCollisionExit(std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1));
    }
}

void neu::PlayerComponent::Update()
{
    float thrust = 0;
	// update transform with input
    Vector2 direction = Vector2::zero;
    if (neu::g_inputSystem.GetKeyState(neu::key_left) == neu::InputSystem::State::Held)
    {
        direction = Vector2::left;
    }

    if (neu::g_inputSystem.GetKeyState(neu::key_right) == neu::InputSystem::State::Held)
    {
        direction = Vector2::right;
    }

    if (neu::g_inputSystem.GetKeyState(neu::key_up) == neu::InputSystem::State::Held)
    {
        auto component = m_owner->GetComponent<PhysicsComponent>();
        if (component)
        {
            component->ApplyForce(Vector2::up * 10);
        }
    }

    auto component = m_owner->GetComponent<PhysicsComponent>();
    if (component)
    {
        // Thrust Force
        Vector2 force = Vector2::Rotate({ 1, 0 }, Math::DegToRad(m_owner->m_transform.rotation)) * thrust;
        component->ApplyForce(force);

        // Gravitational Force
        //force = (Vector2{ 400, 300 } - m_owner->m_transform.position).Normalized() * 60.0f;
        component->ApplyForce(direction * speed);
    }

    m_owner->m_transform.position += direction * 300 * g_time.deltaTime;

    if (neu::g_inputSystem.GetKeyState(neu::key_space) == neu::InputSystem::State::Pressed)
    {
        auto component = m_owner->GetComponent<PhysicsComponent>();
        if (component)
        { }
    }
}

bool neu::PlayerComponent::Write(const rapidjson::Value& value) const
{
    return true;
}

bool neu::PlayerComponent::Read(const rapidjson::Value& value)
{
    READ_DATA(value, speed);

    return true;
}

void neu::PlayerComponent::OnCollisionEnter(Actor* other)
{
    if (other->GetName() == "Coin")
    {
        Event event;
        event.name = "EVENT_ADD_POINTS";
        event.data = 100;

        g_eventManager.Notify(event);

        other->SetDestroy();
    }
    std::cout << "Player Enter\n";
}

void neu::PlayerComponent::OnCollisionExit(Actor* other)
{
    std::cout << "Player Exit\n";
}
