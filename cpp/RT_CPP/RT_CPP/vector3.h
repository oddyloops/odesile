#pragma once
namespace utility
{
	struct vector3
	{
	public:
		float x, y, z;
		float magnitude();
		vector3 normalize();
	};
}