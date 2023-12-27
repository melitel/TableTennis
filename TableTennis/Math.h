#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>


struct Vector2f {

	Vector2f() : x(0.f), y(0.f) {}

	Vector2f(float x_, float y_) : x(x_), y(y_) {}
	
	Vector2f operator+(const Vector2f& val) const {
		return Vector2f(x + val.x, y + val.y);
	}

	Vector2f operator-(const Vector2f& val) const{
		return Vector2f(x - val.x, y - val.y);
	}

	Vector2f operator-() const {
		return Vector2f(-x, -y);
	}
	
	Vector2f operator*(float val) const {
		return Vector2f(x * val, y * val);
	}

	float x;
	float y;

	float length() const {
		return std::sqrt(x * x + y * y);
	}

	Vector2f normalized(Vector2f& vector) const{
		float len = length();

		if (len != 0.0f) {
			return Vector2f(vector.x / len, vector.y / len);
		}
		else {
			// Handle the case where the length is zero to avoid division by zero
			return Vector2f(0.0f, 0.0f);
		}
	}

	Vector2f normalized() const {

		float length = std::sqrt(x * x + y * y);

		if (length != 0.0f) {
			return Vector2f(x / length, y / length);
		}
		else {
			// Handle the case where the length is zero to avoid division by zero
			return Vector2f(0.0f, 0.0f);
		}
	}

	float dot(const Vector2f& vec) const {
		return x * vec.x + y * vec.y;
	}

	Vector2f reflect(const Vector2f& normal) const {
		float dotp = dot(normal) * 2.f;

		return normal * dotp - *this;
	}
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

	BoundingBox offset2world(const Vector2f& worldPos) const {
		return BoundingBox(min + worldPos, max + worldPos);
	}	
};

inline sf::Vector2f vec2sfml(const Vector2f& vec) {
	return sf::Vector2f(vec.x, vec.y);
}

inline Vector2f sfml2svec(const sf::Vector2f& vec) {
	return Vector2f(vec.x, vec.y);
}

inline Vector2f operator*(float val, const Vector2f& vec) {
	return Vector2f(vec.x * val, vec.y * val);
}


