#pragma once
namespace utility
{
	struct vector3
	{
	public:
		float x, y, z;
		float magnitude();
		float magnitude_sq();
		vector3 normalize();
		vector3 clamp();
		static float dot(vector3 a, vector3 b);
		static vector3 mult(vector3 a, vector3 b);
	};
}