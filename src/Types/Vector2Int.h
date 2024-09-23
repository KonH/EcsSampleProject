#pragma once

namespace Sample::Types {
	struct Vector2Int {
		int x;
		int y;
	};

	inline Vector2Int operator+(const Vector2Int& lhs, const Vector2Int& rhs) {
		return { lhs.x + rhs.x, lhs.y + rhs.y };
	}

	inline Vector2Int& operator+=(Vector2Int& lhs, const Vector2Int& rhs) {
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		return lhs;
	}

	inline bool operator==(const Vector2Int& lhs, const Vector2Int& rhs) {
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}
}