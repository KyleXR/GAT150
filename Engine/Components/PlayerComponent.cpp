#include "PlayerComponent.h"
#include "Engine.h"
#include < iostream>

void neu::PlayerComponent::Update()
{
	// update transform with input
    Vector2 direction = Vector2::zero;
    if (neu::g_inputSystem.GetKeyState(neu::key_left) == neu::InputSystem::State::Held)
    {
        m_owner->m_transform.rotation += 180 * g_time.deltaTime;
        //direction = Vector2::left;
    }

    if (neu::g_inputSystem.GetKeyState(neu::key_right) == neu::InputSystem::State::Held)
    {
        m_owner->m_transform.rotation -= 180 * g_time.deltaTime;
        //direction = Vector2::right;
    }

    float thrust = 0;
    if (neu::g_inputSystem.GetKeyState(neu::key_up) == neu::InputSystem::State::Held)
    {
        thrust = speed;
        //direction = Vector2::up;
    }

    /*if (neu::g_inputSystem.GetKeyState(neu::key_down) == neu::InputSystem::State::Held)
    {
        direction = Vector2::down;
    }*/

    auto component = m_owner->GetComponent<PhysicsComponent>();
    if (component)
    {
        // Thrust Force
        Vector2 force = Vector2::Rotate({ 1, 0 }, Math::DegToRad(m_owner->m_transform.rotation)) * thrust;
        component->ApplyForce(force);

        // Gravitational Force
        force = (Vector2{ 400, 300 } - m_owner->m_transform.position).Normalized() * 60.0f;
        component->ApplyForce(force);
    }

    m_owner->m_transform.position += direction * 300 * g_time.deltaTime;

    if (neu::g_inputSystem.GetKeyState(neu::key_space) == neu::InputSystem::State::Pressed)
    {
       auto component =  m_owner->GetComponent<AudioComponent>();
       if (component)
       {
           component->Play();
       }
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
