#include "RBPhysicsComponent.h"
#include "Engine.h"

neu::RBPhysicsComponent::~RBPhysicsComponent()
{
	if (m_body)
	{
		g_physicsSystem.DestroyBody(m_body);
	}
}

void neu::RBPhysicsComponent::Initialize()
{
	m_body = g_physicsSystem.CreateBody(m_owner->m_transform.position, m_owner->m_transform.rotation, data);
	m_body->SetGravityScale(data.gravity_scale);
	m_body->SetLinearDamping(damping);
}

void neu::RBPhysicsComponent::Update()
{
	Vector2 position = B2VEC2_TO_VECTOR2(m_body->GetPosition());
	m_owner->m_transform.position = PhysicsSystem::WorldToScreen(position);
	m_owner->m_transform.rotation = m_body->GetAngle();
}

void neu::RBPhysicsComponent::ApplyForce(const Vector2 force)
{
	m_body->ApplyForceToCenter(VECTOR2_TO_B2VEC2(force), true);
}

bool neu::RBPhysicsComponent::Write(const rapidjson::Value& value) const
{
	return true;
}

bool neu::RBPhysicsComponent::Read(const rapidjson::Value& value)
{
	PhysicsComponent::Read(value);

	READ_DATA(value, data.gravity_scale);
	READ_DATA(value, data.constrain_angle);
	READ_DATA(value, data.is_dynamic);

	return true;
}