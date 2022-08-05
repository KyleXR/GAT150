#pragma once
#include "GameObject.h"
#include "../Renderer/Model.h"

namespace neu
{
	class Scene;

	class Actor : public GameObject
	{
	public:
		Actor() = default;
		Actor(const Model& model, const Transform& transform) : GameObject{ transform }, m_model{model} {}

		virtual void Update() override {}
		virtual void Draw(Renderer& renderer);

		virtual void onCollision(Actor* other) {}
		float GetRadius() { return m_model.GetRadius() * std::max(m_transform.scale.x, m_transform.scale.y); }
		std::string& GetTag() { return m_tag; }

		friend class Scene;

	public:

	protected:
		std::string m_tag;

		bool m_destroy = false;

		// Physics
		Vector2 m_velocity;
		float m_damping = 1;

		Scene* m_scene = nullptr;
		Model m_model;
	};
}