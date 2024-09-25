#pragma once

#include "Components/RenderSettings.h"
#include "Types/Vector2Float.h"

namespace Sample::VectorUtils {
	inline Types::Vector2Float GetScreenCenter(const Components::RenderSettings& renderSettings) {
		const auto unitSize = renderSettings.unitSize;
		return {
			static_cast<float>(renderSettings.screenWidth) / 2.f - unitSize / 2.f,
			static_cast<float>(renderSettings.screenHeight) / 2.f - unitSize / 2.f
		};
	}

	inline Types::Vector2Int ToScreenPosition(const Components::RenderSettings& renderSettings, const Types::Vector2Float& center, const Types::Vector2Int& worldPosition) {
		const auto unitSize = renderSettings.unitSize;
		return {
			static_cast<int>(center.x + static_cast<float>(worldPosition.x) * unitSize),
			static_cast<int>(center.y + static_cast<float>(worldPosition.y) * unitSize)
		};
	}

	inline Types::Vector2Int ToWorldPosition(const Components::RenderSettings& renderSettings, const Types::Vector2Float& center, const Types::Vector2Float& screenPosition) {
		const auto unitSize = renderSettings.unitSize;
		return {
			static_cast<int>(std::floor((screenPosition.x - center.x) / unitSize)),
			static_cast<int>(std::floor((screenPosition.y - center.y) / unitSize))
		};
	}
}