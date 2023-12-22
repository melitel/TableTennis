#pragma once


struct Vector2f {

	Vector2f() : x(0.f), y(0.f) {}

	Vector2f(float x_, float y_) : x(x_), y(y_) {}
	
	Vector2f operator+(const Vector2f& val) {
		return Vector2f(x + val.x, y + val.y);
	}
	float x;
	float y;
};

struct BoundingBox {

	BoundingBox(const Vector2f& min_, const Vector2f& max_) :
		min(min_), max(max_) {}

	BoundingBox() = default;

	Vector2f min;
	Vector2f max;

	bool intersects(const BoundingBox& box) const
	{
		bool AisToTheRightOfB = min.x > box.max.x;
		bool AisToTheLeftOfB = max.x < box.min.x;
		bool AisAboveB = max.y < box.min.y;
		bool AisBelowB = min.y > box.max.y;

		if (!AisToTheRightOfB &&
			!AisToTheLeftOfB &&
			!AisAboveB &&
			!AisBelowB) 
		{
			return true;
		}
		else {
			return false;
		}
	}

	BoundingBox offset2world(const Vector2f& worldPos) {
		return BoundingBox(min + worldPos, max + worldPos);
	}
};

