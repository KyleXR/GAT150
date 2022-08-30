#include "CollisionComponent.h"
#include "Engine.h"
#include <iostream>

void neu::CollisionComponent::Initialize()
{
    auto component = m_owner->GetComponent<RBPhysicsComponent>();
    if (component)
    {
        // if data was not set, get size from render component source rect 
        if (data.size.x == 0 && data.size.y == 0) 
            {
            auto renderComponent = m_owner;// !! check render component from the owner 
                if (renderComponent)
                {
                    data.size = Vector2{source.w, source.h };
                }
            }

        g_physicsSystem.SetCollisionBox(component->m_body, data, m_owner);
    }
}

void neu::CollisionComponent::Update()
{
}

void neu::CollisionComponent::OnCollisionEnter(Actor* other)
{
    if (m_enterFunction) m_enterFunction(other);
}

void neu::CollisionComponent::OnCollisionExit(Actor* other)
{
    if (m_exitFunction) m_exitFunction(other);
}

bool neu::CollisionComponent::Write(const rapidjson::Value& value) const
{
    return true;
}

bool neu::CollisionComponent::Read(const rapidjson::Value& value)
{
    READ_DATA(value, data.size);
    READ_DATA(value, data.density);
    READ_DATA(value, data.friction);
    READ_DATA(value, data.restitution);
    READ_DATA(value, data.is_trigger);
    
    return true;
}


