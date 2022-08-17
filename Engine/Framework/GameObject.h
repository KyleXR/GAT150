#pragma once
#include "Serialization/Serializable.h"

#define REGISTER_CLASS(class) Factory::Instance().Register<class>(#class);

namespace neu
{
	class GameObject
	{
	public:
	public:
		GameObject() = default;
		GameObject(const Transform& transform) : m_transform{ transform } {}

		virtual void Update() = 0;
		Transform m_transform;

	protected:
	};
}
