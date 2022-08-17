#pragma once
#include "GameObject.h"


namespace neu
{
	class Actor;

	class Component : public GameObject, public ISerializable
	{
	public:
		Component() = default;

		friend class Actor;

	protected:
		Actor* m_owner = nullptr;
	};
}