#pragma once
#include "Component.h"
#include <vector>

namespace max
{
	class TilemapComponent : public Component
	{
	public:
		CLASS_DECLERATION(TilemapComponent);

		bool Initialize() override;
		void Update(float dt) override;

	public:
		int numColumns = 0;
		int numRows = 0;
		vec2 size;

		std::vector<std::string> tileNames;
		std::vector<int> tiles;

	};
}
