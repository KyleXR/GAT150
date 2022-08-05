#pragma once
#include "Vector2.h"

namespace neu
{
	struct Transform
	{
		Vector2 position;
		float rotation{0};
		Vector2 scale{1, 1};
	};
}
