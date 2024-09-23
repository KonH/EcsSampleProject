#pragma once

namespace Sample::Types {
	struct Vector2Float {
		float x;
		float y;
	};

	inline Vector2Float operator+(const Vector2Float& lhs, const Vector2Float& rhs) {
		return { lhs.x + rhs.x, lhs.y + rhs.y };
	}

	inline Vector2Float& operator+=(Vector2Float& lhs, const Vector2Float& rhs) {
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		return lhs;
	}

	inline bool operator==(const Vector2Float& lhs, const Vector2Float& rhs) {
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}
}