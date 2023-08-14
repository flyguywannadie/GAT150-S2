#pragma once
#include "Component.h"

namespace max
{
	class RenderComponent : public Component {
	public:
		virtual void Draw(class Renderer& renderer) = 0;
		virtual float GetRadius() { return 0; }
	};
}