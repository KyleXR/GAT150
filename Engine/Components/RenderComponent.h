#pragma once
#include "Framework/Component.h"

namespace neu
{
	class Renderer;

	class RenderComponent : public Component
	{
	public:
		virtual void Draw(Renderer& renderer) = 0;


		// Inherited via Component
		virtual void Update() override;

	};
}